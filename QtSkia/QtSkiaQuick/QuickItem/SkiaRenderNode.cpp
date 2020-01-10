#include "SkiaRenderNode.h"
#include "QSkiaQuickItem.h"

#include "core/SkImageInfo.h"
#include "core/SkSurface.h"
#include "gpu/GrContext.h"
#include "src/gpu/gl/GrGLUtil.h"
#include <QOpenGLContext>
#include <QOpenGLFramebufferObject>
#include <QOpenGLFunctions>
#include <QQuickWindow>
#include <QDebug>
class SkiaGLContext {
public:
    static SkiaGLContext& instance()
    {
        static SkiaGLContext ctx;
        return ctx;
    }
    SkSurface* getSurface(QQuickItem* pItem)
    {
        auto it = surfaceMap.find(pItem->window());
        if (it != surfaceMap.end()) {
            return it.value().get();
        }
        return nullptr;
    }
    SkSurface* addNode(QQuickItem* pItem)
    {
        auto it = windowCountMap.find(pItem->window());
        if (it != windowCountMap.end()) {
            (*it)++;
            return surfaceMap.value(pItem->window()).get();
        }
        return create(pItem);
    }
    void removeNode(QQuickItem* pItem)
    {
        qWarning() << __FUNCTION__;
        auto it = windowCountMap.find(pItem->window());
        if (it != windowCountMap.end()) {
            (*it)--;
            if (windowCountMap.value(pItem->window()) <= 0) {
                windowCountMap.remove(pItem->window());
                contextMap.remove(pItem->window());
                surfaceMap.remove(pItem->window());
            }
        }
    }
    void resize(QQuickItem* pItem)
    {
        qWarning() << __FUNCTION__;
        init(pItem);
    }

protected:
    SkiaGLContext() {}
    SkSurface* create(QQuickItem* pItem)
    {
        qWarning() << __FUNCTION__;
        auto pCtx = GrContext::MakeGL();
        SkASSERT(pCtx);
        contextMap[pItem->window()] = pCtx;
        SkSurface* pSurface = init(pItem);
        windowCountMap[pItem->window()]++;
        return pSurface;
    }
    SkSurface* init(QQuickItem* pItem)
    {
        qWarning() << __FUNCTION__;
        GrGLFramebufferInfo info;
        auto pWindow = pItem->window();
        info.fFBOID = pWindow->openglContext()->defaultFramebufferObject();
        SkColorType colorType;
        colorType = kRGBA_8888_SkColorType;
        if (pWindow->format().renderableType() == QSurfaceFormat::RenderableType::OpenGLES) {
            info.fFormat = GR_GL_BGRA8;
        } else {
            info.fFormat = GR_GL_RGBA8;
        }
        auto size = pItem->size().toSize();

        GrBackendRenderTarget backend(size.width(), size.height(), pWindow->format().samples(), pWindow->format().stencilBufferSize(), info);
        // setup SkSurface
        // To use distance field text, use commented out SkSurfaceProps instead
        // SkSurfaceProps props(SkSurfaceProps::kUseDeviceIndependentFonts_Flag,
        //                      SkSurfaceProps::kLegacyFontHost_InitType);
        SkSurfaceProps props(SkSurfaceProps::kLegacyFontHost_InitType);

        auto gpuSurface = SkSurface::MakeFromBackendRenderTarget(contextMap.value(pItem->window()).get(), backend, kBottomLeft_GrSurfaceOrigin, colorType, nullptr, &props);
        if (!gpuSurface) {
            SkDebugf("SkSurface::MakeRenderTarget return null\n");
            return nullptr;
        }
        auto pos = pItem->mapToScene(pItem->position()).toPoint();
        pWindow->openglContext()->functions()->glViewport(pos.x(), pos.y(), size.width(), size.height());
        surfaceMap[pWindow] = gpuSurface;
        return gpuSurface.get();
    }

private:
    QMap<QQuickWindow*, int> windowCountMap;
    QMap<QQuickWindow*, sk_sp<GrContext>> contextMap;
    QMap<QQuickWindow*, sk_sp<SkSurface>> surfaceMap;
};
SkiaRenderNode::SkiaRenderNode(QSkiaQuickItem* parent)
    : m_item(parent)
{
    qWarning() << __FUNCTION__;
    m_lastTime = QTime::currentTime();
    m_lastSize = m_item->size();
}

void SkiaRenderNode::render(const QSGRenderNode::RenderState*)
{
//    qWarning() << __FUNCTION__;
    SkSurface* pSurface = SkiaGLContext::instance().getSurface(m_item);
    if (!pSurface) {
        pSurface = SkiaGLContext::instance().addNode(m_item);
    } else if (m_item->size() != m_lastSize) {
        SkiaGLContext::instance().resize(m_item);
    }
    if (!pSurface || !pSurface->getCanvas()) {
        qWarning() << __FUNCTION__ << "null ctx";
        return;
    }
    auto cost = m_lastTime.elapsed();
    m_lastTime = QTime::currentTime();
    m_item->draw(pSurface->getCanvas(), cost);
}

void SkiaRenderNode::releaseResources()
{
    qWarning() << __FUNCTION__;
    SkiaGLContext::instance().removeNode(m_item);
}

QSGRenderNode::StateFlags SkiaRenderNode::changedStates() const
{
    return (ColorState | BlendState|DepthState);
}

QSGRenderNode::RenderingFlags SkiaRenderNode::flags() const
{
    return static_cast<QSGRenderNode::RenderingFlags>(BoundedRectRendering | DepthAwareRendering);
}

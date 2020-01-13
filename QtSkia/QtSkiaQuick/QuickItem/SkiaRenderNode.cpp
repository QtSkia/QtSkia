#include "SkiaRenderNode.h"
#include "QSkiaQuickItem.h"

#include "core/SkImageInfo.h"
#include "core/SkSurface.h"
#include "gpu/GrContext.h"
#include "src/gpu/gl/GrGLUtil.h"
#include <QDebug>
#include <QMatrix4x4>
#include <QOpenGLContext>
#include <QOpenGLFramebufferObject>
#include <QOpenGLFunctions>
#include <QQuickWindow>
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
        auto pWindow = pItem->window();
        if (!pWindow) {
            qWarning() << __FUNCTION__ << "storedWindow is empty";
            return;
        }
        auto it = windowCountMap.find(pWindow);
        if (it != windowCountMap.end()) {
            (*it)--;
            if (windowCountMap.value(pWindow) <= 0) {
                windowCountMap.remove(pWindow);
                contextMap.remove(pWindow);
                surfaceMap.remove(pWindow);
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

        auto gpuSurface = SkSurface::MakeFromBackendRenderTarget(contextMap.value(pItem->window()).get(), backend, kTopLeft_GrSurfaceOrigin, colorType, nullptr, &props);
        if (!gpuSurface) {
            qDebug() << "SkSurface::MakeRenderTarget return null";
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
static SkMatrix qmat2skmat(QMatrix4x4 originMat)
{
    SkMatrix mat;
    mat[0] = originMat.constData()[0];
    mat[1] = originMat.constData()[1];
    mat[2] = originMat.constData()[2];
    mat[3] = originMat.constData()[4];
    mat[4] = originMat.constData()[5];
    mat[5] = originMat.constData()[6];
    mat[6] = originMat.constData()[8];
    mat[7] = originMat.constData()[9];
    mat[8] = originMat.constData()[10];

    return mat;
}
QDebug& operator<<(QDebug& dbg, QMatrix4x4 mat)
{
    dbg << mat.constData()[0] << mat.constData()[1] << mat.constData()[2];
    dbg << mat.constData()[4] << mat.constData()[5] << mat.constData()[6];
    dbg << mat.constData()[8] << mat.constData()[9] << mat.constData()[10];
    return dbg;
}

SkiaRenderNode::SkiaRenderNode(QSkiaQuickItem* parent)
    : m_item(parent)
{
    qWarning() << __FUNCTION__;
    m_lastTime = QTime::currentTime();
    m_lastSize = m_item->size();
    QObject::connect(
        m_item->window(), &QQuickWindow::sceneGraphAboutToStop, m_item, [&]() {
            SkiaGLContext::instance().removeNode(m_item);
        },
        static_cast<Qt::ConnectionType>(Qt::DirectConnection | Qt::UniqueConnection));
}

SkiaRenderNode::~SkiaRenderNode()
{
    releaseResources();
}

void SkiaRenderNode::releaseResources()
{
    qWarning() << __FUNCTION__;
}

void SkiaRenderNode::render(const QSGRenderNode::RenderState* state)
{
    SkSurface* pSurface = SkiaGLContext::instance().getSurface(m_item);
    if (!pSurface) {
        qWarning() << __FUNCTION__ << "create ctx";
        pSurface = SkiaGLContext::instance().addNode(m_item);
        m_item->onInit(static_cast<int>(m_item->width()), static_cast<int>(m_item->height()));
    } else if (m_item->size() != m_lastSize) {
        qWarning() << __FUNCTION__ << "resize";
        SkiaGLContext::instance().resize(m_item);
        m_lastSize = m_item->size();
    }
    if (!pSurface || !pSurface->getCanvas()) {
        qWarning() << __FUNCTION__ << "null ctx";
        return;
    }
    auto cost = m_lastTime.elapsed();
    m_lastTime = QTime::currentTime();

    SkAutoCanvasRestore r(pSurface->getCanvas(), true);

    auto pos = m_item->mapToScene(m_item->position()).toPoint();
    m_item->window()->openglContext()->functions()->glViewport(pos.x(), pos.y(), m_item->width(), m_item->height());
    //    qWarning() <<*state->projectionMatrix();
    //    pSurface->getCanvas()->concat(qmat2skmat(*state->projectionMatrix()));
    m_item->draw(pSurface->getCanvas(), cost);
}

QSGRenderNode::StateFlags SkiaRenderNode::changedStates() const
{
    return (ColorState | BlendState | DepthState);
}

QSGRenderNode::RenderingFlags SkiaRenderNode::flags() const
{
    return static_cast<QSGRenderNode::RenderingFlags>(BoundedRectRendering | DepthAwareRendering);
}

QRectF SkiaRenderNode::rect() const
{
    return QRectF(0, 0, m_item->width(), m_item->height());
}

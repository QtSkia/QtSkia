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
class SkiaRenderNodePrivate {
public:
    SkiaRenderNodePrivate(QSkiaQuickItem* item)
        : pItem(item)
    {
        qWarning() << __FUNCTION__;
        pContext = GrContext::MakeGL();
        SkASSERT(pContext);
    }
    ~SkiaRenderNodePrivate()
    {
        qWarning() << __FUNCTION__;
        pContext = nullptr;
        pSurface = nullptr;
    }

    void resizeSurface()
    {
        initSurface();
    }
    void initSurface()
    {
//        auto size = pItem->size().toSize();
//        auto info = SkImageInfo::MakeN32Premul(size.width(), size.height());
//        pSurface = SkSurface::MakeRenderTarget(pContext.get(), SkBudgeted::kNo, info);
//        if (!pSurface) {
//            qDebug() << "SkSurface::MakeRenderTarget return null";
//            return;
//        }

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

                pSurface = SkSurface::MakeFromBackendRenderTarget(pContext.get(), backend, kTopLeft_GrSurfaceOrigin, colorType, nullptr, &props);
                if (!pSurface) {
                    qDebug() << "SkSurface::MakeRenderTarget return null";
                    return;
                }

        //        auto pos = pItem->mapToScene(pItem->position()).toPoint();
        //        pItem->window()->openglContext()->functions()->glViewport(pos.x(), pos.y(), size.width(), size.height());
    }

private:
    friend class SkiaRenderNode;
    QSkiaQuickItem* pItem;
    sk_sp<GrContext> pContext = nullptr;
    sk_sp<SkSurface> pSurface = nullptr;
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
    : m_dptr(new SkiaRenderNodePrivate(parent))
    , m_item(parent)
{
    m_lastTime = QTime::currentTime();
    m_lastSizeF = m_item->size();
}

SkiaRenderNode::~SkiaRenderNode()
{
    delete m_dptr;
    m_dptr = nullptr;
}
void SkiaRenderNode::render(const QSGRenderNode::RenderState* state)
{
    QSizeF realSizeF = m_item->size();
    QSize realSize = realSizeF.toSize();
    if (!m_dptr->pSurface) {
        qWarning() << __FUNCTION__ << "init";
        m_dptr->initSurface();
        m_item->onInit(realSize.width(), realSize.height());
    } else if (realSizeF != m_lastSizeF) {
        qWarning() << __FUNCTION__ << "resize";
        m_dptr->resizeSurface();
        m_item->onInit(realSize.width(), realSize.height());
        m_lastSizeF = realSizeF;
    }
    if (!m_dptr->pSurface || !m_dptr->pSurface->getCanvas()) {
        qWarning() << __FUNCTION__ << "null ctx";
        return;
    }
    auto pCanvas = m_dptr->pSurface->getCanvas();
    auto cost = m_lastTime.elapsed();
    m_lastTime = QTime::currentTime();

    SkAutoCanvasRestore r(pCanvas, true);
    m_item->draw(pCanvas, cost);
    if (m_item->window()) {
        m_item->window()->resetOpenGLState();
    }
}

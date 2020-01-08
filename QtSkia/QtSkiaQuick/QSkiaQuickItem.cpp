#include "QSkiaQuickItem.h"

#include "core/SkImageInfo.h"
#include "core/SkSurface.h"
#include "gpu/GrContext.h"
#include "src/gpu/gl/GrGLUtil.h"

#include <QOpenGLContext>
#include <QOpenGLFramebufferObject>
#include <QOpenGLFunctions>
#include <QResizeEvent>
#include <QTime>
#include <QTimer>

class QSkiaQuickItemPrivate {
public:
    sk_sp<GrContext> context = nullptr;
    sk_sp<SkSurface> gpuSurface = nullptr;
    QTime lastTime;
    QTimer timer;
};
QSkiaQuickItem::QSkiaQuickItem(QQuickItem* parent)
    : QQuickItem(parent)
    , m_dptr(new QSkiaQuickItemPrivate)
{
    connect(this, &QQuickItem::windowChanged, this, &QSkiaQuickItem::handleWindowChanged);

}

QSkiaQuickItem::~QSkiaQuickItem()
{
    delete m_dptr;
    m_dptr = nullptr;
}

void QSkiaQuickItem::handleWindowChanged(QQuickWindow* win)
{
    if (win) {
        qWarning() << __FUNCTION__;
        connect(win, &QQuickWindow::beforeSynchronizing, this, &QSkiaQuickItem::sync, Qt::DirectConnection);
        connect(win, &QQuickWindow::sceneGraphAboutToStop, this, &QSkiaQuickItem::cleanup, Qt::DirectConnection);
        win->setClearBeforeRendering(false);
//        connect(&m_dptr->timer, &QTimer::timeout, this, [&]() {
//            if (window() && isVisible() && window()->isSceneGraphInitialized()) {
//                window()->update();
//            }
//        });
//        m_dptr->timer.start(1000 / 60);
    }
}
void QSkiaQuickItem::sync()
{
    if (!m_dptr->context) {
        qWarning() << __FUNCTION__;
        m_dptr->context = GrContext::MakeGL();
        if (!m_dptr->context) {
            SkDebugf("GrContext::MakeGL return null\n");
            return;
        }
        init(static_cast<int>(width()), static_cast<int>(height()));
        connect(window(), &QQuickWindow::beforeRendering, this, &QSkiaQuickItem::onBeforeRendering, Qt::DirectConnection);
        m_dptr->lastTime = QTime::currentTime();
    }
}
void QSkiaQuickItem::cleanup()
{
    m_dptr->gpuSurface = nullptr;
    m_dptr->context = nullptr;
}

void QSkiaQuickItem::geometryChanged(const QRectF& newGeometry, const QRectF& oldGeometry)
{
    QQuickItem::geometryChanged(newGeometry, oldGeometry);
    if (newGeometry == oldGeometry) {
        return;
    }
    if (m_dptr->context && window() && isVisible() && window()->isSceneGraphInitialized()) {
        init(static_cast<int>(newGeometry.width()), static_cast<int>(newGeometry.height()));
        update();
    }
}

void QSkiaQuickItem::init(int w, int h)
{
    qWarning() << window()->renderTarget();
    qWarning() << window()->openglContext();
    qWarning() << window()->openglContext()->defaultFramebufferObject();

    GrGLFramebufferInfo info;
    info.fFBOID = window()->openglContext()->defaultFramebufferObject();
    SkColorType colorType;
    colorType = kRGBA_8888_SkColorType;
    if (window()->format().renderableType() == QSurfaceFormat::RenderableType::OpenGLES) {
        info.fFormat = GR_GL_BGRA8;
    } else {
        info.fFormat = GR_GL_RGBA8;
    }
    GrBackendRenderTarget backend(w, h, window()->format().samples(), window()->format().stencilBufferSize(), info);
    // setup SkSurface
    // To use distance field text, use commented out SkSurfaceProps instead
    // SkSurfaceProps props(SkSurfaceProps::kUseDeviceIndependentFonts_Flag,
    //                      SkSurfaceProps::kLegacyFontHost_InitType);
    SkSurfaceProps props(SkSurfaceProps::kLegacyFontHost_InitType);

    m_dptr->gpuSurface = SkSurface::MakeFromBackendRenderTarget(m_dptr->context.get(), backend, kBottomLeft_GrSurfaceOrigin, colorType, nullptr, &props);
    if (!m_dptr->gpuSurface) {
        SkDebugf("SkSurface::MakeRenderTarget return null\n");
        return;
    }
}

void QSkiaQuickItem::onBeforeRendering()
{
    if (!isVisible()) {
        return;
    }
    if (!m_dptr->gpuSurface) {
        return;
    }
    auto canvas = m_dptr->gpuSurface->getCanvas();
    if (!canvas) {
        return;
    }
    const auto elapsed = m_dptr->lastTime.elapsed();
    m_dptr->lastTime = QTime::currentTime();
    auto rect = boundingRect().toRect();
    QOpenGLContext::currentContext()->functions()->glViewport(rect.x(), rect.y(), rect.width(), rect.height());
    canvas->save();
    qWarning() << "paint";
    this->draw(canvas, elapsed);
    canvas->restore();
    window()->resetOpenGLState();
}

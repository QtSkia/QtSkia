#include "QSkiaQuickItem.h"

#include "InnerItem_p.h"

#include "core/SkImageInfo.h"
#include "core/SkSurface.h"
#include "gpu/GrContext.h"
#include "src/gpu/gl/GrGLUtil.h"

#include <QOpenGLContext>
#include <QOpenGLFramebufferObject>
#include <QOpenGLFunctions>
#include <QResizeEvent>
#include <QTime>

class QSkiaQuickItemPrivate {
public:
    sk_sp<GrContext> context = nullptr;
    sk_sp<SkSurface> gpuSurface = nullptr;
    QTime lastTimeA;
    QTime lastTimeB;
    InnerItem innerItem;
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
        connect(win, &QQuickWindow::sceneGraphInitialized, this, &QSkiaQuickItem::onSGInited, Qt::DirectConnection);
        connect(win, &QQuickWindow::sceneGraphInvalidated, this, &QSkiaQuickItem::onSGUninited, Qt::DirectConnection);
        win->setClearBeforeRendering(false);
    }
}

void QSkiaQuickItem::onSGInited()
{
    qWarning() << __FUNCTION__;
    connect(window(), &QQuickWindow::beforeRendering, this, &QSkiaQuickItem::onBeforeRendering, static_cast<Qt::ConnectionType>(Qt::DirectConnection | Qt::UniqueConnection));
    connect(window(), &QQuickWindow::afterRendering, this, &QSkiaQuickItem::onAfterRendering, static_cast<Qt::ConnectionType>(Qt::DirectConnection | Qt::UniqueConnection));
    m_dptr->context = GrContext::MakeGL();
    SkASSERT(m_dptr->context);
    init(static_cast<int>(this->width()), static_cast<int>(this->height()));
    onInit(static_cast<int>(this->width()), static_cast<int>(this->height()));
    m_dptr->innerItem.setParentItem(window()->contentItem());
    m_dptr->lastTimeA = QTime::currentTime();
    m_dptr->lastTimeB = QTime::currentTime();
}

void QSkiaQuickItem::onSGUninited()
{
    qWarning() << __FUNCTION__;
    disconnect(window(), &QQuickWindow::beforeRendering, this, &QSkiaQuickItem::onBeforeRendering);
    disconnect(window(), &QQuickWindow::afterRendering, this, &QSkiaQuickItem::onAfterRendering);
}

void QSkiaQuickItem::init(int w, int h)
{
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

void QSkiaQuickItem::geometryChanged(const QRectF& newGeometry, const QRectF& oldGeometry)
{
    QQuickItem::geometryChanged(newGeometry, oldGeometry);
    if (newGeometry == oldGeometry) {
        return;
    }
    if (m_dptr->context && window() && isVisible() && window()->isSceneGraphInitialized()) {
        init(static_cast<int>(newGeometry.width()), static_cast<int>(newGeometry.height()));
//        window()->update();
    }
}


void QSkiaQuickItem::onBeforeRendering()
{
    if (!isVisible() || !window() || !window()->isSceneGraphInitialized()) {
        return;
    }
    if (!m_dptr->gpuSurface) {
        return;
    }
    auto canvas = m_dptr->gpuSurface->getCanvas();
    if (!canvas) {
        return;
    }
    qWarning() << __FUNCTION__;
    const auto elapsed = m_dptr->lastTimeA.elapsed();
    m_dptr->lastTimeA = QTime::currentTime();
    auto pos = mapToScene(position()).toPoint();
    auto rect =  boundingRect().toRect();
    QOpenGLContext::currentContext()->functions()->glViewport(pos.x(), pos.y(), rect.width(), rect.height());
    canvas->save();
    this->drawBeforeSG(canvas, elapsed);
    canvas->restore();
    window()->resetOpenGLState();
}

void QSkiaQuickItem::onAfterRendering()
{
    if (!isVisible() || !window() || !window()->isSceneGraphInitialized()) {
        return;
    }
    if (!m_dptr->gpuSurface) {
        return;
    }
    auto canvas = m_dptr->gpuSurface->getCanvas();
    if (!canvas) {
        return;
    }
    qWarning() << __FUNCTION__;
    const auto elapsed = m_dptr->lastTimeB.elapsed();
    m_dptr->lastTimeB = QTime::currentTime();
    auto pos = mapToScene(position()).toPoint();
    auto rect =  boundingRect().toRect();
    QOpenGLContext::currentContext()->functions()->glViewport(pos.x(), pos.y(), rect.width(), rect.height());
    canvas->save();
    this->drawAfterSG(canvas, elapsed);
    canvas->restore();
    window()->resetOpenGLState();
}

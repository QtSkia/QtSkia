#include "QSkiaQuickItem.h"

#include "core/SkImageInfo.h"
#include "core/SkSurface.h"
#include "gpu/GrContext.h"

#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QResizeEvent>
#include <QTime>
#include <QTimer>

class QSkiaQuickItemPrivate {
public:
    sk_sp<GrContext> context = nullptr;
    sk_sp<SkSurface> gpuSurface = nullptr;
    SkImageInfo info;
    QTime lastTime;
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
        connect(win, &QQuickWindow::beforeSynchronizing, this, &QSkiaQuickItem::sync, Qt::DirectConnection);
        connect(win, &QQuickWindow::sceneGraphInvalidated, this, &QSkiaQuickItem::cleanup, Qt::DirectConnection);
        win->setClearBeforeRendering(false);
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
    this->draw(canvas, elapsed);
    canvas->restore();
    window()->resetOpenGLState();
}

void QSkiaQuickItem::geometryChanged(const QRectF& newGeometry, const QRectF& oldGeometry)
{
    QQuickItem::geometryChanged(newGeometry, oldGeometry);
    if (newGeometry == oldGeometry) {
        return;
    }
    init(static_cast<int>(newGeometry.width()), static_cast<int>(newGeometry.height()));
    update();
}

void QSkiaQuickItem::sync()
{
    if (!m_dptr->context) {
        m_dptr->context = GrContext::MakeGL();
        if (!m_dptr->context) {
            SkDebugf("GrContext::MakeGL return null\n");
            return;
        }
        init(static_cast<int>(width()), static_cast<int>(height()));
        m_dptr->lastTime = QTime::currentTime();
        connect(window(), &QQuickWindow::beforeRendering, this, &QSkiaQuickItem::onBeforeRendering);
    }
}

void QSkiaQuickItem::cleanup()
{
    m_dptr->gpuSurface = nullptr;
    m_dptr->context = nullptr;
}

void QSkiaQuickItem::init(int w, int h)
{
    m_dptr->info = SkImageInfo::MakeN32Premul(w, h);
    m_dptr->gpuSurface = SkSurface::MakeRenderTarget(m_dptr->context.get(), SkBudgeted::kNo, m_dptr->info);
    if (!m_dptr->gpuSurface) {
        SkDebugf("SkSurface::MakeRenderTarget return null\n");
        return;
    }
}

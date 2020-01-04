#include "QSkiaQuickWindow.h"

#include "core/SkImageInfo.h"
#include "core/SkSurface.h"
#include "gpu/GrContext.h"

#include <QOpenGLFunctions>
#include <QTime>
#include <QTimer>
#include <QResizeEvent>
class QSkiaQuickWindowPrivate{
public:
    sk_sp<GrContext> context = nullptr;
    sk_sp<SkSurface> gpuSurface = nullptr;
    SkImageInfo info;
    QTime lastTimeA;
    QTime lastTimeB;
};

QSkiaQuickWindow::QSkiaQuickWindow(QWindow *parent)
    : QQuickWindow(parent)
    , m_dptr (new QSkiaQuickWindowPrivate)
{
    setClearBeforeRendering(false);
    connect(this, &QQuickWindow::sceneGraphInitialized, this, &QSkiaQuickWindow::onSGInited, Qt::DirectConnection);
    connect(this, &QQuickWindow::sceneGraphInvalidated, this, &QSkiaQuickWindow::onSGUninited, Qt::DirectConnection);
}

QSkiaQuickWindow::~QSkiaQuickWindow()
{
    delete m_dptr;
    m_dptr = nullptr;
}

void QSkiaQuickWindow::onSGInited()
{
    connect(this, &QQuickWindow::beforeRendering, this, &QSkiaQuickWindow::onBeforeRendering, static_cast<Qt::ConnectionType>(Qt::DirectConnection | Qt::UniqueConnection));
    connect(this, &QQuickWindow::afterRendering, this, &QSkiaQuickWindow::onAfterRendering, static_cast<Qt::ConnectionType>(Qt::DirectConnection));
    m_dptr->context = GrContext::MakeGL();
    SkASSERT(m_dptr->context);
    init(this->width(), this->height());
    m_dptr->lastTimeA = QTime::currentTime();
    m_dptr->lastTimeB = QTime::currentTime();
}

void QSkiaQuickWindow::onSGUninited()
{
    disconnect(this, &QQuickWindow::beforeRendering, this, &QSkiaQuickWindow::onBeforeRendering);
    disconnect(this, &QQuickWindow::afterRendering, this, &QSkiaQuickWindow::onAfterRendering);
    m_dptr->context = nullptr;
    m_dptr->gpuSurface = nullptr;
}
void QSkiaQuickWindow::init(int w, int h)
{
    m_dptr->info = SkImageInfo::MakeN32Premul(w, h);
    m_dptr->gpuSurface = SkSurface::MakeRenderTarget(m_dptr->context.get(), SkBudgeted::kNo, m_dptr->info);
    if (!m_dptr->gpuSurface) {
        SkDebugf("SkSurface::MakeRenderTarget return null\n");
        return;
    }
}

void QSkiaQuickWindow::resizeEvent(QResizeEvent *e)
{
    init(e->size().width(), e->size().height());
}

void QSkiaQuickWindow::onBeforeRendering()
{
    if (!this->isVisible()) {
        return;
    }
    if (!m_dptr->gpuSurface) {
        return;
    }
    auto canvas = m_dptr->gpuSurface->getCanvas();
    if (!canvas) {
        return;
    }
    const auto elapsed = m_dptr->lastTimeB.elapsed();
    m_dptr->lastTimeB = QTime::currentTime();
    canvas->save();
    this->drawBeforeSG(canvas, elapsed);
    canvas->restore();
}

void QSkiaQuickWindow::onAfterRendering()
{
    if (!this->isVisible()) {
        return;
    }
    if (!m_dptr->gpuSurface) {
        return;
    }
    auto canvas = m_dptr->gpuSurface->getCanvas();
    if (!canvas) {
        return;
    }
    const auto elapsed = m_dptr->lastTimeA.elapsed();
    m_dptr->lastTimeA = QTime::currentTime();
    canvas->save();
    this->drawAfterSG(canvas, elapsed);
    canvas->restore();
}


#include "QSkiaOpenGLWidget.h"

#include "core/SkImageInfo.h"
#include "core/SkSurface.h"
#include "gpu/GrContext.h"
#include "gpu/gl/GrGLInterface.h"

#include <QOpenGLFunctions>
#include <QTime>
#include <QTimer>
#include <QGuiApplication>
#include <QScreen>
#include <QDebug>
class QSkiaOpenGLWidgetPrivate {
public:
    QOpenGLFunctions funcs;
    sk_sp<GrGLInterface> glInterface = nullptr;
    sk_sp<GrContext> context = nullptr;
    sk_sp<SkSurface> gpuSurface = nullptr;
    SkImageInfo info;
    QTimer timer;
    QTime lastTime;
};
QSkiaOpenGLWidget::QSkiaOpenGLWidget(QWidget* parent)
    : QOpenGLWidget(parent)
    , m_dptr(new QSkiaOpenGLWidgetPrivate)
{
    connect(&m_dptr->timer, &QTimer::timeout, this, QOverload<>::of(&QSkiaOpenGLWidget::update));
    m_dptr->timer.start(1000 / qRound(qApp->primaryScreen()->refreshRate()));
}

QSkiaOpenGLWidget::~QSkiaOpenGLWidget()
{
    makeCurrent();
    delete m_dptr;
    m_dptr = nullptr;
    doneCurrent();
}

void QSkiaOpenGLWidget::initializeGL()
{
    m_dptr->funcs.initializeOpenGLFunctions();
    m_dptr->context = GrContext::MakeGL(m_dptr->glInterface);
    SkASSERT(m_dptr->context);
    init(this->width(), this->height());
    m_dptr->lastTime = QTime::currentTime();
}

void QSkiaOpenGLWidget::resizeGL(int w, int h)
{
    if (this->width() == w && this->height() == h) {
        return;
    }
    init(w, h);
}

void QSkiaOpenGLWidget::init(int w, int h)
{
    m_dptr->info = SkImageInfo::MakeN32Premul(w, h);
    m_dptr->gpuSurface = SkSurface::MakeRenderTarget(m_dptr->context.get(), SkBudgeted::kNo, m_dptr->info);
    if (!m_dptr->gpuSurface) {
        qDebug() << "SkSurface::MakeRenderTarget return null";
        return;
    }
    m_dptr->funcs.glViewport(0, 0, w, h);
}

void QSkiaOpenGLWidget::paintGL()
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
    const auto elapsed = m_dptr->lastTime.elapsed();
    m_dptr->lastTime = QTime::currentTime();
    canvas->save();
    this->draw(canvas, elapsed);
    canvas->restore();
}

#include "QSkiaQuickWindow.h"

#include "core/SkImageInfo.h"
#include "core/SkSurface.h"
#include "gpu/GrContext.h"
#include "src/gpu/gl/GrGLUtil.h"

#include <QDebug>
#include <QOpenGLContext>
#include <QOpenGLFramebufferObject>
#include <QOpenGLFunctions>
#include <QPropertyAnimation>
#include <QQuickItem>
#include <QQuickWindow>
#include <QResizeEvent>
#include <QTime>
#include <QTimer>
//InnerItem. 内部用的旋转动画Item，用来驱动QSkiaQuickWindow的渲染.
class InnerItem : public QQuickItem {
    Q_OBJECT
public:
    InnerItem(QQuickItem* parent = nullptr)
        : QQuickItem(parent)
    {
        setWidth(1);
        setHeight(1);
        m_animation.setTargetObject(this);
        m_animation.setPropertyName("rotation");
        m_animation.setStartValue(0);
        m_animation.setEndValue(360);
        m_animation.setDuration(1000);
        m_animation.setLoopCount(-1);
        connect(this, &QQuickItem::rotationChanged, this, &InnerItem::onAnimation);
        m_animation.start();
    }
protected slots:
    void onAnimation()
    {
        if (window() && window()->isSceneGraphInitialized()) {
            window()->update();
        }
    }

private:
    QPropertyAnimation m_animation;
};

class QSkiaQuickWindowPrivate {
public:
    sk_sp<GrContext> context = nullptr;
    sk_sp<SkSurface> gpuSurface = nullptr;
    QTime lastTimeA;
    QTime lastTimeB;
    InnerItem innerItem;
    std::atomic<bool> hasCleaned = false;
    std::atomic<bool> hasResize = false;
};

QSkiaQuickWindow::QSkiaQuickWindow(QWindow* parent)
    : QQuickWindow(parent)
    , m_dptr(new QSkiaQuickWindowPrivate)
{
    connect(this, &QQuickWindow::sceneGraphInitialized, this, &QSkiaQuickWindow::onSGInited, Qt::DirectConnection);
    connect(this, &QQuickWindow::sceneGraphInvalidated, this, &QSkiaQuickWindow::onSGUninited, Qt::DirectConnection);
    setClearBeforeRendering(false);
}

QSkiaQuickWindow::~QSkiaQuickWindow()
{
    qWarning() << __FUNCTION__;
    delete m_dptr;
    m_dptr = nullptr;
}

void QSkiaQuickWindow::onSGInited()
{
    qWarning() << __FUNCTION__;
    connect(this, &QQuickWindow::beforeRendering, this, &QSkiaQuickWindow::onBeforeRendering, static_cast<Qt::ConnectionType>(Qt::DirectConnection | Qt::UniqueConnection));
    connect(this, &QQuickWindow::afterRendering, this, &QSkiaQuickWindow::onAfterRendering, static_cast<Qt::ConnectionType>(Qt::DirectConnection | Qt::UniqueConnection));
    connect(this, &QQuickWindow::beforeSynchronizing, this, &QSkiaQuickWindow::onBeforeSync, static_cast<Qt::ConnectionType>(Qt::DirectConnection | Qt::UniqueConnection));

    //资源释放。
    //sceneGraphInvalidated 信号发出的时候，上下文已经没有了，来不及了。这里只能用sceneGraphAboutToStop。
    //sceneGraphAboutToStop在Window析构之前会发出，最小化之前也会发出。这里使用hasCleaned标记。
    //窗口直接关闭没有影响，最小化之后还原，则在beforeSync中重新创建Skia的上下文环境。
    //对还原速度略微有影响(PC上测试3毫秒左右，可以忽略)，暂无更好的方案。
    connect(
        this, &QQuickWindow::sceneGraphAboutToStop, this, [&]() {
            qWarning() << __FUNCTION__;
            if (m_dptr->context) {
                m_dptr->context = nullptr;
            }
            if (m_dptr->gpuSurface) {
                m_dptr->gpuSurface = nullptr;
            }
            m_dptr->hasCleaned = true;
        },
        static_cast<Qt::ConnectionType>(Qt::DirectConnection | Qt::UniqueConnection));
    //设置innerItem,驱动渲染循环
    m_dptr->innerItem.setParentItem(contentItem());

    m_dptr->context = GrContext::MakeGL();
    SkASSERT(m_dptr->context);
    init(this->width(), this->height());
    m_dptr->lastTimeA = QTime::currentTime();
    m_dptr->lastTimeB = QTime::currentTime();
    onInit(this->width(), this->height());
}

void QSkiaQuickWindow::onSGUninited()
{
    qWarning() << __FUNCTION__;
    disconnect(this, &QQuickWindow::beforeRendering, this, &QSkiaQuickWindow::onBeforeRendering);
    disconnect(this, &QQuickWindow::afterRendering, this, &QSkiaQuickWindow::onAfterRendering);
}

void QSkiaQuickWindow::init(int w, int h)
{
    //    auto info = SkImageInfo::MakeN32Premul(w, h);
    //    m_dptr->gpuSurface = SkSurface::MakeRenderTarget(m_dptr->context.get(), SkBudgeted::kNo, info);

    GrGLFramebufferInfo info;
    info.fFBOID = openglContext()->defaultFramebufferObject();
    SkColorType colorType;
    colorType = kRGBA_8888_SkColorType;
    if (format().renderableType() == QSurfaceFormat::RenderableType::OpenGLES) {
        info.fFormat = GR_GL_BGRA8;
    } else {
        info.fFormat = GR_GL_RGBA8;
    }
    GrBackendRenderTarget backend(w, h, format().samples(), format().stencilBufferSize(), info);
    // setup SkSurface
    // To use distance field text, use commented out SkSurfaceProps instead
    SkSurfaceProps props(SkSurfaceProps::kUseDeviceIndependentFonts_Flag,
        SkSurfaceProps::kLegacyFontHost_InitType);
    //    SkSurfaceProps props(SkSurfaceProps::kLegacyFontHost_InitType);

    m_dptr->gpuSurface = SkSurface::MakeFromBackendRenderTarget(m_dptr->context.get(), backend, kBottomLeft_GrSurfaceOrigin, colorType, nullptr, &props);

    if (!m_dptr->gpuSurface) {
        qDebug() << "SkSurface::MakeRenderTarget return null";
        return;
    }
    if (openglContext() && openglContext()->functions()) {
        openglContext()->functions()->glViewport(0, 0, w, h);
    }
}

void QSkiaQuickWindow::resizeEvent(QResizeEvent* e)
{
    if (e->size() == e->oldSize()) {
        e->accept();
        return;
    }
    if (isSceneGraphInitialized()) {
        m_dptr->hasResize = true;
    }
}
void QSkiaQuickWindow::onBeforeSync()
{
    if (m_dptr->hasResize || m_dptr->hasCleaned) {
        m_dptr->context = GrContext::MakeGL();
        SkASSERT(m_dptr->context);
        init(this->width(), this->height());
        m_dptr->hasCleaned = false;
        m_dptr->hasResize = false;
        onResize(this->width(), this->height());
    }
}
void QSkiaQuickWindow::timerEvent(QTimerEvent*)
{
    if (isVisible() && isSceneGraphInitialized()) {
        update();
    }
}

void QSkiaQuickWindow::onBeforeRendering()
{

    if (!this->isVisible() || !isSceneGraphInitialized()) {
        return;
    }

    if (!m_dptr->gpuSurface) {
        return;
    }
    auto canvas = m_dptr->gpuSurface->getCanvas();
    if (!canvas) {
        return;
    }
    //    qWarning() << __FUNCTION__;
    const auto elapsed = m_dptr->lastTimeB.elapsed();
    m_dptr->lastTimeB = QTime::currentTime();
    canvas->save();
    this->drawBeforeSG(canvas, elapsed);
    canvas->restore();
}

void QSkiaQuickWindow::onAfterRendering()
{
    if (!this->isVisible() || !isSceneGraphInitialized()) {
        return;
    }
    if (!m_dptr->gpuSurface) {
        return;
    }
    auto canvas = m_dptr->gpuSurface->getCanvas();
    if (!canvas) {
        return;
    }
    //    qWarning() << __FUNCTION__;
    const auto elapsed = m_dptr->lastTimeA.elapsed();
    m_dptr->lastTimeA = QTime::currentTime();
    canvas->save();
    this->drawAfterSG(canvas, elapsed);
    canvas->restore();
}
#include "QSkiaQuickWindow.moc"

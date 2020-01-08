#pragma once
#include "QtSkia_global.h"
#include <QQuickWindow>
#include <QPropertyAnimation>
#include <QQuickItem>
class SkCanvas;
class InnerItem : public QQuickItem {
    Q_OBJECT
public:
    InnerItem(QQuickItem *parent = nullptr) : QQuickItem(parent)
    {
        setWidth(1);
        setHeight(1);
        setX(-10);
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

class QSkiaQuickWindowPrivate;
class QtSkia_API QSkiaQuickWindow : public QQuickWindow {
    Q_OBJECT
public:
    QSkiaQuickWindow(QWindow *parent = nullptr);
    virtual ~QSkiaQuickWindow() override;
    //draw before SceneGraph. Note: this function work in SceneGraph Renderer Thread.
    virtual void drawBeforeSG(SkCanvas* canvas, int elapsed) = 0;
    //draw after SceneGraph. Note: this function work in SceneGraph Renderer Thread.
    virtual void drawAfterSG(SkCanvas* canvas, int elapsed) = 0;
protected slots:
    void onSGInited();
    void onSGUninited();
    void onBeforeRendering();
    void onAfterRendering();

protected:
    void init(int w, int h);
    void resizeEvent(QResizeEvent *) override;
    void timerEvent(QTimerEvent *) override;
private:
    QSkiaQuickWindowPrivate* m_dptr = nullptr;
};

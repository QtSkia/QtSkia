#pragma once
#include <QQuickItem>
#include <QPropertyAnimation>
#include <QQuickWindow>
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

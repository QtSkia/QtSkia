#pragma once
#include "QtSkia_global.h"
#include <QQuickItem>
#include <QQuickWindow>
class SkCanvas;
class QSkiaQuickItemPrivate;
class QtSkia_API QSkiaQuickItem : public QQuickItem {
    Q_OBJECT
public:
    QSkiaQuickItem(QQuickItem *parent = nullptr);
    virtual ~QSkiaQuickItem() override;
    virtual void onInit(int w, int h) = 0;
    //draw before SceneGraph. Note: this function work in SceneGraph Renderer Thread.
    virtual void drawBeforeSG(SkCanvas* canvas, int elapsed) = 0;
    //draw after SceneGraph. Note: this function work in SceneGraph Renderer Thread.
    virtual void drawAfterSG(SkCanvas* canvas, int elapsed) = 0;
protected:
    void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry) override;
    void init(int w, int h);
protected slots:
    void onSGInited();
    void onSGUninited();
    void onBeforeRendering();
    void onAfterRendering();
    void handleWindowChanged(QQuickWindow *win);
private:
    QSkiaQuickItemPrivate* m_dptr = nullptr;
};

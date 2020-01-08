#pragma once
#include "QtSkia_global.h"
#include <QQuickWindow>

class SkCanvas;
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

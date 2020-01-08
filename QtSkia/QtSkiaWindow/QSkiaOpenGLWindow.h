#pragma once
#include "QtSkia_global.h"
#include <QOpenGLWindow>
class SkCanvas;
class QSkiaOpenGLWindowPrivate;
class QtSkia_API QSkiaOpenGLWindow : public QOpenGLWindow {
    Q_OBJECT
public:
    QSkiaOpenGLWindow(QWindow *parent = nullptr);
    ~QSkiaOpenGLWindow() override;
    virtual void onInit(int w, int h) = 0;
    virtual void onResize(int w, int h) = 0;
    virtual void draw(SkCanvas* canvas, int elapsed = 16) = 0;
protected:
    virtual void initializeGL() override;
    virtual void resizeGL(int w, int h) override;
    virtual void paintGL() override;
    void init(int w, int h);

private:
    QSkiaOpenGLWindowPrivate* m_dptr = nullptr;
};

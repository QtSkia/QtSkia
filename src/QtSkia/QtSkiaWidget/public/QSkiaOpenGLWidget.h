#pragma once
#include "QtSkia_global.h"
#include <QOpenGLWidget>
class SkCanvas;
class QSkiaOpenGLWidgetPrivate;
class QtSkia_API QSkiaOpenGLWidget : public QOpenGLWidget {
    Q_OBJECT
public:
    QSkiaOpenGLWidget(QWidget* parent = nullptr);
    ~QSkiaOpenGLWidget() override;

    virtual void draw(SkCanvas* canvas, int elapsed = 16) {}

protected:
    virtual void initializeGL() override;
    virtual void resizeGL(int w, int h) override;
    virtual void paintGL() override;
    void init(int w, int h);

private:
    QSkiaOpenGLWidgetPrivate* m_dptr = nullptr;
};

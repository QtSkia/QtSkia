#pragma once
#include <QOpenGLWindow>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
class SkiaWindow : public QOpenGLWidget , public QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit SkiaWindow(QWidget *parent = nullptr);
    ~SkiaWindow() override;
protected:
    virtual void initializeGL() override;
    virtual void resizeGL(int w, int h) override;
    virtual void paintGL() override;
    void timerEvent(QTimerEvent *) override;
    void init(int w, int h);
private:
    int m_rotateAngle = 0;
};


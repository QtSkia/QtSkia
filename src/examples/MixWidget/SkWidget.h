#pragma once

//#include "QSkiaOpenGLWidget.h"
//class SkWidget : public QSkiaOpenGLWidget {
#include "QSkiaWidget.h"
class SkWidget : public QSkiaWidget {
    Q_OBJECT
public:
    virtual void draw(SkCanvas* canvas, int elapsed) override;
public slots:
    void moveRight() { x += 5; }
    void moveLeft() { x -= 5; }
    void moveUp() { y -= 5; }
    void moveDown() { y += 5; }
    void setSpeed(float speed)
    {
        m_rotateSpeed = speed;
    }

private:
    int x = 0;
    int y = 0;
    float m_rotateSpeed = 90.0f / 1000;
    int m_rotateAngle = 0;
};

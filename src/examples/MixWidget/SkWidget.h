#pragma once

#include "QSkiaWidget.h"
//#include "QSkiaOpenGLWidget.h"
class SkWidget : public QSkiaWidget {
//class SkWidget : public QSkiaOpenGLWidget {
    Q_OBJECT
public slots:
    void moveRight() { x+=5; }
    void moveLeft() { x-=5; }
    void moveUp() { y-=5; }
    void moveDown() { y+=5; }
    void setSpeed(float speed) {
        m_rotateSpeed = speed;
    }
public:
    virtual void draw(SkCanvas* canvas, int elapsed) override;

private:
    int x = 0;
    int y = 0;
    float m_rotateSpeed = 90.0f / 1000;
    int m_rotateAngle = 0;
};

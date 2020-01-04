#pragma once
class SkCanvas;
class SampleRender {
public:
    void draw(SkCanvas *canvas, int elapsed, int w, int h);
private:
    float m_rotateSpeed = 90.0f / 1000;
    int m_rotateAngle = 0;
};

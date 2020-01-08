#pragma once
#include "IRender.h"
class SkCanvas;

class SampleRender : public IRender{
public:
    void draw(SkCanvas *canvas, int elapsed, int w, int h) override;
private:
    float m_rotateSpeed = 90.0f / 1000;
    int m_rotateAngle = 0;
};

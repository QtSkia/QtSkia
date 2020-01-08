#pragma once
#include "IRender.h"
class SkCanvas;


class ComposeRender : public IRender
{
public:
    void draw(SkCanvas *canvas, int elapsed, int w, int h) override;
};


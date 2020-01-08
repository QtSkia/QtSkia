#pragma once
#include "IRender.h"

class ShapesRender : public IRender
{
public:

    // IRender interface
public:
    virtual void draw(SkCanvas *canvas, int elapsed, int w, int h) override;
};


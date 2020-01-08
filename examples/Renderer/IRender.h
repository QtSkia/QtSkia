#pragma once
class SkCanvas;
class IRender {
public:
    virtual ~IRender () = default;
    virtual void draw(SkCanvas *canvas, int elapsed, int w, int h) = 0;
};

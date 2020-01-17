#pragma once
class SkCanvas;
class IRender {
public:
    virtual ~IRender () = default;
    virtual void init(int w, int h) = 0;
    virtual void resize(int w, int h) = 0;
    virtual void draw(SkCanvas *canvas, int elapsed, int w, int h) = 0;
};

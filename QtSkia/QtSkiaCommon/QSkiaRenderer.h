#pragma once
class SkCanvas;
class IQSkiaRenderer {
public:
    virtual ~IQSkiaRenderer() = default;
    virtual void init(int w, int h) = 0;
    virtual void resize(int w, int h) = 0;
    virtual void draw(SkCanvas* canvas, int elapsed) = 0;
    virtual void cleanup() = 0;
};
#include "ShaderRender.h"

#include "effects/SkDashPathEffect.h"
#include "effects/SkDiscretePathEffect.h"
#include "effects/SkGradientShader.h"
static SkPath star()
{
    const SkScalar R = 115.2f, C = 128.0f;
    SkPath path;
    path.moveTo(C + R, C);
    for (int i = 1; i < 8; ++i) {
        SkScalar a = 2.6927937f * i;
        path.lineTo(C + R * cos(a), C + R * sin(a));
    }
    return path;
}

void ShaderRender::draw(SkCanvas* canvas, int elapsed, int w, int h)
{
    canvas->clear(SK_ColorWHITE);
    canvas->drawPath(path, paint);
    canvas->flush();
}

void ShaderRender::init(int w, int h)
{
    paint.setPathEffect(SkDiscretePathEffect::Make(10.0f, 4.0f));
    SkPoint points[2] = {
        SkPoint::Make(0.0f, 0.0f),
        SkPoint::Make(256.0f, 256.0f)
    };
    SkColor colors[2] = { SkColorSetRGB(66, 133, 244), SkColorSetRGB(15, 157, 88) };
    paint.setShader(SkGradientShader::MakeLinear(
        points, colors, nullptr, 2,
        SkTileMode::kClamp, 0, nullptr));
    paint.setAntiAlias(true);
    path = star();
}

void ShaderRender::resize(int w, int h)
{
}

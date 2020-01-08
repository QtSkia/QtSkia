#include "ShaderRender.h"

#include "core/SkCanvas.h"
#include "core/SkPaint.h"
#include "core/SkPath.h"
#include "effects/SkDiscretePathEffect.h"
#include "effects/SkDashPathEffect.h"
#include "effects/SkGradientShader.h"
static SkPath star() {
    const SkScalar R = 115.2f, C = 128.0f;
    SkPath path;
    path.moveTo(C + R, C);
    for (int i = 1; i < 8; ++i) {
        SkScalar a = 2.6927937f * i;
        path.lineTo(C + R * cos(a), C + R * sin(a));
    }
    return path;
}

void ShaderRender::draw(SkCanvas *canvas, int elapsed, int w, int h)
{
    SkPaint paint;
    paint.setPathEffect(SkDiscretePathEffect::Make(10.0f, 4.0f));
    SkPoint points[2] = {
        SkPoint::Make(0.0f, 0.0f),
        SkPoint::Make(256.0f, 256.0f)
    };
    SkColor colors[2] = {SkColorSetRGB(66,133,244), SkColorSetRGB(15,157,88)};
    paint.setShader(SkGradientShader::MakeLinear(
        points, colors, NULL, 2,
        SkTileMode::kClamp, 0, NULL));
    paint.setAntiAlias(true);
    canvas->clear(SK_ColorWHITE);
    SkPath path(star());
    canvas->drawPath(path, paint);
}

#include "SkWidget.h"
#include "core/SkCanvas.h"
#include "core/SkColor.h"
#include "core/SkPaint.h"
#include "core/SkRRect.h"
#include "core/SkFont.h"
void SkWidget::draw(SkCanvas* canvas, int elapsed)
{
    m_rotateAngle = int(elapsed * m_rotateSpeed + m_rotateAngle) % 360;
    canvas->clear(SK_ColorWHITE);
    SkRect rect = SkRect::Make(SkISize::Make(this->width(), this->height()));
    SkRRect rrect = SkRRect::MakeRectXY(rect, this->width() / 2, this->height() / 4);
    SkPaint paint;
    paint.setAntiAlias(true);
    paint.setARGB(128, 51, 76, 102);
    canvas->translate(x, y);
    canvas->drawRRect(rrect, paint);

    SkFont font;
    font.setSize(30);
    paint.setColor(SK_ColorRED);
    canvas->rotate(m_rotateAngle, this->width() / 2, this->height() / 2);
    canvas->drawString("Hello Skia", 600, 300, font, paint);

    canvas->flush();
}

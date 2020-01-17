#include "TextRender.h"
#include "core/SkFont.h"
#include "core/SkCanvas.h"
#include "core/SkPaint.h"
#include "core/SkFontMgr.h"
#include "core/SkTextBlob.h"
void TextRender::draw(SkCanvas *canvas, int elapsed, int w, int h)
{
    const char* fontFamily = nullptr;  // Default system family, if it exists.
    SkFontStyle fontStyle;  // Default is normal weight, normal width,  upright slant.
    sk_sp<SkFontMgr> fontManager = SkFontMgr::RefDefault();
    sk_sp<SkTypeface> typeface = fontManager->legacyMakeTypeface(fontFamily, fontStyle);

    SkFont font1(typeface, 64.0f, 1.0f, 0.0f);
    SkFont font2(typeface, 64.0f, 1.5f, 0.0f);
    font1.setEdging(SkFont::Edging::kAntiAlias);
    font2.setEdging(SkFont::Edging::kAntiAlias);

    // Note: MakeFromString may fail to produce exected results if the typeface
    // does not have glyphs for the characters in the string.  The characters
    // will not be kerned or shaped beyond a simple mapping from one Unicode
    // code point to one glyph with a default advance.
    sk_sp<SkTextBlob> blob1 = SkTextBlob::MakeFromString("Skia", font1);
    sk_sp<SkTextBlob> blob2 = SkTextBlob::MakeFromString("Skia", font2);

    SkPaint paint1, paint2, paint3;

    paint1.setAntiAlias(true);
    paint1.setColor(SkColorSetARGB(0xFF, 0x42, 0x85, 0xF4));

    paint2.setAntiAlias(true);
    paint2.setColor(SkColorSetARGB(0xFF, 0xDB, 0x44, 0x37));
    paint2.setStyle(SkPaint::kStroke_Style);
    paint2.setStrokeWidth(3.0f);

    paint3.setAntiAlias(true);
    paint3.setColor(SkColorSetARGB(0xFF, 0x0F, 0x9D, 0x58));

    canvas->clear(SK_ColorWHITE);
    canvas->drawTextBlob(blob1.get(), 20.0f, 64.0f,  paint1);
    canvas->drawTextBlob(blob1.get(), 20.0f, 144.0f, paint2);
    canvas->drawTextBlob(blob2.get(), 20.0f, 224.0f, paint3);
    canvas->flush();
}

void TextRender::init(int w, int h)
{

}

void TextRender::resize(int w, int h)
{

}

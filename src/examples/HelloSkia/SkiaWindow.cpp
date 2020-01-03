#include "SkiaWindow.h"

#include "core/SkData.h"
#include "core/SkImage.h"
#include "core/SkImageInfo.h"
#include "core/SkStream.h"
#include "core/SkSurface.h"
#include "core/SkFont.h"
#include "gpu/GrContext.h"
#include "gpu/gl/GrGLInterface.h"
#include "src/gpu/gl/GrGLUtil.h"
#include <QDebug>
static sk_sp<GrGLInterface> g_interface = nullptr;
static sk_sp<GrContext> g_context = nullptr;
static sk_sp<SkSurface> g_gpuSurface = nullptr;
static SkImageInfo g_info;
SkiaWindow::SkiaWindow(QWidget *parent)
    : QOpenGLWidget( parent)
{
    startTimer(1000 / 60);
}

SkiaWindow::~SkiaWindow()
{
    makeCurrent();
    g_gpuSurface = nullptr;
    g_context = nullptr;
    g_interface = nullptr;
    doneCurrent();
}

void SkiaWindow::timerEvent(QTimerEvent*)
{
    update();
}

void SkiaWindow::init(int w, int h)
{
    g_info = SkImageInfo::MakeN32Premul(this->width(), this->height());
    g_gpuSurface = SkSurface::MakeRenderTarget(g_context.get(), SkBudgeted::kNo, g_info);
    if (!g_gpuSurface) {
        SkDebugf("SkSurface::MakeRenderTarget return null\n");
        return;
    }
    glViewport(0, 0, w, h);
}
void SkiaWindow::initializeGL()
{
    initializeOpenGLFunctions();
    g_context = GrContext::MakeGL(g_interface);
    SkASSERT(g_context);
    init(this->width(), this->height());
//    GrGLint buffer;
//    GR_GL_GetIntegerv(g_interface.get(), GR_GL_FRAMEBUFFER_BINDING, &buffer);
//    GrGLFramebufferInfo info;
//    info.fFBOID = (GrGLint)buffer;

}

void SkiaWindow::resizeGL(int w, int h)
{
    init(w, h);
}

void SkiaWindow::paintGL()
{
    if (!g_gpuSurface) {
        return;
    }
    auto canvas = g_gpuSurface->getCanvas();
    if (!canvas) {
        return;
    }
    canvas->save();
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    m_rotateAngle = (1 + m_rotateAngle) % 360;
    SkPaint p;
    p.setAntiAlias(true);
    p.setColor(SK_ColorRED);
    p.setStrokeWidth(2.0f);
    canvas->clear(SK_ColorWHITE);
    SkFont font;
    font.setSize(30);
    canvas->rotate(m_rotateAngle, this->width() /2, this->height() /2);
    canvas->drawString("Hello Skia", 600, 300, font, p);
    canvas->drawLine(300, 300, 500, 500, p);
    canvas->restore();
    canvas->flush();
}

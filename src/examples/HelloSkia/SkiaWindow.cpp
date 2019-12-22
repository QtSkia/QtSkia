#include "SkiaWindow.h"

#include "core/SkImageInfo.h"
#include "gpu/GrContext.h"
#include "gpu/gl/GrGLInterface.h"
#include "src/gpu/gl/GrGLDefines.h"
#include "src/gpu/gl/GrGLGpu.h"

SkiaWindow::SkiaWindow(QWindow* parent)
    : QWindow(parent)
{

    // setup GrContext
    auto interface = GrGLMakeNativeInterface();

    // setup contexts
    sk_sp<GrContext> grContext(GrContext::MakeGL(interface));
    SkASSERT(grContext);

    // Wrap the frame buffer object attached to the screen in a Skia render target so Skia can
    // render to it
    GrGLint buffer;
    GR_GL_GetIntegerv(interface.get(), GR_GL_FRAMEBUFFER_BINDING, &buffer);
    GrGLFramebufferInfo info;
    info.fFBOID = (GrGLuint)buffer;
    SkColorType colorType;
}

void SkiaWindow::resize(int w, int h)
{
}

void SkiaWindow::show()
{
}

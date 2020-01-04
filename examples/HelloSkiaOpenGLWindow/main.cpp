#include <QGuiApplication>
#include "SkiaGLWindow.h"

int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);

    SkiaGLWindow win;
    win.resize(1024, 768);
    win.show();
    return app.exec();
}

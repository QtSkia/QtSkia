#include <QGuiApplication>
#include "SkiaQuickWindow.h"

int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);

    SkiaQuickWindow win;
    win.resize(1024, 768);
    win.show();
    return app.exec();
}

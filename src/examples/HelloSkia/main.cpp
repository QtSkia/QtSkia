#include <QGuiApplication>
#include "SkiaWindow.h"

int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);

    SkiaWindow win;
    win.resize(1024, 768);
    win.show();
    return app.exec();
}

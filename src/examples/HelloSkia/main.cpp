#include <QApplication>
#include "SkiaWindow.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    SkiaWindow win;
    win.resize(1024, 768);
    win.show();
    return app.exec();
}

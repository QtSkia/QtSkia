#include <QApplication>
#include "SkiaGLWidget.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    SkiaGLWidget win;
    win.resize(1024, 768);
    win.show();
    return app.exec();
}

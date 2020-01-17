#include <QGuiApplication>
#include <QQuickView>

#include "SkiaItem.h"
#include <QSurfaceFormat>
int main(int argc, char* argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    registerSkiaItem();

//    auto fmt = QSurfaceFormat::defaultFormat();
//    fmt.setSamples(4);
//    QSurfaceFormat::setDefaultFormat(fmt);
    QQuickView view;
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.setSource(QUrl("qrc:/main.qml"));
    view.show();
    return app.exec();
}

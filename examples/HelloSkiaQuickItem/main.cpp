#include <QGuiApplication>
#include <QQuickView>

#include "SkiaQuickItem.h"
int main(int argc, char* argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    qmlRegisterType<SkiaQuickItem>("SkiaQuickItem", 1, 0, "SkiaQuickItem");
    QQuickView view;
    view.setSource(QUrl("qrc:/main.qml"));
    view.show();
    return app.exec();
}

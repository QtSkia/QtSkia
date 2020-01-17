#include <QGuiApplication>
#include <QQuickView>
#include <QQmlContext>
#include "QSkiaLottieItem.h"
int main(int argc, char* argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QSkiaLottieItem::registerLottie();
    QQuickView view;
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.rootContext()->setContextProperty("resPath", resPath);
    view.setSource(QUrl("qrc:/main.qml"));
    view.show();
    return app.exec();
}

#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "gameoflifemodel.h"

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);

    qmlRegisterType<GameOfLifeModel>("GameOfLifeModel", 1, 0, "GameOfLifeModel");

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/GameOfLife/main.qml"_qs);
    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreated, &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl) QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}

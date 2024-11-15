#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include<QQmlContext>
#include"Blocks.h"
#include"TetrisMap.h"
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("tetris", "Main");

    // QPointer<TetrisMap> tetrisMap = new TetrisMap;
    // engine.rootContext()->setContextProperty("tetrisMap",tetrisMap);

    return app.exec();
}

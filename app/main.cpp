#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "managers/AppManager.hpp"

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    AppManager appManager;

    appManager.setContext(&engine);

    const QUrl url(QStringLiteral("qrc:/qt/qml/SimVital/main.qml"));
    engine.load(url);

    int exitCode = app.exec();

    return exitCode;
}
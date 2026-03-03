#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <thread>
#include <chrono>

#include "../core/include/MitBihParser.hpp"
#include "../core/include/RingBuffer.hpp"
#include "controllers/EcgController.hpp"

void fillBuffer(MitBihParser* parser, RingBuffer* buffer, std::atomic<bool>& flag) {
    while(!flag) {
        int val;

        // break if we run out of file data
        if (!parser->getNextVal(val)) break;

        // gets rid of a value to get data from only channel 1
        int dummyVal;
        if (!parser->getNextVal(dummyVal)) break;

        // keep trying to write the same value until there is space
        while (!buffer->write(val)) {

            // if the app is closed, exit the loop
            if (flag) return;

            // buffer is full, sleep for 5ms to let UI read some data
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
        }
    }
}

int main(int argc, char *argv[]) {
    std::atomic<bool> flag = false; // flag for shutdown sequence

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    
    MitBihParser parser;
    RingBuffer buffer(1024);

    std::string testFile = "data/100.dat";

    // loading data file
    if (!parser.loadFile(testFile)) {
        qDebug() << "Could not find file";
        return -1;
    }

    // creates a thread to fill buffer in the background so it does not interupt UI
    std::thread fillBufferThread(fillBuffer, &parser, &buffer, std::ref(flag));

    EcgController ecgController(&parser, &buffer);

    // put ecgController into global context so that QML files can see it
    engine.rootContext()->setContextProperty("ecgController", &ecgController);

    // telling the QML engine to load the main qml file
    const QUrl url(QStringLiteral("qrc:/qt/qml/SimVital/main.qml"));
    engine.load(url);

    int exitCode = app.exec();

    // shuts down thread before shutting down the app
    flag = true;
    fillBufferThread.join();

    return exitCode;
}
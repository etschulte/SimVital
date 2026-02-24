#include <QApplication>
#include <QLabel>

#include "../core/src/MitBihParser.hpp"
#include "../core/src/RingBuffer.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MitBihParser parser;
    RingBuffer buffer(1024);

    std::string testFile = "../data/100.dat";

    if (!parser.loadFile(testFile)) {
        qDebug() << "Could not find file";
        return -1;
    }

    while(true) {
        int val;

        if (!parser.getNextVal(val)) break;

        if (!buffer.write(val)) {
            qDebug() << "Successfully filled buffer to capacity";
            qDebug() << buffer.getCapacity();
            break;
        }

    }
    return 0;
}
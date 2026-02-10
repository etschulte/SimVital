#include <QApplication>
#include <QLabel>

#include "../core/src/MitBihParser.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MitBihParser parser;

    std::string testFile = "../data/100.dat";

    if (!parser.loadFile(testFile)) {
        qDebug() << "Could not find file";
        return -1;
    }

    int count = 0;
    while(count < 20) {
        int val;

        if (!parser.getNextVal(val)) break;

        qDebug() << "Sample" << count << ":" << val;
        count++;

    }
    return 0;
}
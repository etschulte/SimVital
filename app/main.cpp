#include <QApplication>
#include <QLabel>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QLabel label("SimVital");
    label.setAlignment(Qt::AlignCenter);
    label.resize(400, 300);
    label.show();

    return app.exec();
}
#include "MyMainWindow.h"
#include <QApplication>

int main(int argc, char **argv) {
    QApplication app (argc, argv);
    MyMainWindow mainWindow;
    mainWindow.resize(800, 500);

    mainWindow.show();
    return app.exec();
}

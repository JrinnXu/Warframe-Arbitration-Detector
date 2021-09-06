#include <QApplication>
#include "MainWindow.h"
#include <QStyleFactory>
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QResource::registerResource("warframe.rcc");
    QApplication::setQuitOnLastWindowClosed(false);
    MainWindow w = MainWindow();
    w.show();
    return QApplication::exec();
}

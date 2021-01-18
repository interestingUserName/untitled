#include "mainwindow.h"
#include <QApplication>

MainWindow* win;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    win = &w;
    w.show();
    return a.exec();
}

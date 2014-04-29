#include <QtGui/QApplication>
#include "mainwindow.h"
#include <iostream>

extern QString dirLocation;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if (a.arguments().count() != 2)
    {
      std::cerr << "You need to pass the absolute path to the directory containing the images\n" << endl;
      return 1;
    }

    dirLocation = a.arguments()[1];
    MainWindow w;

    w.setContextMenuPolicy(Qt::NoContextMenu);
    w.setWindowFlags(Qt::FramelessWindowHint);
    w.showMaximized();
    w.show();
    return a.exec();
}

#include "mainwindow.h"

#include <QApplication>
#include<QFile>
#include<QStringList>
#include<QString>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}

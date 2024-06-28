#include "mainwindow.h"
#include<QtGlobal>
#include <QApplication>
#include<QVBoxLayout>
#include<QLabel>
#include<QLineEdit>
#include<QPushButton>
#include<QString>
#include<QFile>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget window;
    window.setWindowTitle("Number Converter");
    QVBoxLayout layout(&window);
    QLabel inputLabel("Enter number:");
    QLineEdit input;
    layout.addWidget(&inputLabel);
    layout.addWidget(&input);
    QLabel resultLabel("Result:");
    QLineEdit result;
    result.setReadOnly(true);
    layout.addWidget(&resultLabel);
    layout.addWidget(&result);
    QPushButton convertButton("Convert");
     layout.addWidget(&convertButton);
    window.show();
    QObject::connect(&convertButton,&QPushButton::clicked,[&]()
    {
        qlonglong num=input.text().toLongLong();
        QString binary=QString::number(num,2);
         QString octal=QString::number(num,8);
         QString hex=QString::number(num,16);
         result.setText("Binary:"+binary+"\nOctal:"+octal+"\nHex"+hex);
    });
    QTextStream out(stdout);
    QString filename ="C:\\Documents\\1.txt";
    QFile fileIn{filename};
    QFile fileOut("C:\\Documents\\2.txt");
    if (!fileIn.exists()) {
        qWarning("The file does not exist");
    }
    if(fileIn.open(QIODevice::ReadOnly) && fileOut.open(QIODevice::WriteOnly)) {
        // Создаем объект класса QTextStream и передаем ему адрес объекта fileIn:
        QTextStream readStream(&fileIn);
        QString qstr;
        readStream>>qstr;
        // Создаем объект класса QTextStream и передаем ему адрес объекта fileOut:
        QTextStream writeStream(&fileOut);

        //запись строки в в файл:
        writeStream <<qstr;
        fileOut.close();
    }
    return a.exec();
}

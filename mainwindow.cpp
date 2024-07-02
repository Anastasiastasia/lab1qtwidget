#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"QString"
#include "QKeyEvent"
#include "QComboBox"
#include<QTextStream>
#include "dialog.h"
#include"QCheckBox"
#include<QFile>
#include <algorithm>
#include <string>
using namespace std;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label->setText("Insert number");
    //QFont font;
    //создать шрифт, высоту-  10 пикселей
    //  QFont font( "Arial", 10);
    QFont font( "Cursive", 10, QFont::Bold);
        // QFont font( "Cursive", 10);
    //QFont font( "helvetica", 40 );
    //QFont font= QFont("SansSerif");
    font.setPointSize(20); // размер шрифта
    // Установить цвет текста:
    ui->label->setStyleSheet("color:blue;");

    ui->label->setFixedHeight(30);//высота поля label
    ui->label->setFixedWidth(100);//ширина поля label
    //размещение текста:
    ui->label->setAlignment(Qt::AlignTop | Qt::AlignCenter);
    QFile fileIn("D:\\1.txt");
    if (!fileIn.open(QIODevice::ReadOnly|QIODevice::Text)) {
        qWarning("The file does not exist");
        return;
    }
    QTextStream in(&fileIn);
    while(!in.atEnd())
    {
        QString line=in.readLine();
        ui->comboBox->addItem(line);
    }
    fileIn.close();


}
void MainWindow::keyPressEvent(QKeyEvent *e)
{
    QString oldText = ui->label->text();
    // e->accept();
    int key=e->key();

    QString str = QString(QChar(key));
    //выводит символ клаиши и код клвиши:
    ui->label->setText(str+"-"+QString::number(key));

    if (key==Qt::Key_Backspace) { //BackSpace стирает символ
        ui->label->setText(oldText.left(oldText.length()-1));
    }
    else if (key==Qt::Key_Delete) { //Delete стирает всё
        ui->label->setText("");
    }
    if (key==Qt::Key_NumLock) {
        ui->label->setText("NumLock");
    }
    if (key==Qt::Key_Enter) {
        ui->label->setText("Enter");
    }
    if (key==Qt::Key_CapsLock) {
        ui->label->setText("CapsLock");
    }
    if(e->modifiers() & Qt::ControlModifier)
    {
        ui->label->setText("Ctrl");
    }
    if(e->modifiers() & Qt::ShiftModifier)
    {
        ui->label->setText("Shift");
    }
    if(e->modifiers() & Qt::AltModifier)
    {
        ui->label->setText("Alt");
    }

    switch (e->key()) {
    case Qt::Key_Up:
        ui->label->setText("вверх");
        break;
    case Qt::Key_Down:
        ui->label->setText("вниз");
        break;
    case Qt::Key_Left:
        ui->label->setText("<-");
        break;
    case Qt::Key_Right:
        ui->label->setText("->");
        break;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_pushButton_clicked()
{

   if(ui->checkBox->isChecked())//если 10с/с

      {
        qlonglong num;
            QString S1=ui->textEdit->toPlainText();
            num=S1.toInt();
            QString binary=QString::number(num,2);
        QString octal=QString::number(num,8);
        QString hex=QString::number(num,16);
        ui->textEdit_2->setText("Binary:"+binary+"\nOctal:"+octal+"\nHex:"+hex);
      }
        if(ui->checkBox_2->isChecked())//если 2 с/с
        {
          qlonglong num;
          QString S1=ui->textEdit->toPlainText();
          num=S1.toInt();
          qlonglong decimalNumber = 0;
          int power = 0;
          while (num > 0)
          {
              qlonglong remainder = num % 10;
              decimalNumber += remainder * pow(2, power);
              num /= 10;
              power++;
          }
          QString norm=QString::number(decimalNumber,10);
          QString octal=QString::number( decimalNumber,8);
          QString hex=QString::number(decimalNumber,16);
        ui->textEdit_2->setText("Dec:"+norm+"\nOctal:"+octal+"\nHex:"+hex);
        }
         if(ui->checkBox_3->isChecked())//если 8с/с
        {
            QString S1=ui->textEdit->toPlainText();

                  qlonglong decimalNumber = 0;
                int power = 0;

   // Convert octal number to decimal number
   for (int i = S1.length() - 1; i >= 0; i--)
   {
    int digit = S1[i].digitValue();
    decimalNumber += digit * qPow(8, power);
    power++;
    }
   QString norm=QString::number(decimalNumber,10);
   QString binary=QString::number( decimalNumber,2);
   QString hex=QString::number(decimalNumber,16);
    ui->textEdit_2->setText("Dec:"+norm+"\nBinary:"+binary+"\nHex:"+hex);
     }
    if(ui->checkBox_4->isChecked())//если 16 с/с
    {
         QString S1=ui->textEdit->toPlainText();
         qlonglong decimalNumber=S1.toLongLong(nullptr,16);
          QString norm=QString::number(decimalNumber,10);
        QString binary=QString::number( decimalNumber,2);
         QString octal=QString::number( decimalNumber,8);
        ui->textEdit_2->setText("Norm:"+norm+"\nBinary:"+binary+"\nOctal:"+octal);

    }
}




void MainWindow::on_pushButton_2_clicked()
{
    QString text=ui->comboBox->currentText();
    ui->textEdit->setText(text);
}

void MainWindow::on_pushButton_3_clicked()
{
    QFile file("D:\\2.txt");
    if (!file.open(QIODevice::WriteOnly|QIODevice::Text)) {
        qWarning("The file2 does not exist");
        return;
    }

    QTextStream out(&file);

    while(!out.atEnd())
    {
        QString text=ui->textEdit_2->toPlainText();
        out<<text;

    }

    file.close();
}


void MainWindow::on_pushButton_4_clicked()
{
    //создание модального окна:
    Dialog dlg;
    dlg.setModal(true);
    dlg.exec();
}


void MainWindow::on_pushButton_5_clicked()
{
    QPalette pal;
        //установить желтый цвет фона вокруг текста
    pal.setColor(ui->label->backgroundRole(), Qt::yellow);
    //установки цветов RGBA (то есть цвета RGB со значением Alpha для прозрачности)
    //pal.setColor(ui->label->backgroundRole(),QColor(255, 100, 100, 255));
    // включить цвет фона:
    ui->label->setAutoFillBackground(true) ;
    // установить синий цвет текста:
    pal.setColor(ui->label->foregroundRole(), Qt::blue);


    // установить желтый цвет фона вокруг текста, используя QBrush:
    // CrossPattern -  заливка решёткой (клеткой):
    pal.setBrush(QPalette::Window, QBrush(QColor(255, 255, 100, 255), Qt::CrossPattern));
    ui->label->setPalette(pal);
}
void MainWindow::on_checkBox_clicked()
{


}


void MainWindow::on_checkBox_2_clicked()
{

}


void MainWindow::on_checkBox_4_clicked()
{

}


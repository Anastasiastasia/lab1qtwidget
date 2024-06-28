#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QColorDialog"
#include "QKeyEvent"
#include <QMessageBox>
#include "dialog.h"
#include "QString"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

        // заполнение элементами ComboBox
        // 1 способ:
    for(int i = 0; i < 5; i++)
    {
        ui->comboBox->addItem("Element " + QString::number(i));
    }
ui->label->setText("TEXT");
    QFont font( "Cursive", 10, QFont::Bold);
font.setPointSize(20);
    ui->label->setStyleSheet("color:red;");
ui->label->setFixedHeight(30);
 ui->label->setFixedWidth(100);
 ui->label->setAlignment(Qt::AlignTop | Qt::AlignCenter);
 ui->label->setContentsMargins(1, 1, 2, 2);
 this->setContextMenuPolicy(Qt::CustomContextMenu);

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

void MainWindow::on_pushButton_1_clicked()
{
    QColorDialog *dialog = new QColorDialog(this);
    QColor color=  dialog->getColor();
    QVariant variant= color;
    QString colcode = variant.toString();
    // установка выбранного цвета для текста и зеленый (хаки) для фона:
    ui->label->setStyleSheet("QLabel { background-color :rgb(100, 100, 0) ; color :"+colcode+"; }");
}
void MainWindow::on_pushButton_2_clicked()
{
    // убрать настройки цвета фона и текста для label
    ui->label->setStyleSheet("*");
    // 2 способ, используя палитру:
    QPalette pal;
    //установить желтый цвет фона вокруг текста
    pal.setColor(ui->label->backgroundRole(), Qt::yellow);
    //установки цветов RGBA (то есть цвета RGB со значением Alpha для прозрачности)
    //pal.setColor(ui->label->backgroundRole(),QColor(255, 100, 100, 255));
    // включить цвет фона:
    ui->label->setAutoFillBackground(true) ;
    // установить синий цвет текста:
    pal.setColor(ui->label->foregroundRole(), Qt::blue);
    // установить цвет красный  текста (2 способ):
    //  pal.setColor (QPalette::WindowText, Qt::red);

    // установить желтый цвет фона вокруг текста, используя QBrush:
    // CrossPattern -  заливка решёткой (клеткой):
    pal.setBrush(QPalette::Window, QBrush(QColor(255, 255, 100, 255), Qt::CrossPattern));
    // SolidPattern -  сплошная заливка :
    // pal.setBrush(QPalette::Window, QBrush(QColor(255, 255, 100, 255), Qt::SolidPattern));
    ui->label->setPalette(pal);
}


void MainWindow::on_MainWindow_customContextMenuRequested(const QPoint &pos)
{
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    QMenu *pMenu = new QMenu(this);

    QAction * pNewTask = new QAction (tr ("Элемент 1"), this);
    QAction * pEditTask = new QAction (tr ("Элемент 1"), this);
    // Для текста на английском:
    //QAction * pEditTask= new QAction ("Удуьуте 2", this);

    pNewTask->setData(1);
    pEditTask->setData(2);

    // Добавить объект QAction в меню
    pMenu->addAction(pNewTask);
    pMenu->addAction(pEditTask);
        // Подключаем сигнал правой кнопки мыши
    connect(pNewTask, SIGNAL(triggered()), this, SLOT(onTaskBoxContextMenuEvent()));
    connect(pEditTask, SIGNAL(triggered()), this, SLOT(onTaskBoxContextMenuEvent()));

    // Отображение меню по правому клику мыши
    pMenu->exec(cursor().pos());

    // Освободить память
    QList<QAction*> list = pMenu->actions();
    foreach (QAction* pAction, list) delete pAction;
    delete pMenu;
}
void MainWindow::onTaskBoxContextMenuEvent()
{
    // this-> sender () является сигнализатором QAction:
    QAction * pEven = qobject_cast <QAction *> (this-> sender ());

    // Получить тип отправляемой информации (1 или 2) ( 1: Элемент 1 2: Элемент 2)
    int iType = pEven->data().toInt();

    switch (iType)
    {
    case 1:
        //устанавливает заголовки и выводится текст из pEven
        QMessageBox::about(this, "Element 1", pEven->text());
        break;
    case 2:
        QMessageBox::about(this, "Element 2", pEven->text());
        break;
    default:
        break;
    }
}



void MainWindow::on_pushButton_3_clicked()
{
        //создание модального окна:
        Dialog dlg;
        dlg.setModal(true);
        dlg.exec();

}


void MainWindow::on_pushButton_4_clicked()
{
    //чтение из текстового пoля нового элемента для списка и
    // добавление в список этого элемента

    QString val=(ui->textEdit)->toPlainText();
    if (val!="")
        ui->comboBox->addItem(val);
}


void MainWindow::on_pushButton_5_clicked()
{

    //вывод в текстовой поле текущего элемента (выбранного) из списка
    ui->textEdit->setText(ui->comboBox->currentText());

}


#include "QtWidgetsApplication1.h"
#include<qpushbutton.h>
#include<qdebug.h>
#include<qopengltexture.h>
#include<qimage.h>
QtWidgetsApplication1::QtWidgetsApplication1(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::QtWidgetsApplication1Class())
{
    ui->setupUi(this);
    this->sqlpage = new sqlclass;
    loginUI();
}

QtWidgetsApplication1::~QtWidgetsApplication1()
{
    delete ui;
}
void QtWidgetsApplication1::loginUI()
{
   connect(ui->login, &QPushButton::clicked, this, &QtWidgetsApplication1::login);
 }

void QtWidgetsApplication1::login()
{
    inputid = ui->idEdit->text();
    inputpassword = ui->passwordEdit->text();
    sqlpage->id = inputid;
    bool r;
    r=SqliteOperator::getInstance()->login(inputid, inputpassword);
    if (r)
    {
        sqlpage->show();
        this->close();
    }
    else
    {
        QMessageBox::warning(this, "错误", "请重新输入",QMessageBox::Close);
    }
}
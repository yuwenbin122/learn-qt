#include "addUIClass.h"
#include<qpushbutton.h>
#include<qdebug.h>
addUIClass::addUIClass(QMainWindow*parent)
	: QMainWindow(parent),ui(new Ui::addUIClassClass())
{
	ui->setupUi(this);
    adduser();
}

addUIClass::~addUIClass()
{
    delete ui;
}
void addUIClass::adduser()
{
   
    ui->idEdit->clear();
    ui->userNameEdit->clear();
    ui->passWordEdit->clear();
    ui->nameEdit->clear();
    ui->modelEdit->clear();
    connect(ui->pushButton, &QPushButton::clicked, this, &addUIClass::add1);
}
void addUIClass::add1()
{
    sid = ui->idEdit->text();
    for (auto it : sid)
    {
        if (it < "0" || it>"9")
        {
            QMessageBox::warning(this, "错误", "学号输入错误", QMessageBox::Close);
        }
    }
     susername = ui->userNameEdit->text();
     spassword = ui->passWordEdit->text();
     sname = ui->nameEdit->text();
     smodel = ui->modelEdit->text();

    QStringList l = { sid ,susername,spassword,sname,smodel};
    QVector<QStringList>v;
    v.push_back(l);
    l.clear();
    bool ret;
    ret=SqliteOperator::getInstance()->AddUser(v);
    v.clear();
    if (ret)
    {
        QMessageBox::information(this, "提示", "添加成功", QMessageBox::Ok);
        this->close();
        is = 1;
    }
    else is = 0;
}


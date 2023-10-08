#include "addBookClass.h"
#include<qmessagebox.h>

addBookClass::addBookClass(QWidget *parent)
	: QMainWindow(parent),ui(new Ui::addBookClassClass())
{
	ui->setupUi(this);
    addBook();
}

addBookClass::~addBookClass()
{}
void addBookClass::addBook()
{

    ui->bookNameEdit->clear();
    ui->articleEdit->clear();
    ui->typeEdit->clear();
    ui->numbEdit->clear();
    ui->localEdit->clear();
    connect(ui->pushButton, &QPushButton::clicked, this, &addBookClass::add1);
}
void addBookClass::add1()
{
    QString bookName = ui->bookNameEdit->text();
    QString articleName = ui->articleEdit->text();
    QString type = ui->typeEdit->text();
    QString local = ui->localEdit->text();
    QString numb = ui->numbEdit->text();
    QString rest = numb;
    QStringList l = { bookName ,articleName,type,local,numb,rest };
    QVector<QStringList>v;
    v.push_back(l);
    l.clear();
    bool ret;
    ret = SqliteOperator::getInstance()->AddBooks(v);
    v.clear();
    if (ret)
    {
        QMessageBox::information(this, "提示", "添加成功", QMessageBox::Ok);
        this->close();  
    }
}
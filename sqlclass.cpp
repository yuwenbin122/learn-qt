#include "sqlclass.h"


sqlclass::sqlclass(QWidget *parent)
	: QMainWindow(parent), ui(new Ui::sqlclassClass()),usersManagePage(nullptr)
{
	ui->setupUi(this);
    intPage();
}

sqlclass::~sqlclass()
{
    delete ui;
}
void sqlclass::intPage()
{
    usersManagePage = new usersManageClass(this);
    bookPage = new bookClass(this);
    tablePage = new tableClass(this);
    ui->stackedWidget->addWidget(usersManagePage);
    ui->stackedWidget->addWidget(bookPage);
    ui->stackedWidget->addWidget(tablePage);
    ui->stackedWidget->setCurrentIndex(0);
    connect(ui->userManage, &QToolButton::clicked, this, &sqlclass::turnPage1);
    connect(ui->bookManage, &QToolButton::clicked, this, &sqlclass::turnPage2);
    connect(ui->tableManage, &QToolButton::clicked, this, &sqlclass::turnPage3);
}
void sqlclass::turnPage1()
{
    ui->stackedWidget->setCurrentIndex(0);
}
void sqlclass::turnPage2()
{
    bookPage->nowid = id;
    ui->stackedWidget->setCurrentIndex(1);
}
void sqlclass::turnPage3()
{
    ui->stackedWidget->setCurrentIndex(2);
}

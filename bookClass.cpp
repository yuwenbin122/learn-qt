#include "bookClass.h"

bookClass::bookClass(QWidget *parent)
	: QWidget(parent),ui(new Ui::bookClassClass())
{
	ui->setupUi(this);
    this->addPage = new addBookClass;
    ui->tableView->setModel(&m_model);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_model.setHorizontalHeaderLabels(QStringList{ "书名","作者","类型","位置","总本书","剩余"});
    QList<QStandardItem*>items;
    items.append(new QStandardItem());
    bookui();
}

bookClass::~bookClass()
{}
void bookClass::bookui(QString condition)
{
    connect(ui->borrowBook, & QPushButton::clicked, this, & bookClass::borrowbook);
    connect(ui->returnBook, &QPushButton::clicked, this, &bookClass::returnbook);
    connect(ui->bookDelete, &QPushButton::clicked, this, &bookClass::deletebook);
    connect(ui->newButton, &QPushButton::clicked, this, &bookClass::newpage);
    connect(ui->lineEdit, &QLineEdit::textChanged, this, &bookClass::searchbook);
    connect(ui->bookAdd, &QPushButton::clicked, this, &bookClass::turnPage);
    auto l = SqliteOperator::getInstance()->getBook(condition);
    m_model.clear();
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_model.setHorizontalHeaderLabels(QStringList{ "书名","作者","类型","位置","总本书","剩余" });
    for (int i = 0; i < l.size(); i++)
    {
        QList<QStandardItem*>items;
        for (int j = 0; j < l[i].size(); j++)
        {
            items.append(new QStandardItem(l[i][j]));
        }
        m_model.appendRow(items);
    }

}
void bookClass::returnbook()
{
    int r = ui->tableView->currentIndex().row();
    if (r!=-1)
    {
        auto id = ui->tableView->model()->index(r, 0).data().toString();
        SqliteOperator::getInstance()->returnBooks(id,nowid);
        bookui();
    }
}
void bookClass::borrowbook()
{
    int r = ui->tableView->currentIndex().row();
    if (r!=-1)
    {
        auto id = ui->tableView->model()->index(r, 0).data().toString();
        SqliteOperator::getInstance()->borrowBooks(id, nowid);
        bookui();
    }
}

void bookClass::turnPage()
{
    addPage->show();
    addPage->addBook();
}
void bookClass::newpage()
{
    bookui();
}
void bookClass::searchbook()
{
    QString arg1;
    arg1 = ui->lineEdit->text();
    QString str = QString("where bookname like '%%1%'").arg(arg1);
    bookui(str);
}
void bookClass::deletebook()
{
    int r = ui->tableView->currentIndex().row();
    if (r!=-1)
    {
        auto id = ui->tableView->model()->index(r, 0).data().toString();
        SqliteOperator::getInstance()->deleteBooks(id);
        bookui();
    }
}
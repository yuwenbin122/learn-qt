#include "tableClass.h"

tableClass::tableClass(QWidget *parent)
	: QWidget(parent),ui(new Ui::tableClassClass())
{
	ui->setupUi(this);
    ui->tableView->setModel(&m_model);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_model.setHorizontalHeaderLabels(QStringList{ "用户名","书名","借书时间","还书时间"});
    QList<QStandardItem*>items;
    items.append(new QStandardItem());
    inint();
}

tableClass::~tableClass()
{}
void tableClass::inint(QString condition)
{
    auto l = SqliteOperator::getInstance()->getTrace(condition);
    m_model.clear();
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_model.setHorizontalHeaderLabels(QStringList{ "用户名","书名","借书时间","还书时间" });
    for (int i = 0; i < l.size(); i++)
    {
        QList<QStandardItem*>items;
        for (int j = 0; j < l[i].size(); j++)
        {
            items.append(new QStandardItem(l[i][j]));
        }
        m_model.appendRow(items);
    }
    connect(ui->newButton, &QPushButton::clicked, this, &tableClass::in);
    connect(ui->clearButton, &QPushButton::clicked, this, &tableClass::tableClear);
    connect(ui->lineEdit, &QLineEdit::textChanged, this, &tableClass::searchRecord);
}
void tableClass::in()
{
    inint();
}
void tableClass::tableClear()
{
    SqliteOperator::getInstance()->clearRecord();
    inint();
}
void tableClass::searchRecord()
{
    QString arg1;
    arg1 = ui->lineEdit->text();
    QString str = QString("where userName like '%%1%'").arg(arg1);
    inint(str);
}

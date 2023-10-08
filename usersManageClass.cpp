#include "usersManageClass.h"

usersManageClass::usersManageClass(QWidget *parent)
	: QWidget(parent),ui(new Ui::usersManageClassClass())
{
	ui->setupUi(this);
    this->addPage = new addUIClass;
    ui->tableView->setModel(&m_model);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_model.setHorizontalHeaderLabels(QStringList{ "学号","用户名","密码","姓名","权限" });
    QList<QStandardItem*>items;
    items.append(new QStandardItem());
    addui();
}

usersManageClass::~usersManageClass()
{}
void usersManageClass::addui(QString condition)
{
    connect(ui->usersAdd, &QPushButton::clicked, this, &usersManageClass::turnPage);
    connect(ui->usersDelete, &QPushButton::clicked, this, &usersManageClass::delteusers);
    connect(ui->lineEdit, &QLineEdit::textChanged, this, &usersManageClass::searchuser);
    connect(ui->newButton, &QPushButton::clicked, this, &usersManageClass::inint);
    auto l = SqliteOperator::getInstance()->getUser(condition);
    m_model.clear();
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_model.setHorizontalHeaderLabels(QStringList{ "学号","用户名","密码","姓名","权限" });

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
void usersManageClass::turnPage()
{  
    addPage->show(); 
    addPage->adduser(); 
    
}
void usersManageClass::delteusers()
{
    int r = ui->tableView->currentIndex().row();
    if(r!=-1)
    {
        auto id = ui->tableView->model()->index(r, 1).data().toString();
       SqliteOperator::getInstance()->deleteUser(id);
       addui();
    }
  
}
void usersManageClass::searchuser()
{
    QString arg1;
    arg1=ui->lineEdit->text();
    QString str = QString("where username like '%%1%'").arg(arg1);
    addui(str);
}
void usersManageClass::inint()
{
    
    addui();
}

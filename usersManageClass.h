#pragma once

#include <QWidget>
#include "ui_usersManageClass.h"
#include<qstandarditemmodel.h>
#include<addUIClass.h>
QT_BEGIN_MOC_NAMESPACE
namespace Ui { class usersManageclass; };
QT_END_NAMESPACE
class usersManageClass : public QWidget
{
	Q_OBJECT

public:
	usersManageClass(QWidget *parent = nullptr);
	~usersManageClass();
    addUIClass* addPage=NULL;
    void addui(QString conditon="");
public slots:
    void turnPage();
    void delteusers();
    void searchuser();
    void inint();
private:
	Ui::usersManageClassClass *ui;
    QStandardItemModel m_model;
    
};

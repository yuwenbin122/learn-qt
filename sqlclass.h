#pragma once

#include <QMainWindow>
#include<usersManageClass.h>
#include<bookClass.h>
#include<tableClass.h>
#include "ui_sqlclass.h"
QT_BEGIN_MOC_NAMESPACE
namespace Ui { class sqlclass; };
QT_END_NAMESPACE
class sqlclass : public QMainWindow
{
	Q_OBJECT

public:
	sqlclass(QWidget *parent = nullptr);
	~sqlclass();
    void intPage();
    void turnPage1();
    void turnPage2();
    void turnPage3();
    QString id;
private:
	Ui::sqlclassClass *ui;
    usersManageClass* usersManagePage;
    bookClass* bookPage;
    tableClass* tablePage;
};

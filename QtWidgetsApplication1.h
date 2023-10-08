#pragma once

#include <QtWidgets/QMainWindow>
#include<sqlclass.h>
#include<qsqldatabase.h>
#include<qsqlquery.h>
#include<qsqlerror.h>
#include<qdebug.h>
#include<qsqldatabase.h>
#include<qsqlrecord.h>
#include<SqliteOperator.h>
#include<qmessagebox.h>
#include "ui_QtWidgetsApplication1.h"
QT_BEGIN_MOC_NAMESPACE
namespace Ui { class QtWidgetsApplication1Class; };
QT_END_NAMESPACE
class QtWidgetsApplication1 : public QMainWindow
{
    Q_OBJECT

public:
    QtWidgetsApplication1(QWidget *parent = nullptr);
    ~QtWidgetsApplication1();
    sqlclass* sqlpage=NULL;
    
    void loginUI();
    QString inputid;
    QString inputpassword;
public slots:
    void login();
private:
    Ui::QtWidgetsApplication1Class *ui;

};

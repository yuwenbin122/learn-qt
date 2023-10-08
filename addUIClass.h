#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_addUIClass.h"
#include<qmessagebox.h>
#include<SqliteOperator.h>

QT_BEGIN_MOC_NAMESPACE
namespace Ui { class addUIclass; };
QT_END_NAMESPACE

class addUIClass : public QMainWindow
{
	Q_OBJECT

public:
	addUIClass(QMainWindow*parent = nullptr);
	~addUIClass();
    void adduser();
    QString sid;
    QString susername;
    QString spassword;
    QString sname;
    QString smodel;
    bool is;
    bool panduan();
public slots:
    void add1();
private:
	Ui::addUIClassClass *ui;
    
};

#pragma once

#include <QMainWindow>
#include "ui_addBookClass.h"
#include<SqliteOperator.h>
QT_BEGIN_MOC_NAMESPACE
namespace Ui { class addBookClass; };
QT_END_NAMESPACE
class addBookClass : public QMainWindow
{
	Q_OBJECT

public:
	addBookClass(QWidget *parent = nullptr);
	~addBookClass();
    void addBook();
public slots:
    void add1();
private:
	Ui::addBookClassClass *ui;
};

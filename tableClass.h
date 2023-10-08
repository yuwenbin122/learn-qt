#pragma once

#include <QWidget>
#include "ui_tableClass.h"
#include<qstandarditemmodel.h>
#include<SqliteOperator.h>
QT_BEGIN_MOC_NAMESPACE
namespace Ui { class tableclass; };
QT_END_NAMESPACE
class tableClass : public QWidget
{
	Q_OBJECT

public:
	tableClass(QWidget *parent = nullptr);
	~tableClass();
    void inint(QString conditon = "");
public slots:
    void in();
    void tableClear();
    void searchRecord();
private:
	Ui::tableClassClass *ui;
    QStandardItemModel m_model;
};

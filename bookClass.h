#pragma once

#include <QWidget>
#include "ui_bookClass.h"
#include<qstandarditemmodel.h>
#include<addBookClass.h>
QT_BEGIN_MOC_NAMESPACE
namespace Ui { class bookClass; };
QT_END_NAMESPACE
class bookClass : public QWidget
{
	Q_OBJECT

public:
	bookClass(QWidget *parent = nullptr);
	~bookClass();
    void bookui(QString conditon = "");
    addBookClass* addPage = NULL;
    void newpage();
    void searchbook();
    void deletebook();
    QString nowid;
public slots:
    void turnPage();
    void returnbook();
    void borrowbook();
private:
	Ui::bookClassClass *ui;
    QStandardItemModel m_model;
   
};

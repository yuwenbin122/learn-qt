#include "QtWidgetsApplication1.h"
#include <QtWidgets/QApplication>
#include<QString>
#include<QtSql/qsqltablemodel.h>
#include <QApplication>			
#include <QDebug>
#include <QMessageBox>
#include"SqliteOperator.h"
#include<qsqlquery.h>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SqliteOperator::getInstance()->inint();
    QtWidgetsApplication1 w;
    w.show();
    return a.exec();
}

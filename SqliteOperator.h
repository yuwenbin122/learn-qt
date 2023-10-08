#pragma once
#ifndef SQLITEOPERATOR_H
#define SQLITEOPERATOR_H
#include<qsqldatabase.h>
#include<qsqlquery.h>
#include<qsqlerror.h>
#include<qdebug.h>
#include<qsqldatabase.h>
#include<qsqlrecord.h>
class SqliteOperator
{
public:
    SqliteOperator();
    ~SqliteOperator();
    static SqliteOperator* instance;
    static SqliteOperator* getInstance()
    {
        if (nullptr == instance)
        {
            instance = new SqliteOperator();
        }
        return instance;
    }
    void inint();
    bool login(QString strUsser,QString strPass);
    QVector<QStringList>getUser(QString condition = "");
    QVector<QStringList>getBook(QString condition = "");
    QVector<QStringList>getTrace(QString condition = "");
    bool AddUser(QVector<QStringList>v );
    void deleteUser(QString id);
    bool AddBooks(QVector<QStringList>v);
    void borrowBooks(QString bookName, QString username);
    void deleteBooks(QString bookName);
    void returnBooks(QString bookName, QString username);
    void clearRecord();
private:
    QSqlDatabase db;
   
};


#endif
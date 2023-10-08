#include<SqliteOperator.h>
#include<qcoreapplication.h>
#include<qmessagebox.h>
#include<qdatetime.h>
 SqliteOperator*SqliteOperator::instance = nullptr;
 SqliteOperator::SqliteOperator()
 {
 }

 SqliteOperator::~SqliteOperator()
 {
 }

 bool SqliteOperator::login(QString strUsser, QString strPass)
 { 
    
     bool r=1;
     QString strsql = QString("select * from user where username ='%1'and password = '%2'").arg(strUsser).arg(strPass);
     QSqlQuery q(strsql);
     if (!q.next())
     {
         r = 0;
         qDebug() << r;
     }
     return r;

 }
 QVector<QStringList>SqliteOperator::getUser(QString condition)
 {
     QSqlQuery q(db);
     QString strsql = QString("select * from user %1").arg(condition);
     QVector<QStringList> vec;
     bool ret = q.exec(strsql);
     if (ret)
     {
         int ic = q.record().count();
         QStringList l;
         while (q.next())
         {
             l.clear();
             for (int i = 0; i < ic; i++)
             {
                 l << q.value(i).toString();
             }
             vec.push_back(l);
         }
         return vec;
     }
 }
 QVector<QStringList>SqliteOperator::getTrace(QString condition)
 {
     QSqlQuery q(db);
     QString strsql = QString("select * from trace %1").arg(condition);
     QVector<QStringList> vec;
     bool ret = q.exec(strsql);
     if (ret)
     {
         int ic = q.record().count();
         QStringList l;
         while (q.next())
         {
             l.clear();
             for (int i = 0; i < ic; i++)
             {
                 l << q.value(i).toString();
             }
             vec.push_back(l);
         }
         return vec;
     }
 }
 QVector<QStringList>SqliteOperator::getBook(QString condition)
 {
     QSqlQuery q(db);
     QString strsql = QString("select * from book %1").arg(condition);
     QVector<QStringList> vec;
     bool ret = q.exec(strsql);
     if (ret)
     {
         int ic = q.record().count();
         QStringList l;
         while (q.next())
         {
             l.clear();
             for (int i = 0; i < ic; i++)
             {
                 l << q.value(i).toString();
             }
             vec.push_back(l);
         }
         return vec;
     }
 }
 void SqliteOperator::inint()
 {
     QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");   //数据库驱动类型为SQL Server
     db.setDatabaseName("user.db");
     if (!db.open())
     {
         qDebug() << "open error";
     }

     QString createsql = QString("create table if not exists user(id integer primary key autoincrement,"
         "username text unique not NULL, "
         "password text not NULL,"
         "name text not NULL,"
         "model text not NULL )");
     QSqlQuery q;
     if (!q.exec(createsql)) {
         qDebug() << q.lastError();
     }
     else {
         qDebug() << "table create success";
     }
      createsql = QString("create table if not exists book(bookName text primary key ,"
         "articleName text not NULL, "
         "type text not NULL,"
         "local text not NULL,"
         "allin int not NULL ,"
         "rest int check(rest>=0 and rest<=allin))");
     q.clear();
     if (!q.exec(createsql)) {
         qDebug() << q.lastError();
     }
     else {
         qDebug() << "table create success";
     }
     q.clear();
     createsql= QString("create table if not exists trace(userName text not NULL ,"
         "bookName text  not NULL, "
         "borrowTime text not NULL ,"
         "endTime text )");
     if (!q.exec(createsql)) {
         qDebug() << q.lastError();
     }
     else {
         qDebug() << "table create success";
     }

     
 }
bool SqliteOperator::AddUser(QVector<QStringList>v)
 {
    bool r;
     QSqlQuery q(db);
     for (auto it : v)
     {
      QString sql = QString("insert into user values ('%1','%2','%3','%4','%5');").arg(it[0])
          .arg(it[1]).
          arg(it[2]).
          arg(it[3]).
          arg(it[4]);
          r = q.exec(sql);
         if (!r)
             qDebug() << r;
     }
     return r;
 }
bool SqliteOperator::AddBooks(QVector<QStringList>v)
{
    bool r;
    QSqlQuery q(db);
    for (auto it : v)
    {
        QString sql = QString("insert into book values ('%1','%2','%3','%4','%5','%6');").arg(it[0])
            .arg(it[1]).
            arg(it[2]).
            arg(it[3]).
            arg(it[4].toInt()).arg(it[5].toInt());
        r = q.exec(sql);
        if (!r)
            qDebug() << q.lastError();
    }
    return r;
}
void  SqliteOperator::deleteUser(QString id)
{
    QSqlQuery q;
    QString sql = QString("delete from user where username = '%1'").arg(id);
    if (!q.exec(sql))
    {
        qDebug() << q.lastError(); 
    }
   
}
void  SqliteOperator::deleteBooks(QString bookName)
{
    QSqlQuery q;
    QString sql = QString("delete from book where bookName = '%1'").arg(bookName);
    if (!q.exec(sql))
    {
        qDebug() << q.lastError();
    }

}
void SqliteOperator::returnBooks(QString bookName,QString  username)
{
    QSqlQuery q;
   
    QString sql2 = QString("update trace set endTime='%1'where bookName='%2'and userName='%3'").arg(QDateTime::currentDateTime().toString()).arg(bookName).arg(username);
    if (!q.exec(sql2))
    {
        qDebug() << q.lastError();
    }
    else { 
        q.clear();
        QString sql = QString("update book set rest=rest+1 where bookName = '%1'").arg(bookName);
        if (!q.exec(sql))
        {
            qDebug() << q.lastError();
        }
    }
}
void SqliteOperator::borrowBooks(QString bookName, QString  username)
{
    QSqlQuery q;
    QString sql2 = QString("insert into trace values('%2', '%3', '%4',NULL)").arg(username).arg(bookName).arg(QDateTime::currentDateTime().toString());
    if (!q.exec(sql2))
    {
        qDebug() << q.lastError();
    }
    else
    {
        q.clear();
        QString sql = QString("update book set rest=rest-1 where bookName = '%1'").arg(bookName);
        if (!q.exec(sql))
        {
            qDebug() << q.lastError();
        }
    }

   
   
}

void SqliteOperator::clearRecord()
{
    QSqlQuery q;
    QString sql = QString("delete from trace");
    if (!q.exec(sql))
    {
        qDebug() << q.lastError();
    }
}




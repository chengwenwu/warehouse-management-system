#include "database.h"
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QVariant>

bool Database::Connect(const QString &dbName)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbName);
    if (!db.open()) {
        QMessageBox::critical(0, QObject::tr("Database Error"), db.lastError().text());
        return false;
    }
    return true;
}

bool Database::CreatDataBase()
{
    if (Connect("demo.db")) {
        QSqlQuery query;
        //判断表是否已经存在
        QString sql = QString("select * from sqlite_master where name='%1'").arg("goods");
        query.exec(sql);
        if (query.next()) {
            return true;
        }
        query.finish();
        if (!query.exec("CREATE TABLE goods("
                        "id INT,"
                        "name VARCHAR,"
                        "number INT)")) {
            QMessageBox::critical(0, QObject::tr("Database Error"), query.lastError().text());
            return false;
        }
        return true;
    }
    return false;
}

bool Database::WriteAnItemToDataBase(int id, QString name, int number)
{
    QSqlQuery query;
    if (number == -1) { //删除指定商品
        query.prepare("delete from goods where id = :id_in");
        query.bindValue(":id_in", id);

        if (!query.exec()) {
            QMessageBox::critical(0, QObject::tr("Database Error -1"), query.lastError().text());
            return false;
        }
        return true;
    }

    query.prepare("select * from goods where id = :id_in");
    query.bindValue(":id_in", id);
    query.exec();
    if (query.next()) { //如果该商品存在，那么更新它的数据
        query.finish();
        query.prepare("update goods set number = :number_in where id = :id_in");
        query.bindValue(":id_in", id);
        query.bindValue(":number_in", number);
        if (!query.exec()) {
            QMessageBox::critical(0, QObject::tr("Database Error-2"), query.lastError().text());
            return false;
        }
        return true;
    } else { //如果不存在这个商品，那个添加这个商品
        query.finish();
        query.prepare("insert into goods(id, name, number) values(:id_in,:name_in,:number_in)");
        query.bindValue(":id_in", id);
        query.bindValue(":name_in", name);
        query.bindValue(":number_in", number);
        if (!query.exec()) {
            QMessageBox::critical(0, QObject::tr("Database Error-3"), query.lastError().text());
            return false;
        }
    }
    return true;
}

#pragma once
#include <QString>
class Database {
public:
    bool Connect(const QString &dbName);
    bool CreatDataBase();
    /*
    @number_in:应该是更新后的数据
    */
    bool WriteAnItemToDataBase(int id, QString name, int number);
};

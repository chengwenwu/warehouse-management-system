#ifndef DATABASE_H
#define DATABASE_H
#include <QString>
class Database {
public:
    bool Connect(const QString &dbName);
    bool CreatDataBase();
    /*
    @number_in:应该是更新后的数据
    */
    bool WriteAnItemToDataBase(int id_in, QString name_in, int number_in);

private:
};
#endif // DATABASE_H

#include "warehouse.h"
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>

Warehouse::Warehouse()
{
    this->goodsList_.clear();
    if (!db.CreatDataBase()) {
        QMessageBox message(QMessageBox::Warning, "waring", "Creat Database failed!", QMessageBox::Ok);
        if (message.exec() == QMessageBox::Ok)
            exit(-1);
    }
    this->ReadGoodsFromDataBase();
}

Warehouse::~Warehouse() {}

void Warehouse::Empty() //用来将仓库中的货物清零
{
    QSqlQuery query;
    query.exec("delete from goods");
    this->goodsList_.clear();
    QString str = "Warehouse is empty!";
    throw str;
}

bool Warehouse::InputCheck(QString &id, QString &name, QString &count)
{
    QString text = "";
    if (id.length() > 100 || id.length() == 0) {
        text = "Id is wrong, please input again!\n";
    }
    if (name.length() > 100 || name.length() == 0) {
        text = "Name is wrong, please input again!\n";
    }

    if (count.length() >= 10) {
        text += "number is wrong, please input again!\n";
    }

    bool res = false;
    count.toLongLong(&res);

    if (!res) {
        text += "Goods number should only include number!\n";
    }

    id.toLongLong(&res);
    if (!res) {
        text += "id should only include number!\n";
    }

    if (text != "") {
        throw text;
    }
    return true;
}

bool Warehouse::AddGoods(QString id, QString name, QString count)
{
    try {
        if (!InputCheck(id, name, count)) {
            return false;
        }
        int id_temp = stringToNum(id);
        int number = stringToNum(count);
        vector<Goods>::iterator it;
        for (it = goodsList_.begin(); it != goodsList_.end(); it++) {
            if (it->id == id_temp) {
                if (it->name != name) {
                    QString str = "Id and name mismatch\n";
                    throw str;
                }
                //存到数据库中
                db.WriteAnItemToDataBase(id_temp, name, it->count + number);
                it->count += number;
                QString str = "Goods have been stored!";
                throw str;
            }
        } //若已存在要入库的商品，则只需增加其数量
        if (it == goodsList_.end()) {
            AddToList(id_temp, name, number);
            return true;
        } //若目前仓库中没有该商品，则将其加入商品列表
    } catch (QString str1) {
        throw str1;
    }
    return true;
}

//在列表中加入新的商品，该函数在函数add_goods(string name, int count)内部调用
bool Warehouse::AddToList(int id, QString name, int count)
{
    try {
        if (this->goodsList_.size() < ALL) { //仓库未满直接存储
            Goods good = {.id = id, .name = name, .count = count};

            //存进数据库
            db.WriteAnItemToDataBase(id, name, count);
            this->goodsList_.push_back(good);
            QString str = "Goods have been stored!";
            throw str;
        } else {
            QString str = "save failed\n warehouse is full!";
            throw str;
        } //当储存位置已经满了的时候，显示“仓库已满”
    } catch (QString str1) {
        throw str1;
    }
}

//出货
bool Warehouse::DeleteGoods(QString id, QString count)
{
    QString null = "null";
    if (!InputCheck(id, null, count)) {
        return false;
    }
    int id_temp = stringToNum(id);
    int number = stringToNum(count);
    vector<Goods>::iterator it;
    for (it = goodsList_.begin(); it != goodsList_.end(); it++) {
        if (it->id == id_temp) {
            if ((it->count - number) < 0) {
                QString str = "Goods is not enough!";
                throw str;
            } else if ((it->count - number) == 0) { //出货数量大于库存时，拒绝请求
                db.WriteAnItemToDataBase(id_temp, it->name, -1);
                this->goodsList_.erase(it);

                QString str = "OK!\nAll this Goods have been delete!";
                throw str;
                // return true;
            } else if ((it->count - number) > 0) { //出货数量刚好等于库存时，出货，并将该商品从列中移除
                //存进数据库中
                db.WriteAnItemToDataBase(id_temp, it->name, it->count - number);
                it->count -= number;
                QString str = "OK!";
                throw str;
            }
            return true;
        }
    }
    if (it == goodsList_.end()) {
        QString str = "Error\n Goods not exists";
        throw str;
    } //若目前仓库中没有该商品，提示未找到
    return false;
}

//显示目前仓库中所有商品及其数量
void Warehouse::ShowGoods()
{
    QString text = "Id        Name           number\n";
    if (goodsList_.size() == 0) {
        QMessageBox massagebox(QMessageBox::Warning, "waring", "warehouse is empty", QMessageBox::Ok, NULL);
        massagebox.exec();
        return;
    }
    vector<Goods>::iterator it;
    for (it = goodsList_.begin(); it != goodsList_.end(); it++) {
        QString id = QString::number(it->id);
        QString count = QString::number(it->count);
        text = text + id + "        " + it->name + "           " + count + "\n";
    }
    throw text;
}

//在所有商品中进行查找目标商品
void Warehouse::FindGoods(QString id, QString name)
{
    QString text = "Id        Name           number\n";
    vector<Goods>::iterator it;
    for (it = goodsList_.begin(); it != goodsList_.end(); it++) {
        if (it->name == name || QString::number(it->id) == id) {
            QString id_r = QString::number(it->id);
            QString name_r = it->name;
            QString num_r = QString::number(it->count);
            text += (id_r + "        " + name_r + "           " + num_r + "\n");
        }
    }
    throw text;
}

void Warehouse::ReadGoodsFromDataBase()
{
    QSqlQuery query;
    query.exec("SELECT id, name, number FROM goods");
    while (query.next()) {
        int id = query.value(0).toInt();
        QString name = query.value(1).toString();
        int number = query.value(2).toInt();
        Goods good = {.id = id, .name = name, .count = number};
        this->goodsList_.push_back(good);
    }
}

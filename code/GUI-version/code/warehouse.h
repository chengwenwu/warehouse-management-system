#ifndef WAREHOUSE_H
#define WAREHOUSE_H
#include "database.h"
#include "good.h"
#include <cstring>
#include <exception> //对于所有错误的处理形式都是一样的，所以没有对异常进行分类
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <vector>
#define ALL 1500
using namespace std;

namespace Ui {
class Warehouse;
}

class Warehouse {
public:
    Warehouse();
    ~Warehouse();
    void Empty();                                                //初始化储存商品信息的vector
    bool InputCheck(QString &id, QString &name, QString &count); //检查用户输入的商品名和数量是否合法
    bool AddGoods(QString id, QString name, QString count); //进货，对应进货模块，表示当前进货一批数量为count的name商品
    bool AddToList(int id, QString name, int count); //更新库存列表，对应新增商品子功能，新增name商品且初始数量为count
    bool DeleteGoods(QString id, QString count); //出货，对应出货模块，表示当前出货一批数量为count的name商品
    void ShowGoods();                            //显示当前库存列表，包括商品名及其库存量
    void FindGoods(QString id, QString name); //查看仓库中的name商品
    void ReadGoodsFromDataBase();

private:
    vector<Goods> goods;
    Database db;
    int stringToNum(const QString &str)
    {
        return str.toInt();
    } //模板，将字符串类型的变量变为int型
};

#endif // WAREHOUSE_H

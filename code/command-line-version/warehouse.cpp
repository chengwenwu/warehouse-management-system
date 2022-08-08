#include "warehouse.h"
Goods::Goods()
{
    this->name = "";
    this->count = 0;
}
void Goods::setName(string name_i)
{
    this->name = name_i;
}
string Goods::getName()
{
    return this->name;
}
void Goods::setCount(int count_i)
{
    this->count = count_i;
}
int Goods::getCount()
{
    return this->count;
}

Warehouse::Warehouse()
{
    this->goods.clear();
}

void Warehouse::empty() //用来将仓库中的货物清零
{
    this->goods.clear();
    cout << endl
         << "              仓库空空如也，快储存货物吧！    \n"
         << endl
         << endl
         << endl
         << "          注意：" << endl
         << endl
         << "            商品名称应少于100个字符，数量小于100000！" << endl
         << endl;
}

void Warehouse::direction()
{
    cout << "------------------ 请选择要进行的操作 ----------------" << endl
         << "*                                                    *" << endl
         << "*                      1 进货                        *" << endl
         << "*                                                    *" << endl
         << "*                      2 出货                        *" << endl
         << "*                                                    *" << endl
         << "*                      3 货物清单                    *" << endl
         << "*                                                    *" << endl
         << "*                      4 查询货物                    *" << endl
         << "*                                                    *" << endl
         << "*                      5 清空仓库                    *" << endl
         << "*                                                    *" << endl
         << "*                      6 退出系统                    *" << endl
         << "------------------------------------------------------" << endl;
}

bool Warehouse::input(char *commond)
{
    cin >> *commond;
    cin.get();
    cin.sync();
    cin.clear();
    if (*commond < '1' || *commond > '6') //指令错误时不继续下面的操作
    {
        cout << endl << "                   您的指令错误，请重新输入！" << endl << endl;
        return false;
    } else {
        return true;
    }
} //若指令不合法，要求重新输入，直到输入合法指令

int Warehouse::inputCheck(string &name, string count)
{
    while (name.length() > 100 || name.length() == 0) {
        cout << endl << "         您输入的商品名称有误，请重新输入！ " << endl << endl;
        cin >> name;
        cin.sync();
        cin.clear();
    }

    int number;
    while (!0) {
        while (count.length() >= 10) {
            cout << endl << "         您输入的商品数量有误，请重新输入！ " << endl << endl;
            cin >> count;
            cin.sync();
            cin.clear();
        }
        int coun = 0;
        for (coun = 0; coun < count.length(); coun++) {
            if (!isdigit(count[coun])) {
                cout << endl << "         您输入的商品数量有误，请重新输入！ " << endl << endl;
                break;
            }
        }
        if (coun < count.length()) {
            cin >> count;
            cin.sync();
            cin.clear();
            continue;
        } else {
            number = strtol(count.c_str(), NULL, 0); //将输入的
            if (number > 0 && number < 100000)
                break;
            else {
                cout << endl << "         您输入的商品数量有误，请重新输入！ " << endl << endl;
                cin >> count;
                cin.sync();
                cin.clear();
                continue;
            }
        }
    }
    return number;
}

bool Warehouse::add_goods(string name, string count)
{
    int number = inputCheck(name, count);
    vector<Goods>::iterator it;
    for (it = goods.begin(); it != goods.end(); it++) {
        if (it->getName() == name) { //若已存在要入库的商品，则只需增加其数量
            it->setCount(it->getCount() + number);
            cout << endl << "货物已储存，目前您的货物" << name << "的数量为：" << it->getCount() << endl << endl;
            return true;
        }
    }
    if (it == goods.end()) { //若目前仓库中没有该商品，则将其加入商品列表
        add_to_list(name, number);
        return true;
    }
    return false;
}

//在列表中加入新的商品，该函数在函数add_goods(string name, int count)内部调用
bool Warehouse::add_to_list(string name, int count)
{
    if (this->goods.size() < ALL) { //仓库未满直接存储
        Goods good;
        good.setName(name);
        good.setCount(count);

        this->goods.push_back(good);
        cout << endl << "货物已储存，目前您的货物" << name << "的数量为：" << count << endl << endl;
        return true;
    } else { //当储存位置已经满了的时候，显示“仓库已满”
        cout << endl << "                    仓库已满!            " << endl << endl;
        return false;
    }
}

//出货
bool Warehouse::delete_goods(string name, string count)
{
    int number = inputCheck(name, count);
    vector<Goods>::iterator it;
    for (it = goods.begin(); it != goods.end(); it++) {
        if (it->getName() == name) {
            if ((it->getCount() - number) < 0) { //出货数量大于库存时，拒绝请求
                cout << endl << "                  库存不足，请求已被拒绝！" << endl << endl;
                return false;
            } else if ((it->getCount() - number) == 0) { //出货数量刚好等于库存时，出货，并将该商品从列中移除
                this->goods.erase(it);
                cout << endl << "                    请求成功，该货物已全部出库，库存为零！" << endl << endl;
                return true;
            } else if ((it->getCount() - number) > 0) {
                it->setCount(it->getCount() - number);
                cout << endl << "请求已被受理，目前商品" << name << "的数量为：" << it->getCount() << endl << endl;
                return true;
            }
            return true;
            break;
        }
    }
    if (it == goods.end()) { //若目前仓库中没有该商品，提示未找到
        cout << endl << "               未找到该商品，输入有误！" << endl << endl;
        return false;
    }
    return true;
}

//显示目前仓库中所有商品及其数量
void Warehouse::show_goods()
{
    cout << setw(100) << left << "商品" << setw(8) << left << "数量" << endl;
    vector<Goods>::iterator it;
    for (it = goods.begin(); it != goods.end(); it++) {
        cout << setw(100) << left << it->getName() << setw(8) << left << it->getCount() << endl;
    }
}

//在所有商品中进行查找目标商品
void Warehouse::find_goods(string name)
{
    vector<Goods>::iterator it;
    for (it = goods.begin(); it != goods.end(); it++) {
        if (it->getName() == name) {
            cout << "商品 " << name << " 的数量为" << it->getCount() << "件" << endl << endl;
            break;
        }
    }
    if (it == goods.end()) {
        cout << endl << "                      目前仓库中没有该商品！" << endl << endl;
    }
}
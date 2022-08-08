#include "warehouse.h"
#include "warehouseMgrSysConfig.h"
#include <cstring>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    cout << argv[0] << " Version " << warehouseMgrSys_VERSION_MAJOR << "." << warehouseMgrSys_VERSION_MINOR
         << std::endl;
    Warehouse warehouse;
    warehouse.empty();
    char commond = '3';

    while (commond != '6') //输入指令6时退出系统
    {
        warehouse.direction(); //为用户做出提示，方便操作

        while (warehouse.input(&commond) == false)
            ; //检查输入是否正确

        switch (commond) //开关实现各功能分块选择
        {
            case '1': { //进货
                cout << endl << "    请输入要入库的商品名称，并以回车键结束 : " << endl;
                string name1;
                getline(cin, name1);
                cin.sync();
                cin.clear();

                cout << endl << "   请输入要入库的商品数量 : " << endl;
                string count;
                getline(cin, count);
                cin.sync();
                cin.clear();

                warehouse.add_goods(name1, count);
                break;
            }
            case '2': { //出货
                cout << endl << "  请输入要出库的商品名称，并以回车键结束 : " << endl;
                string name2;
                getline(cin, name2);
                cin.sync();
                cin.clear();

                cout << endl << "   请输入要出库的商品数量 : " << endl;
                string count2;
                cin >> count2;
                cin.sync();
                cin.clear();

                warehouse.delete_goods(name2, count2);
                break;
            }
            case '3': { //显示清单
                warehouse.show_goods();
                break;
            }
            case '4': { //实现查询
                cout << endl << "  请输入要查询的商品名称，并以回车键结束 : " << endl;
                string name3;
                getline(cin, name3);
                cin.sync();
                cin.clear();

                warehouse.find_goods(name3);
                break;
            }
            case '5': { //清空仓库
                warehouse.empty();
            }
        }
    }
    return 0;
}

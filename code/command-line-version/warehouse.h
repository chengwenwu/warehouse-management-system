#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <sstream>
#include <iomanip>
#include <vector>
#define ALL 1500
using namespace std;

class Goods{
public:
	Goods();
	void setName(string name_i);
	string getName();
	void setCount(int count_i);
	int getCount();
private:
	string name;
	int count;
}; 

class Warehouse {
public:
	Warehouse();
	void empty();//初始化储存商品信息的vector 
	void direction();//输出提示语，方便用户操作 
	bool input(char *commond);//检查输入是否正确 
	int inputCheck(string &name, string count);//检查用户输入的商品名和数量是否合法
	//进货： 
	//进货，对应进货模块，表示当前进货一批数量为count的name商品
	bool add_goods(string name, string count);

	//更新库存列表，对应新增商品子功能，新增name商品且初始数量为count
	bool add_to_list(string name, int count);

	//出货：
	//出货，对应出货模块，表示当前出货一批数量为count的name商品
	bool delete_goods(string name, string count);

	//查询：
	///显示当前库存列表，包括商品名及其库存量
	void show_goods();
	//查看仓库中的name商品
	void find_goods(string name);
private:
	vector<Goods> goods;
	template <class Type>
	Type stringToNum(const string& str)
	{
		istringstream iss(str);
		Type num;
		iss >> num;
		return num;
	} //模板，将字符串类型的变量变为int型 
};

 
 

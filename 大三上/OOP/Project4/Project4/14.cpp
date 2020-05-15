#include <iostream>
using namespace std;
//必要的头文件等，可能为多条语句
class Gather   //定义类Gather
{
protected:
	int m_data[100]; //数据成员
	int m_count; //集合元素个数

public:
	Gather() {
		this->Clear();
	}   //定义默认构造函数，函数体中调用Clear()函数

	void Clear() {
		m_count = 0;
	}//清空集合函数Clear()，函数体中设置m_count为0

	int GetCount()  const {
		return m_count;
	}//定义返回集合元素个数函数int GetCount()，函数体中返回m_count
	//如果找到，返回下标，如果没有找到，返回-1
	int Find(int a) {
		for (int i = 0; i < GetCount(); i++) {
			if (m_data[i] == a) return i;
		}
		return -1;
	}
	//定义集合元素位置函数int Find()，函数只有一个参数，即要查找的元素值。元素位置从0开始，找不到则返回-1。

	bool Add(int a) {
		if (Find(a) == -1) {
			m_data[m_count++] = a;
			return true;
		}
		else {
			return false;
		}
	}//定义加入集合元素函数Add()，函数只有一个参数，即要加入集合的元素值。如果该元素在集合中已经存在，则返回false；否则加入该元素，并返回true。

	bool Remove(int a) {
		int index = Find(a);
		if (index == -1) {
			return false;
		}
		else {
			for (int i = 0; i < m_count; i++) {
				m_data[i] = m_data[i + 1];
			}
			m_count--;
			return true;
		}
	}//定义移出集合元素函数Remove()，函数只有一个参数，即要移出集合的元素值。如果该元素在集合中不存在，则返回false；否则移出该元素，并返回true。

	Gather operator + (const Gather& b) {
		Gather c = *this;
		int flag;
		for (int i = 0; i < b.m_count; i++) {
			flag = c.Find(b.m_data[i]);
			if (flag != -1) c.Add(b.m_data[i]);
		}
		return c;
	}    //重载加号运算符，代表集合并运算，函数只有一个参数，即Gather类型集合g2对象的常引用。

	Gather operator - (const Gather& b) {
		Gather c = *this;
		int flag;
		for (int i = 0; i < b.m_count; i++) {
			flag = c.Find(b.m_data[i]);
			if (flag >= 0) c.Remove(b.m_data[i]);
			else;
		}
		return c;
	}    //重载减法运算符，代表集合差运算，函数只有一个参数，即Gather类型集合g2对象的常引用。

	friend ostream& operator << (ostream& a, const Gather& b) {
		a << "(";
		for (int i = 0; i < b.GetCount(); i++) {
			if (i == 0) a << b.m_data[i];
			else {
				a << "," << b.m_data[i];
			}
		}
		a << ")";
		return a;
	}//输出运算符<<重载友元函数，函数有两个参数，即ostream类型dout的引用、Gather类型集合g对象的常引用。

};
int main()
{


	Gather g1, g2;    //创建Gather对象g1和g2
	int x, y, a, b;
	cin >> x >> y;    //输入整数x和y，然后将[x, y]之间的所有整数放入集合g1中

	g2 = g1;   //调用默认赋值运算符重载函数，将g1赋给g2
	cout << "集合g2内容如下：" << g2 << endl; //调用输出运算符重载函数

	Gather g3(g1);    //调用默认拷贝构造函数，将g1赋给g3	

	cin >> x >> y >> a >> b;
	g3.Remove(x);
	g3.Remove(y);//从g3中移走集合元素函数x，y
	g3.Add(a);
	g3.Add(b);//加入a和b到集合g3中

	cout << "集合g3内容如下：" << g3 << endl;
	cout << "集合g2与g3的差：" << g2 - g3 << endl;
	cout << "集合g2与g3的合：" << g2 + g3 << endl;
	return 0;
}

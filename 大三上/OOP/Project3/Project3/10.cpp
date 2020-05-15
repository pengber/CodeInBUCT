#include <iostream>
using namespace std;
class A //基类A 
{
private:
	int a;
public:
	A() {};
	A(int i) {
		this->Set(i);
	}
	void Set(int i) //给数据成员a赋值 
	{
		a = i;
	}
	int Get() //返回数据成员a的值 
	{
		return a;
	}
};
class B:public A //从A类公有派生B类 
{
private:
	int b;
public:
	B() {};
	B(int i, int j):A(i) {
		this->Set(j);
	}
	void Set(int i) //给数据成员b赋值 
	{
		 b= i;
	}
	int Get() //返回数据成员b的值 
	{
		return b;
	}
	void Show() //输出数据成员a和b的值 
	{
		cout << "A::a=" << A::Get() << ", B::b=" << this->Get() << endl;
	}
};
int main()
{
	B bb; //创建类B的对象bb 
	int x, y;
	cin >> x >> y;
	bb.A::Set(x); //给数据成员a赋值 
	bb.Set(y); //给数据成员b赋值 
	bb.Show();
	return 0;
}
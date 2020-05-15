#include <iostream>
using namespace std;//必要的头文件等，可能为多条语句 
class A1    //基类A1类 
{
protected:    //保护成员 
	  int a1;
public:    //公有成员 
		 A1(int a = 0):a1(a)    //带有一个参数a的构造函数（且参数有默认值0），在初始化列表中使用a的值初始化数据成员a1，函数体如下： 
	  {
		 cout << "执行基类A1的构造函数" << endl;
	  }
		 virtual ~A1 ()   //析构函数，函数体如下： 
	  {
		 cout << "执行基类A1的析构函数" << endl;
	  }
	  void ShowA1() const //输出数据成员到屏幕 
	  {
		 cout << "A1::a1=" << a1 << endl;
	  }
};
class A2    //基类A2类 
{
protected:    //保护成员 
	  int a2;
public:    //公有成员 
		 A2(int a):a2(a)    //带有一个参数a的构造函数（且参数有默认值0），在初始化列表中使用a的值初始化数据成员a2，函数体如下： 
	  {
		 cout << "执行基类A2的构造函数" << endl;
	  }
		 virtual ~A2()    //析构函数，函数体如下： 
	  {
		 cout << "执行基类A2的析构函数" << endl;
	  }
	  void ShowA2() const //输出数据成员到屏幕 
	  {
		 cout << "A2::a2=" << a2 << endl;
	  }
};
class B:public A1, private A2    //派生类B从A1公有继承，从A2私有继承 
{
public:    //公有成员 
		 B(int a1,int a2):A1(a1),A2(a2)    //带有两个参数a1、a2的构造函数（且参数均有默认值0），在初始化列表中分别调用基类A1、A2的构造函数，并传递相应的参数，函数体如下： 
	  {
		 cout << "执行派生类B的构造函数" << endl;
	  }
		~B()    //析构函数，函数体如下： 
	  {
		 cout << "执行派生类B的析构函数" << endl;
	  }
		void Show() const    //输出常成员函数 
		{
			  ShowA1();    //调用基类函数ShowA1() 
		ShowA2();    //调用基类函数ShowA2() 
	  }
};
int main()
{
	int x, y;
	cin >> x >> y;
	B obj(x, y); //创建派生类B对象obj 
	obj.Show();
	obj.ShowA1();
	return 0;
}
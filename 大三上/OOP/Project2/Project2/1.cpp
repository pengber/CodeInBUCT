#include <iostream>//必要的头文件等，可能为多条语句 
#include <string>
#include <iomanip>
using namespace std;
class Fruit    //基类Fruit类 
{
protected:    //保护成员 
	  string color; //颜色 
	  string flavor; //味道 
	  float weight; //重量 
	  string kind; //种类 

public:    //公有成员 
	Fruit() {};    //无参构造函数，函数体可以为空 

	void SetKind(string k) { kind = k; };    //设置种类SetKind()成员函数，一个string类型的参数，函数无返回值，在函数体中将参数赋给相应的数据成员 

	void SetColor(string c) { color = c; };    //设置颜色SetColor()成员函数，一个string类型的参数，函数无返回值，在函数体中将参数赋给相应的数据成员 

	void SetFlavor(string f) {
		flavor = f;
	};    //设置味道SetFlavor()成员函数，一个string类型的参数，函数无返回值，在函数体中将参数赋给相应的数据成员 

	void SetWeight(float w) { weight = w; };    //设置重量SetWeight()成员函数，一个float类型的参数，函数无返回值，在函数体中将参数赋给相应的数据成员 

	float GetWeight() const {
		return weight;
	}    //返回重量常成员函数GetWeight()，函数无参数，返回值float类型，在函数体中将返回相应的数据成员 
};

class Apple:public Fruit   	//定义派生类Apple，公有继承方式 
{
	public:
	Apple() { SetKind("苹果"); }    //定义无参构造函数，并在其中调用基类SetKind("苹果")函数，将字符串"苹果"作为参数 
};

int main()
{
	Apple a, b;    //创建Apple类的对象a、b，并分别调用SetColor()、SetFlavor()函数。 
	a.SetColor("red");
	b.SetFlavor("smelly");
	float x, y;
	cin >> x >> y;//输入两个float类型的数据x和y，调用相应函数将x和y的值赋给a、b对象的数据成员weight。 
	a.SetWeight(x);
	b.SetWeight(y);
		if (a.GetWeight() > b.GetWeight())
			cout << setiosflags(ios::fixed) << setprecision(2) << "最重为a苹果" << a.GetWeight() << "克" << endl;
		else
			cout << setiosflags(ios::fixed) << setprecision(2) << "最重为b苹果" << b.GetWeight() << "克" << endl;
	return 0;
}
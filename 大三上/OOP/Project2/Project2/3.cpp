#include <iostream>
#include <iomanip>
using namespace std;
class Circle //基类Circle 
{
protected:
	double radius; //圆半径 
public:
	void SetRadius(double r) //设置半径函数 
	{
		radius = r;
	}
	double GetArea() const //返回圆面积常成员函数 
	{
		return 3.14 * radius * radius;
	}
};
class Sphere :public Circle {
public:
	void SetRadius(double r) {
		Circle::SetRadius(r);
	}
	double GetArea() const
	{
		return  4 * 3.14 * radius * radius;
	}
	double GetVolume() const {
		return (4.0 / 3) * 3.14 * radius * radius * radius;
	}
};
int main()
{
	double r;
	cin >> r;
	Sphere s; //创建派生类Sphere的对象球s 
	s.SetRadius(r); //调用基类函数设置球s的半径 
	cout << "球的表面积和体积为：" << setiosflags(ios::fixed) << setprecision(2) << s.GetArea() << ", " << s.GetVolume() << endl;
	cout << "把球从中间劈开，横切面的面积为：" << s.Circle::GetArea() << endl;
	return 0;
}
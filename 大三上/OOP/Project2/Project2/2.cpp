#include <iostream>
#include <iomanip>
using namespace std;//必要的头文件等，可能为多条语句 
class Point    //定义点类Point 
{
protected:
	int x;
	int y;//定义保护数据成员：int类型的x和y 
public:
	Point() {
		x = 0;
		y = 0;
	}    //无参默认构造函数，在函数体中初始化数据成员x和y为0 

	Point(int x1, int y1) {
		x = x1;
		y = y1;//有两个参数（参数没有默认值）的构造函数，在函数体中将形参x1和y1分别赋给数据成员x和y 
	}
	void SetX(int x1) { x = x1; }   //设置x坐标的函数setX(int), 将形参x1赋给数据成员x 

	void SetY(int y1) { y = y1; }    //设置y坐标的函数setY(int), 将形参y1赋给数据成员y 

	int getX () const {
		return x;
	}   //返回x坐标的函数getX () 

	int getY() const {
		return y;
	}//返回y坐标的函数getY() 
};
class Circle
{
protected:
	Point center;
	int radius;//定义保护数据成员：Point类型的圆心坐标center，int类型的半径radius 

public:
	Circle() {
		center.SetX(0);
		center.SetY(0);
		radius = 0;
	}//默认构造函数，在初始化列表中初始化子对象center，设置圆心坐标为0和0；在函数体中，设置radius半径为0 

	Circle(int x1, int y1, int r1) {
		this->center.SetX(x1);
		this->center.SetY(y1);
		this->radius = r1;//有三个参数x1、y1和r1的构造函数，在初始化列表中初始化子对象center，设置圆心坐标为x1和y1；在函数体中，设置radius半径为r1 
	}
	double area() const {
		return 3.14 * radius * radius;
	}//计算并返回圆面积常成员函数area()，pi使用3.14。 

	int getX () {
		return center.getX ();
	}    //返回圆心坐标center的x坐标的成员函数getX ()。 

	int getY() {
		return center.getY();
	}//返回圆心坐标center的y坐标的成员函数getY() 
};
int main()
{
	int x1, y1, r1;
	cin >> x1 >> y1 >> r1;
	Circle a(x1, y1, r1), b;
	cout << "创建了2个圆对象a和b" << endl;
	cout << "圆a的圆心坐标" << a.getX () << "和" << a.getY() << endl;
	cout << "圆b的圆心坐标" << b.getX () << "和" << b.getY() << endl;
	cout << "圆a的面积为" << setiosflags(ios::fixed) << setprecision(2) << a.area() << endl;    //注意面积输出要求小数点后必须保留2位有效数字（四舍五入），不足补零 
	cout << "圆b的面积为" << setiosflags(ios::fixed) << setprecision(2) << b.area() << endl;    //注意面积输出要求小数点后必须保留2位有效数字（四舍五入），不足补零 
		return 0;
}
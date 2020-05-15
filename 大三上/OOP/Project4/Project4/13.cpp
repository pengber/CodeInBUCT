#include <iostream>//必要的头文件等，可能为多条语句
using namespace std;
class Test    //Test类
{
protected:
	int x;
	int y;//定义保护的int类型的数据成员x和y
public:
	Test(int a = 0, int b = 0) :x(a), y(b) {}
	      //带有两个int类型参数a和b，且参数默认值均为0的构造函数，在初始化列表中，将形参a赋给数据成员x，b赋给y

	~Test()
	{
		cout << x << " " << y << endl;
	}   //析构函数，在函数体中输出x、y的值到屏幕，共占一行，两个值之间用一个空格隔开
};
int main()
{
	Test t1;    //创建Test对象t1
	Test* t2;    //定义Test指针t2
		int a, b;


	for (int i = 0; i < 2; i++)
	{
		cin >> a >> b;
		t2 = new    Test(a, b); //创建Test堆对象，并将地址赋给指针t2
		delete    t2; //释放堆对象
	}
	return 0;
}
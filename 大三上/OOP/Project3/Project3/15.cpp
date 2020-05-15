#include <iostream>
#include <iomanip>
using namespace std;
template <class T,int a>
class Stack {
protected:
	T *m_data;
	int m_count;
public:
	Stack() { m_data = new int(a) };
	~Stack() { clear() };
	void clear() { delete m_data };
	void Push(T);
	bool Pop(T &);
};
int main()
{
	Stack <int, 100> stk1; //创建对象 
	Stack <double, 100> stk2; //创建对象 
	int n, m;
	cin >> n >> m;
	//输入n个整数，并压入堆栈stk1中 

		…… //输入m个浮点数，并压入堆栈stk2中 

		int a;
	if (stk1.Pop(a))
		cout << a << endl;
	if (stk1.Pop(a))
		cout << a << endl;
	double x;
	if (stk2.Pop(x))
		cout << x << endl;
	if (stk2.Pop(x))
		cout << x << endl;
	return 0;
}
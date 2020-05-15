#include <iostream>
using namespace std;

bool Neighbor(int a, int b) {
	if (a - b == 1 || a - b == -1) {
		return true;
	}
	else return false;
}
bool Neighbor(int a, int b, int c) {
	if ((Neighbor(a, b) && Neighbor(b, c))||(Neighbor(a,c)&&Neighbor(c,b))||(Neighbor(a,b)&&Neighbor(c,a))) return true;
	else
	{
		return false;
	}
}
int main()
{
	int a, b, c, d, e;
	cin >> a >> b >> c >> d >> e;
	if (Neighbor(a, b)) //调用重载函数Neighbor() 
		cout << "true" << endl;
	else
		cout << "false" << endl;
	if (Neighbor(c, d, e)) //调用重载函数Neighbor() 
		cout << "true" << endl;
	else
		cout << "false" << endl;
	return 0;
}
#include <iostream>
using namespace std;
class B
{
public:
	double x;

	double y;

	double z;
};
int main()
{
	B b;


	cin >> b.x;
	cin >> b.y;
	cin >> b.z;
	cout << b.x << endl;
	cout << b.y << endl;
	cout << b.z << endl;
	return 0;
}
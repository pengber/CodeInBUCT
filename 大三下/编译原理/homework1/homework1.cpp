#include <fstream>
#include <iostream>
using namespace std;
int main()
{
	int a[1000];
	ifstream in("input.txt");
	for (int i = 0; i < 10; i++)
		in >> a[i];
	cout << "file content:" << endl;
	for (int i = 0; i < 10; i++)
		cout << a[i] << endl;
	ofstream out("output.txt");
	out << "file content:" << endl;
	for (int i = 0; i < 10; i++) {
		out << a[i];
	}
	in.close();
	out.close();
	cin.get();
}
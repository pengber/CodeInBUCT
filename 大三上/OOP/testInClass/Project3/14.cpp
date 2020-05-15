#include <iostream>
#include <string>
using namespace std;
class CWnd
{
protected:
	int width;
	int height;
public:
	CWnd()
	{
		width = height = 0;
	}
	CWnd(int a, int b)
	{
		width = a;
		height = b;
	}
	void setHeight(int s)
	{
		height = s;
	}
	void setWidth(int s)
	{
		width = s;
	}
	int getHeight()
	{
		return height;
	}
	int getWidth()
	{
		return width;
	}
};
class CEdit:public CWnd {
protected:
	string text;
public:
	CEdit() { text = ""; }
	CEdit(int a, int b, string c):CWnd(a,b){
		text = c;
	}
	void setText(string a) {
		text = a;
	}
	string getText()  const {
		return text;
	}
};
int main()
{
	int a, b;
	string c;
	cin >> a >> b >> c;
	CEdit d(a, b, c);
	cout << d.getWidth() << endl;
	cout << d.getHeight() << endl;
	cout << d.getText() << endl;
	return 0;
}
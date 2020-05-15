#include<iostream>
#include<iomanip>
#include<string>
#include<cmath>
using namespace std;
class Gather {
protected:
	int m_data[100]; //数据成员 
	int m_count; //集合元素个数 
public:
	Gather() {
		Clear();
	}
	void Clear() {
		m_count = 0;
	}
	int GetCount()const {
		return m_count;
	}
	int Find(int e) {
		for (int i = 0; i < m_count; i++) {
			if (m_data[i] == e) {
				return i;
			}
		}
		return -1;
	}
	bool Add(int e) {
		int pos = Find(e);
		if (pos != -1) {
			return false;
		}
		m_data[m_count++] = e;
		return true;
	}
	bool Remove(int e) {
		int pos = Find(e);
		if (pos == -1)
			return false;
		for (int i = pos + 1; i < m_count; i++) {
			m_data[i - 1] = m_data[i];
		}
		m_count--;
		return true;
	}
	Gather operator+(const Gather& g2) {
		Gather tmp = *this;
		int len = g2.GetCount();
		for (int i = 0; i < len; i++) {
			tmp.Add(g2.m_data[i]);
		}
		return tmp;
	}
	Gather operator-(const Gather& g2) {
		Gather tmp = *this;
		int len = g2.GetCount();
		for (int i = 0; i < len; i++) {
			tmp.Remove(g2.m_data[i]);
		}
		return tmp;
	}
	friend ostream& operator<<(ostream& dout, const Gather& g) {
		dout << "(";
		int len = g.GetCount();
		for (int i = 0; i < len; i++) {
			if (i == 0) {
				dout << g.m_data[i];
			}
			else {
				dout << "," << g.m_data[i];
			}
		}
		dout << ")";
		return dout;
	}
};
int main()
{
	Gather g1, g2;
	int x, y, a, b;
	cin >> x >> y;
	for (int i = x; i <= y; i++) {
		g1.Add(i);
	}
	g2 = g1;
	cout << "集合g2内容如下：" << g2 << endl;
	Gather g3 = g1;
	cin >> x >> y >> a >> b;
	g3.Remove(x);
	g3.Remove(y);
	g3.Add(a);
	g3.Add(b);
	cout << "集合g3内容如下：" << g3 << endl;
	cout << "集合g2与g3的差：" << g2 - g3 << endl;
	cout << "集合g2与g3的合：" << g2 + g3 << endl;
	return 0;
}
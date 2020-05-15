#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>
#include <map>
using namespace std;
void printMap(map<int, char>::iterator& temp);
int main() {
	vector<int> a{ 1,2,3,4,5,6};
	int arr[10];
	cout << "a is:" << endl;
	for (auto ptr = a.begin(); ptr != a.end(); ptr++) {
		cout << *ptr;
	}
	cout << endl;
	for (int i = 0; i < 10; i++) {
		arr[i] = i;
	}
	vector<int> b(arr, arr + sizeof(arr) / sizeof(arr[0]));
	cout << "b is:" << endl;
	for (auto ptrB = b.begin(); ptrB != b.end(); ptrB++) {
		cout << *ptrB;
	}
	cout << endl << b.size();

	cout << endl;
	b.assign(a.begin(), a.end());
	for (auto ptrBR = b.rbegin(); ptrBR != b.rend(); ptrBR++) {
		cout << *ptrBR;
	}
	cout << "---------------------" << endl;
	deque<int> que{ 1,2,3,4,5,6,7,8 };
	for (auto ptrC = que.begin(); ptrC != que.end(); ptrC++) {
		cout << *ptrC;
	}

	que.insert(que.begin()+6, 999);
	for (auto ptrC = que.begin(); ptrC != que.end(); ptrC++) {
		cout << *ptrC;
	}
	
	map<int, char> m{ {1,'v' }, {2, 'a'}};				//*****为花括号
	for (auto ptr = m.begin(); ptr != m.end(); ptr++) {
		cout << ptr->first << "->" << ptr->second;
	}
	m.find(1);
	//for_each(m.begin(), m.end(), printMap);

	cout << count(que.begin(), que.end(), 1);
	return 0;
}
void printMap(map<int,char>::iterator & temp) {
	cout << temp->first << "____" << temp->second;
}
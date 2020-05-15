#include <string>
#include <iostream>
using namespace std;

int main() {
	string sOne;
	string sTwo;
	int location;


	while (cin >> sOne,							//I should write this line although oj does't text some datas;
		cin >> sTwo,
		cin >> location) {
		sOne.insert(location - 1, sTwo);
		cout << sOne << endl;

		sOne = '\0';
		sTwo = '\0';
	}
	
	return 0;
}
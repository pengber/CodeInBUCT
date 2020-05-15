#include <string>
#include <iostream>
using namespace std;

int main() {
	string sOne;
	string sTwo;

	while(cin >> sOne) {
		cin >> sTwo;

		if ((sOne += sTwo).length() > 100) {
			cout << "Result String is cutted." << endl;	//There is a point after "cutted".!
		}
		else {
			cout << sOne << endl;
		}
	}
	


	return 0;
}
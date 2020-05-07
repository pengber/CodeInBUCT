#include <set>
#include <iostream>
using namespace std;

int main() {
	set<int> set1 = { 1,2 };
	set<int> set2 = { 1,2 };
	if (set1 == set2) {
		cout << "yes";
	}
	return 0;
}
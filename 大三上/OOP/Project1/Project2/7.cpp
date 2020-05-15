#include <iostream>
#include <iomanip>
using namespace std;

void fun(int arr[], int n) {
	int i, j;
	int min;
	int index;
	for (int i = 0; i < n; i++) {
		index = i;
		min = arr[i];
		for (int j = i + 1; j < n; j++) {
			if (arr[j] < min) {
				min = arr[j];
				index = j;
			}
		}
		int t = 0;
		t = arr[index];
		arr[index] = arr[i];
		arr[i] = t;
	}
	return;
}
void fun(double arr[], int n) {
	int i, j;
	double min;
	int index;
	for (int i = 0; i < n; i++) {
		index = i;
		min = arr[i];
		for (int j = i + 1; j < n; j++) {
			if (arr[j] < min) {
				min = arr[j];
				index = j;
			}
		}
		double t = 0;
		t = arr[index];
		arr[index] = arr[i];
		arr[i] = t;
	}
	return;
}

int main() {
	char choice;
	int n;
	int a1[1000];
	double a2[1000];
	cin >> choice;

	if (choice == 'i') {
		cin >> n;
		for (int i = 0; i < n; i++) {
			cin >> a1[i];
		}
		fun(a1, n);
		for (int i = 0; i < n; i++) {
			cout << a1[i] << " ";
		}
	}
	else if (choice == 'd') {
		cin >> n;
		for (int i = 0; i < n; i++) {
			cin >> a2[i];	
		}
		fun(a2, n);
		for (int i = 0; i < n; i++) {
			cout << setiosflags(ios::fixed) << showpoint << setprecision(2) <<a2[i]<< " ";
		}
	}
	return 0;
}
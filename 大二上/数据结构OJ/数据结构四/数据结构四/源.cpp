#include <iostream>
#include <iomanip>
using namespace std;
int returnWindow(int *, int, int);
int main() {
	int m, total, curWindow, tempTime, time = 0, waitTime = 0, curMan = 0, nextMan = 0;
	int window[20] = { 0 };					
	int man[2][200] = { 0 };				
	
	while (cin >> m >> total) {
		for (int i = 0; i < total; i++) {
			cin >> man[0][i];
			cin >> man[1][i];
		}
		for (time = 0; nextMan < total; time++) {
			for (curMan = nextMan; man[0][curMan] == time; nextMan = ++curMan) {
				curWindow = returnWindow(window, m, time);
				tempTime = window[curWindow] - man[0][curMan];
				waitTime += tempTime > 0 ? tempTime : 0;

				window[curWindow] += man[1][curMan];

			}
			for (int j = 0; j < m; j++) {
				while (window[j] <= time) {
					window[j] = time + 1;
				}
			}
		}
		cout << fixed << setprecision(2) << 1.0*waitTime / total << endl;

		for (int i = 0; i < m; i++) {
			window[i] = 0;
		}
		for (int j = 0; j < total; j++) {
			man[0][j] = man[1][j] = 0;
		}
		curWindow = tempTime = time = waitTime = curMan = nextMan = 0;

	}
	return 0;
}
int returnWindow(int * window, int m, int time) {
	int windowTime = window[0] - time;
	int theWindow = 0;

	for (int i = 0; i < m; i++) {
		if (windowTime >(window[i] - time)) {
			windowTime = (window[i] - time);
			theWindow = i;
		}
	}
	return theWindow;

}
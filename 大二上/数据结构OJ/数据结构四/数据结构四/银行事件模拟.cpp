#include <iostream>
#include <iomanip>
#include <string>
using namespace std;
int returnWindow(int *, int, int);			//返回应该排队的窗口
int main() {
	int m, total, curWindow, tempTime, time = 0, waitTime = 0, curMan = 0, nextMan = 0;
	//curWindow	:表示当前应该在哪个窗口班里业务
	//time		:表示现在处于什么时刻
	//waitTime	:需要等待总时间	
	//curMan	:现在哪个人需要办理业务
	//nextMan	:下一个办理业务的人
	int window[20] = { 0 };					//表示20个窗口,存储的数据表示前一业务班里完后的所处时刻
	int man[2][200] = { 0 };				//表示total个人,man[0][j]表示进门时刻,man[1[[j]表示所需时间

	cin >> m >> total;
	for (int i = 0; i < total; i++) {
		cin >> man[0][i];
		cin >> man[1][i];
	}
	cout << "总共有" << total << "个人办理业务" << endl;
	cout << "总共有" << m << "个窗口可以办理业务" << endl;
	cout << endl;
	for (time = 0; nextMan < total; time++) {
		for (curMan = nextMan; man[0][curMan] == time; nextMan = ++curMan) {
			cout << "第" << time << "时:";
			cout << "第" << curMan << "个人进入了";
			curWindow = returnWindow(window, m, time);
			cout << curWindow << "个窗口" << endl;
			cout << "他需要" << man[1][curMan] << "时间" << endl;
			cout << "此窗口" << "任务结束时间:" << window[curWindow] << endl;
			cout << "此前等待总时间:" << waitTime << endl;
			tempTime = window[curWindow] - man[0][curMan];		//tempTime表示窗口前一业务班里
			waitTime += tempTime > 0 ? tempTime : 0;
			cout << "他进来后等待总时间:" << waitTime << endl;
			window[curWindow] += man[1][curMan];
			cout << curWindow << "窗口结束时间变更为" << window[curWindow] << endl;
			cout << endl;
		}
		//处理没办理业务的窗口业务显示时间
		for (int j = 0; j < m; j++) {
			while (window[j] <= time) {		//窗口结束时间小于当前时间的,一律置为下一秒
				window[j] = time + 1;
			}
		}
	}

	cout << "所有客户业务办理成功!" << endl;
	system("pause");
	return 0;
}
//函数名称: int returnWindow(int * window, int m, int time)
//函数功能: 返回当前客户应该办理业务的序号
//注意事项: window[j] - time代表这个窗口此时需要执行业务时等待的时间,恒大于等于0,
//			应该比较的是每个窗口结束业务的时间和当前时间的差值,差值越小,说明等待
//			时间越小.
int returnWindow(int * window, int m, int time) {
	int windowTime = window[0] - time;
	int theWindow = 0;

	for (int i = 0; i < m; i++) {
		if (windowTime > (window[i] - time)) {
			windowTime = (window[i] - time);
			theWindow = i;
		}
	}
	return theWindow;

}
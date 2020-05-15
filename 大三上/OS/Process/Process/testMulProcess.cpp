#include<windows.h>
#include<iostream>
#include<tchar.h>
using namespace std;
int main() {

	DWORD processId = GetCurrentProcessId();//当前进程id
	DWORD sessionId;
	cout << processId << endl;
	if (ProcessIdToSessionId(processId, &sessionId)) {
		_tprintf(TEXT("Process '%u' runs in Terminal Services session '%u'"), processId, sessionId);//该函数在tchar.h中
	}
	else {
		_tprintf(TEXT("Unable to get Terminal Services session ID for process '%u'"), processId);
	}
	system("pause");
}
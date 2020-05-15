#include <Windows.h>
#include <iostream>

using namespace std;

int main()
{
	STARTUPINFO startupInfo = { 0 };
	PROCESS_INFORMATION processInformation = { 0 };

	BOOL bSuccess = CreateProcess(TEXT("C:\\Windows\\py.exe"), NULL, NULL, NULL, FALSE, NULL, NULL, NULL, &startupInfo, &processInformation);

	if (bSuccess)
	{
		cout << "Process started." << endl
			<< "Process ID:\t"
			<< processInformation.dwProcessId << endl;
	}
	else
	{
		cout << "Cannot start process!" << endl
			<< "Error code:\t" << GetLastError() << endl;
	}


	return system("pause");
}
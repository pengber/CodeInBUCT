#include "dos.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "windows.h"




//char current_directory[256] = "";//当前目录

//char format_file_name[32];//虚拟磁盘文件名



using namespace std;
using namespace DOS;

int main()
{
	/*char *content = new char [sizeof(FCB)];
		memset(content, 0, sizeof(FCB));
		cout<<content<<endl;
	return 0;*/
	while (1) {
		string cmd, str[10];
		int length;
		if (current_directory.length() == 0) {
			cout << "\\$ ";
		}
		else {
			cout << current_directory << "$ ";
		}
		getline(cin, cmd);
		length = split(cmd, str, ' ');
		toLowerCase(str[0]);


		if (str[0] == "exit") {
			exit(0);
		}
		else if (str[0] == "cls") {
			system("cls");
		}
		else if (str[0] == "help" || str[0] == "?") {
			help();
		}
		else if (str[0] == "format") {
			if (length == 3) {
				do_format(str[1], to_integer(str[2]), BLOCK_SIZE);
			}
			else {
				format();
			}
		}
		else if (str[0] == "info") {
			if (length == 2) {
				display_content(str[1]);
			}
			else if (length == 3) {
				display_content(str[1], str[2]);
			}
			else {
				//alert("Error command!");
			}
		}
		else if (str[0] == "md" && length == 2) {
			char aa[100];
			strcpy(aa, str[1].c_str());
			md(aa);
		}
		else if (str[0] == "dir") {
			dir();
		}
		else if (str[0] == "cd") {
			//char bb[100];
			//strcpy(bb, str[1].c_str());
			if (length == 2) {
				cd(str[1]);
			}
			else {
				string bb = "NULL";
				cd(bb);
			}
		}
		else if (str[0] == "mk" && length == 2) {
			char bb[100];
			strcpy(bb, str[1].c_str());
			mk(bb, 0, NULL);
		}
		else if (str[0] == "mk" && length == 3) {
			int size = to_integer(str[2]);
			if (size > 0) {
				char* content = (char*)malloc(size);
				memset(content, 0, size);
				char cc[100];
				strcpy(cc, str[1].c_str());
				mk(cc, size, content);
			}
		}
		else if (str[0] == "put" && length == 2) {
			string cc = "NULL";
			put(str[1], cc);
		}
		else if (str[0] == "put" && length == 3) {
			put(str[1], str[2]);
		}
		else if (str[0] == "rd" && length == 2) {
			rd(str[1]);
		}
		else if (str[0] == "del" && length == 2) {

		}
		else {
			//alert("Error command!");
		}
	}


	return 0;
}

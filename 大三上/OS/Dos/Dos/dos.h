#ifndef DOS_H_INCLUDED
#define DOS_H_INCLUDED
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <cmath>
#define LAST_BLOCK 0xFFFF//fat16
#define EMPTY_BLOCK 0x0000
#define BLOCK_SIZE 1024
#define BEEP 7


using namespace std;

typedef struct FCB {
	char name[8];//文件或者目录名
	int size;//文件或者目录字节数
	int first_block;//第一个块号
	char dateTime[15];//日期时间
	char type;//1.文件 2.目录 0.空闲
}FCB;


string current_directory = "";
string format_file_name = "";
int current_directory_block_no = 0;//当前目录块号

namespace DOS {
	void alert(char str[]) {
		cout << str << endl;
	}

	bool is_all_digits(string& str) {//判断是否为全数字
		for (int i = 0; i < str.length(); i++) {
			if (str[i] < '0' || str[i] > '9') {
				return false;
			}
		}
		return true;
	}

	int to_integer(string& str) {//字符串转化为数字
		if (is_all_digits(str)) {
			return atoi(str.c_str());
		}
		return -1;
	}

	bool is_power_of_two(int i) {//判断是否为2的整数次幂
		if (i % 2 != 0) {
			return false;
		}
		else {
			while (i != 1) {
				if (i % 2 != 0) {
					return false;
				}
				i = i / 2;
			}
		}
		return true;
	}

	void trim(char* str) {//去掉前后空格
		char* p = str;
		while (*p == ' ' || *p == '\t' || *p == '\r' || *p == '\n') {
			p++;
		}
		strcmp(str, p);
		int i = strlen(str) - 1;
		while (str[i] == ' ' || str[i] == '\t' || str[i] == '\r' || str[i] == '\n') {
			i--;
		}
		str[i + 1] = '\0';
	}

	void toUpperCase(string& str) {
		transform(str.begin(), str.end(), str.begin(), ::toupper);
	}

	void toLowerCase(string& str) {
		transform(str.begin(), str.end(), str.begin(), ::tolower);
	}

	int split(string& str, string ss[10], char ch) {//分割字符串
		int i = 0, j = 0, k = 0;
		while (str[i] == ch) {
			i++;
		}
		//       if(str[i] == 0) {
		//           return 0;
		//      }
		char a[10][40];
		int index = 0;
		for (; i < str.length(); i++) {
			if (str[i] != ch) {
				a[j][k++] = str[i];
			}
			else {
				a[j][k] = '\0';
				if (k != 0) {
					ss[index] = a[j];
					index++;
				}
				j++;
				k = 0;
			}
		}
		a[j][k] = '\0';
		if (k != 0) {
			ss[index] = a[j];
			index++;
		}
		return index;
	}

	void setDateTime(char dateTime[]) {
		time_t ticks = time(NULL);
		struct tm* t = localtime(&ticks);
		strftime(dateTime, 16, "%Y%m%d %H%M%S", t);
	}

	int get_block_count() {//获取块大小
		ifstream in(format_file_name.c_str(), ios::in | ios::binary | ios::ate);
		long size = in.tellg();
		in.close();
		return size / (BLOCK_SIZE + 2);
	}

	int get_file_size(string& str) {//获取文件大小
		ifstream in(str.c_str(), ios::in | ios::binary | ios::ate);
		long size = in.tellg();
		in.close();
		return size;
	}

	void read_fat(char* c) {
		ifstream in(format_file_name.c_str(), ios::in | ios::binary);
		if (!in.is_open()) {
			//alert("Failed to create file!!");
			return;
		}
		int length = get_block_count();
		in.read(c, 2 * length);
		in.close();
	}

	void write_fat(char* c) {
		FILE* fp = fopen(format_file_name.c_str(), "rb+");
		if (fp == NULL) return;
		fwrite(c, 2 * get_block_count(), 1, fp);
		fclose(fp);
	}

	void read_block(int block_no, char* str) {
		ifstream in(format_file_name.c_str(), ios::in | ios::binary);
		if (!in.is_open()) {
			//alert("Failed to create file!!");
			return;
		}
		in.seekg((get_block_count() * 2 + block_no * BLOCK_SIZE), ios::beg);
		in.read(str, BLOCK_SIZE);
		in.close();

	}

	void write_block(int block_no, char* str) {
		FILE* fp = fopen(format_file_name.c_str(), "rb+");
		if (fp == NULL) {
			return;
		}
		int i = get_block_count() * 2 + block_no * BLOCK_SIZE;
		fseek(fp, i, 0);
		fwrite(str, BLOCK_SIZE, 1, fp);
		fclose(fp);
	}

	int get_empty_block_num(int start) {//start开始以后后面第一个空闲块号
		char* fat;
		unsigned short* tmp;
		int blockNum = -1;
		int i, length;
		length = get_block_count();
		fat = new char[get_block_count() * 2];
		read_fat(fat);
		tmp = (unsigned short*)fat;
		for (i = 0; i < start; i++, tmp++);
		for (; i < length; i++, tmp++) {
			//cout<<(short *)*tmp<<endl;
			if (*tmp == EMPTY_BLOCK) {
				blockNum = i;
				break;
			}
		}
		delete[] fat;
		//cout<<blockNum<<endl;
		return blockNum;

	}

	void set_fat_item(int idx, unsigned short c) {//设置FAT表第idx项为c
		char* fat, * tmp;
		unsigned short* shortPnt;
		fat = new char[get_block_count() * 2];
		read_fat(fat);
		shortPnt = (unsigned short*)fat;
		*(shortPnt + idx) = c;
		//printf("%4x%d",c,idx);
		write_fat(fat);
		delete[] fat;
	}

	char get_fat_item(int idx) {
		char* fat, * tmp;
		fat = new char[get_block_count() * 2];
		read_fat(fat);
		char c = *(fat + idx);
		delete[] fat;
		return c;
	}

	bool is_valid_name(string& str) {//判断文件名是否符合规矩
		if (str.find("\\", 0) != -1) {
			//alert("The file or directory name includes illegal characters");
			return false;
		}
		else if (str.length() > 8) {
			//alert("The file or directory name can not exceed 8 characters");
			return false;
		}
		else if (str == "." || str == "..") {
			//alert("The file or directory name can not make '.' Or '..'");
			return false;
		}
		return true;
	}

	void display_vd_content(int pos, int length) {//显示内容核心
		ifstream in(format_file_name.c_str(), ios::binary | ios::in);
		if (!in.is_open()) {
			//alert("Failed to open file!!");
			return;
		}
		in.seekg(pos, ios::beg);
		int  i = 0;
		char c;
		while (i < length) {
			printf("%08d  ", pos + i);
			for (int j = 0; j < 16; j++) {
				char tmp[20];
				in.read(&c, 1);
				if (in.eof()) {
					break;
				}
				sprintf(tmp, "%02x", c);
				if (strlen(tmp) > 2) {
					string tmm = tmp;
					cout << tmm.substr(strlen(tmp) - 2, 2) << " ";
				}
				else {
					printf("%02x ", c);
				}
				i++;
			}
			in.seekg(-16, ios::cur);
			cout << "  ";
			for (int j = 0; j < 16; j++) {
				in.read(&c, 1);
				if (in.eof()) {
					break;
				}
				if (c > 13 && c < 127) {
					cout << c;
				}
				else {
					cout << ".";
				}
			}

			cout << endl;
		}
		in.close();
	}

	void display_content(string& str1, string& str2) {//显示内容
		int start = to_integer(str1);
		if (start >= 0) {
			int length = to_integer(str2);
			if (length > 0) {
				display_vd_content(start, length);
			}
			else {
				display_vd_content(start, 256);
			}
		}
		else {

		}
	}

	void display_content(string& str1) {

		toLowerCase(str1);

		if (str1 == "fat") {
			ifstream in(format_file_name.c_str(), ios::in | ios::binary | ios::ate);
			long size = in.tellg();
			in.close();
			display_vd_content(0, (size / (BLOCK_SIZE + 2)) * 2);
		}
	}

	void write_directory_content(int block_no, int parent_block_no, char* dateTime) {
		char* directory_content = new char[BLOCK_SIZE];
		memset(directory_content, 0, BLOCK_SIZE);
		FCB* tmp = (FCB*)directory_content;
		strcpy(tmp->name, ".");
		strcpy(tmp->dateTime, dateTime);
		tmp->size = BLOCK_SIZE;
		tmp->first_block = block_no;
		tmp->type = 2;
		tmp++;
		strcpy(tmp->name, "..");
		strcpy(tmp->dateTime, dateTime);
		tmp->size = BLOCK_SIZE;
		tmp->first_block = parent_block_no;
		tmp->type = 2;
		tmp++;
		write_block(block_no, directory_content);
		delete[]directory_content;
	}

	void do_format(string& str, int integer, int Bsize) {//创建FAT表文件
		if (!is_power_of_two(integer)) {
			//alert("Not the power of 2");
		}
		else if (integer > 65535) {//64K minus FAT minus 0000
			//alert("Exceeds the maximum memory range");
		}
		else {
			ofstream out(str.c_str(), ios::out | ios::binary);
			if (!out.is_open()) {
				//alert("Failed to create file!!");
			}
			else {
				format_file_name = str;
				cout << "Formatting:  " << str << ", BlockSize:  " << Bsize << ", BlockNum:  " << integer << endl;

				int myByte = LAST_BLOCK;
				out.write((char*)&myByte, 2);
				myByte = EMPTY_BLOCK;
				for (int i = 0; i < integer - 1; i++) {
					out.write((char*)&myByte, 2);
				}
				char buf[BLOCK_SIZE];
				memset(buf, 0, BLOCK_SIZE);
				for (int i = 0; i < integer; i++) {
					out.write(buf, BLOCK_SIZE);
				}
				char dateTime[15];
				setDateTime(dateTime);
				write_directory_content(0, 0, dateTime);
				out.close();
			}
		}
	}




	void format() {
		string aa = "a";
		do_format(aa, 32, BLOCK_SIZE);
	}

	void help() {

	}


	FCB* get_directory_item(FCB* content, int type, char* name) {
		FCB* tmp = content;
		for (int i = 0; i < BLOCK_SIZE / sizeof(FCB); i++, tmp++) {
			if (tmp->type == type) {
				if (strcmp(tmp->name, name) == 0) {
					return tmp;
				}
			}
		}
		return NULL;
	}


	void md(char* name) {//创建目录
		string ss = name;
		if (!is_valid_name(ss)) {
			return;
		}
		FCB* directory_content = new FCB[BLOCK_SIZE];
		read_block(current_directory_block_no, (char*)directory_content);
		if (get_directory_item(directory_content, 1, name) != NULL || get_directory_item(directory_content, 2, name) != NULL) {
			//alert("Directory name is occupied");
			delete[] directory_content;
			return;
		}

		int block_no = get_empty_block_num(0);
		if (block_no < 0) {
			//alert("insufficient space in drive");
			delete[] directory_content;
			return;
		}
		FCB* tmp = directory_content;
		for (int i = 0; i < BLOCK_SIZE / sizeof(FCB); i++, tmp++) {
			if (tmp->type == 0) {
				char dateTime[15];
				setDateTime(dateTime);
				strcpy(tmp->name, name);
				tmp->size = BLOCK_SIZE;
				tmp->first_block = block_no;
				strcpy(tmp->dateTime, dateTime);
				tmp->type = (char)2;
				write_block(current_directory_block_no, (char*)directory_content);
				set_fat_item(block_no, LAST_BLOCK);
				delete[] directory_content;
				write_directory_content(block_no, current_directory_block_no, dateTime);
				return;
			}
		}

	}

	void rd(string& name) {//删除目录
		char aa[100];
		strcpy(aa, name.c_str());
		if (!is_valid_name(name)) {
			return;
		}
		FCB* directory_content = new FCB[BLOCK_SIZE];
		read_block(0, (char*)directory_content);
		FCB* tmp, * tmp2;
		tmp = directory_content;
		tmp2 = get_directory_item(directory_content, 2, aa);
		if (tmp2 != NULL) {
			char* content = new char[BLOCK_SIZE];
			memset(content, 0, BLOCK_SIZE);
			int block_no = tmp2->first_block;
			cout << block_no << endl;

			write_block(block_no, content);
			set_fat_item(block_no, EMPTY_BLOCK);
			memset((char*)tmp2, 0, sizeof(FCB));
			write_block(0, (char*)directory_content);
			delete[] directory_content;


		}
		else {
			cout << "Not Find Name" << endl;
		}
	}

	void dir() {//显示目录
		FCB* directory_content = new FCB[BLOCK_SIZE];
		read_block(current_directory_block_no, (char*)directory_content);
		FCB* tmp = directory_content;
		for (int i = 0; i < BLOCK_SIZE / sizeof(FCB); i++, tmp++) {
			if (tmp->type == 1 || tmp->type == 2) {
				int type = tmp->type;
				if (tmp->first_block >= 0) {
					printf("%d\t", tmp->first_block);
				}
				else {
					printf("\t");
				}

				*(tmp->dateTime + 15) = 0;
				printf("%s\t", tmp->dateTime);
				if (type == 2) {
					printf("<DIR>\t");
				}
				else {
					printf("%d\t", tmp->size);
				}
				printf("%s\n", tmp->name);
			}
		}
		delete[]directory_content;
	}

	void cd(string& name) {//定位

		if (name == "NULL") {
			if (current_directory.length() == 0) {
				cout << "\\ " << endl;
			}
			else {
				cout << current_directory << endl;
			}
		}
		else if (name == ".") {
			return;
		}
		else if (name == "\\") {
			current_directory_block_no = 0;
			current_directory = "";
			return;
		}
		else {
			FCB* directory_content = new FCB[BLOCK_SIZE];
			read_block(current_directory_block_no, (char*)directory_content);
			char name1[100];
			strcpy(name1, name.c_str());
			FCB* tmp = get_directory_item(directory_content, 2, name1);
			if (tmp == NULL) {
				//alert("Not Find Contents");
			}
			else {
				current_directory_block_no = tmp->first_block;
				current_directory += "\\";
				current_directory += name1;
			}
			delete[]directory_content;
		}

	}

	void mk(char* name, int size, char* content) {//创建文件
		string ss = name;
		if (!is_valid_name(ss)) {
			return;
		}
		FCB* directory_content = new FCB[BLOCK_SIZE];
		read_block(current_directory_block_no, (char*)directory_content);
		if (get_directory_item(directory_content, 1, name) != NULL || get_directory_item(directory_content, 2, name) != NULL) {
			//alert((char *)("Directory name is occupied"));
			delete[] directory_content;
			return;
		}

		int block_no = get_empty_block_num(0);
		if (block_no < 0) {
			//alert("insufficient space in drive");
			delete[] directory_content;
			return;
		}


		FCB* tmp = directory_content;
		for (int i = 0; i < BLOCK_SIZE / sizeof(FCB); i++, tmp++) {
			if (tmp->type == 0) {
				char dateTime[15];
				setDateTime(dateTime);
				strcpy(tmp->name, name);
				strcpy(tmp->dateTime, dateTime);
				tmp->type = (char)1;
				tmp->size = size;
				if (size > 0) {
					tmp->first_block = block_no;
					int block_count = (int)ceil(size / (double)BLOCK_SIZE);
					int* block_numbers = new int[sizeof(int) * block_count];
					*block_numbers = block_no;
					for (int j = 1; j < block_count; j++) {
						*(block_numbers + j) = get_empty_block_num(*(block_numbers + j - 1) + 1);
						if (*(block_numbers + j) == -1) {
							//alert("There is not enough memory space");
							delete[] block_numbers;
							delete[] directory_content;
							return;
						}
					}
					for (int j = 0; j < block_count; j++) {
						if ((j + 1) == block_count) {
							set_fat_item(*(block_numbers + j), LAST_BLOCK);
						}
						else {
							set_fat_item(*(block_numbers + j), *(block_numbers + j + 1));
						}
						write_block(*(block_numbers + j), (char*)(content + BLOCK_SIZE * j));

					}
					delete[] block_numbers;


				}
				else {
					tmp->first_block = -1;
				}
				write_block(current_directory_block_no, (char*)directory_content);
				delete[] directory_content;

				return;
			}
		}
		//alert("The parent directory is full");
		delete[] directory_content;
	}

	void del(string& name) {//删除文件

	}

	void put(string& src, string& dest) {
		FILE* fp = fopen(src.c_str(), "rb");
		if (fp == NULL) {
			//alert("Did not find the local file");
		}
		else {
			int size = get_file_size(src);
			char* content = new char[(int)(ceil(size / (double)BLOCK_SIZE)) * BLOCK_SIZE];
			memset(content, 0, ceil(size / (double)BLOCK_SIZE) * BLOCK_SIZE);
			fread(content, size, 1, fp);
			if (dest == "NULL") {
				char aa[100];
				strcpy(aa, src.c_str());
				mk(aa, size, content);
			}
			else {
				char bb[100];
				strcpy(bb, dest.c_str());
				mk(bb, size, content);
			}
			delete[] content;
		}
		fclose(fp);
	}

}



#endif // DOS_H_INCLUDED

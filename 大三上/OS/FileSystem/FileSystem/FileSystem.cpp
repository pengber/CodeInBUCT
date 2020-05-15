#include "DiskOeprate.h"
#include "FileOperate.h"


int main() {
	initSystem();
	FileSystem system;
	system.showDir();
	system.createDirectory((char*)"1d");
	system.showDir();
	system.createFile((char*)"1f", 30);
	system.showDir();

	char content[20];
	for (int i = 0; i < 20; i++) {
		content[i] = 'A' + i;
	}
	system.write((char*)"1f", content);
	system.read((char*)"1f", 5);
	printf("\n");
	system.read((char*)"1f", 10);

	for (int i = 0; i < 20; i++) {
		content[i] = 'a' + i;
	}
	system.reWrite((char*)"1f", content);
	system.read((char*)"1f", 10);

	system.changeDir((char*)"1d");
	system.showDir();
	system.createFile((char*)"1_1f",10);
	system.showDir();

	system.deleteFile((char*)"1_1f");
	system.showDir();
	getchar();
	return 0;
}
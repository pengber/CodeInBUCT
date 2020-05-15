#pragma once
#include <string.h>
#include <stdio.h>
#include "DiskOeprate.h"
/*
	这里定义的目录项结构对应的是索引节点+FCB,一个目录项结构的内容是文件名，文件类型，文件大小，属性等等信息，而这里只定义额文
	件名和文件类型，再加一个FCB的索引
*/
//目录项结构（占用64B大小）：
struct dirUnit {
	char fileName[59];
	char type;								//文件类型，0为目录，1为文件，如果是文件的化，FCB起始盘块存储的是数据文件的FCB，而如果是目录的话，则存放目录表(目录文件的FCB）
	int startBlock;							//FCB起始盘块
};

/*
因为目录表的存储空间是一个盘块1024B，而一个目录项为64B，所以全部存储目录项的话可以存储1024/64=16个，但是还有一个4B大小的dirUnitAmount需要存储，所以只能存储15个啦
*/
#define DIRTABLE_MAX_SIZE 15
//目录表结构：（树形目录）
struct dirTable {
	int dirUnitAmount;						//这一层目录项的数目
	dirUnit dirs[DIRTABLE_MAX_SIZE];		//目录项列表
};

struct FCB {
	int blockOrder;							//文件数据盘块们的起始盘块号
	int fileSize;							//文件大小，盘块为单位
	int dataSize;							//已经写入的内容大小，字节为单位，文件类型为顺序文件
	int readPtr;							//读指针，字节为单位
	int link;								//文件链接数，用于文件共享
};

class FileSystem {
private:
	dirTable* rootDirTable;					//根目录
	dirTable* currentDirTable;				//当前所在目录
	char path[200];
	//创建文件辅助函数
	void createFCB(int FCBBlockOrder, int fileBlockOrder, int fileSize);
	int addDirUnit (char fileName[], int type, int FCBStartBlock);
	int findUnitInTable(char unitName[]);
	//删除文件辅助函数
	void releaseFile(int FCBBlockOrder);			//根据文件所在DirTable位置，释放对应FCB表的空间
	void deleteUnitInTable(int unitIndex);
	//写文件辅助函数
	int doWrite(FCB* myFCB, char content[]);
	//读文件辅助函数
	int doRead(FCB* myFCB, int length);
	//创建目录辅助函数
	int addDirUnitForNew(dirTable* newTable, char fileName[], int type, int FCBStartBlock);
	//创建目录时必须向新创建的目录项中添加父目录的地址

public:
	FileSystem();
	//
	void showDir();
	int changeDir(char dirName[]);
	int changeName(char oldName[], char newName[]);
	//文件相关操作
	int createFile(char fileName[], int fileSize);
	int deleteFile(char fileName[]);
	int write(char fileName[], char content[]);//从文件尾部写内容
	int reWrite(char fileName[], char content[]);//清空文件，从头写入
	int read(char fileName[], int length);	//从上次读取文件位置后在读取size大小
	int reRead(char fileName[], int length);	//从头读取
	//目录相关操作
	int createDirectory(char directoryName[]);
};
void FileSystem::createFCB(int FCBBlockOrder, int fileBlockOrder, int fileSize) {
	FCB* FCBPtr = (FCB*)getBlockAddr(FCBBlockOrder);//现根据FCB表的盘块号得到物理地址
	FCBPtr->blockOrder = fileBlockOrder;
	FCBPtr->fileSize = fileSize;
	FCBPtr->dataSize = 0;					//刚创建文件，写入为0
	FCBPtr->link = 1;
FCBPtr->readPtr = 0;
return;
}
int FileSystem::addDirUnit(char fileName[], int type, int FCBStartBlock) {
	int dirUnitNum = currentDirTable->dirUnitAmount;
	if (dirUnitNum == DIRTABLE_MAX_SIZE) {
		printf("dirTable is full,try to delete some file\n");
		return -1;
	}
	if (findUnitInTable(fileName) != -1) {
		printf("file already exits\n");
		return -1;
	}
	dirUnit* newDirUnit = &(currentDirTable->dirs[currentDirTable->dirUnitAmount]);
	currentDirTable->dirUnitAmount++;//当前目录的目录表项数量+1
	strcpy(newDirUnit->fileName, fileName);
	newDirUnit->type = type;
	newDirUnit->startBlock = FCBStartBlock;

	return 0;
}

int FileSystem::addDirUnitForNew(dirTable* newTable,char fileName[], int type, int FCBStartBlock) {
	int dirUnitNum = newTable->dirUnitAmount;
	if (dirUnitNum == DIRTABLE_MAX_SIZE) {
		printf("dirTable is full,try to delete some file\n");
		return -1;
	}
	
	dirUnit* newDirUnit = &(newTable->dirs[newTable->dirUnitAmount]);
	newTable->dirUnitAmount++;//当前目录的目录表项数量+1
	strcpy(newDirUnit->fileName, fileName);
	newDirUnit->type = type;
	newDirUnit->startBlock = FCBStartBlock;

	return 0;
}

//返回文件名所对应的目录项，没有则返回-1
int FileSystem::findUnitInTable(char unitName[])
{
	//获得目录表
	int dirUnitAmount = currentDirTable->dirUnitAmount;
	int unitIndex = -1;
	for (int i = 0; i < dirUnitAmount; i++)//查找目录项位置
		if (strcmp(unitName, currentDirTable->dirs[i].fileName) == 0)
			unitIndex = i;
	return unitIndex;
}
void FileSystem::releaseFile(int FCBBlockOrder) {
	FCB* FCBStart = (FCB*)getBlockAddr(FCBBlockOrder);
	FCBStart->link--;
	if (FCBStart != 0) { return; }

	releaseBlock(FCBStart->blockOrder, FCBStart->fileSize);//释放文件的空间
	releaseBlock(FCBBlockOrder, 1);			//释放FCB表所占空间
	return;
}
void FileSystem::deleteUnitInTable(int unitIndex) {
	for (int i = unitIndex; i < currentDirTable->dirUnitAmount - 1; i++) {
		currentDirTable->dirs[i] = currentDirTable->dirs[i + 1];
	}
	currentDirTable->dirUnitAmount--;
	return;
}
int FileSystem::doWrite(FCB* myFCB, char content[]) {

	int contentLen = strlen(content);
	char* dataStart = getBlockAddr(myFCB->blockOrder);
	dataStart += myFCB->dataSize;
	int i;
	for (i = 0; myFCB->dataSize + i < myFCB->fileSize && i < contentLen; i++) {
		*(dataStart + i) = content[i];
	}
	myFCB->dataSize += i-1;
	if (myFCB->dataSize == myFCB->fileSize) {
		printf("file is full\n");
	}
	return 0;
}
int FileSystem::doRead(FCB* myFCB, int length) {
	int dataSize = myFCB->dataSize;
	char* dataStart = getBlockAddr(myFCB->blockOrder);
	dataStart += myFCB->readPtr;
	int i;
	for (i = 0; myFCB->readPtr + i < myFCB->fileSize && i < length; i++) {
		printf("%c",*(dataStart + i));
	}
	myFCB->readPtr += i;
	if (myFCB->readPtr == myFCB->fileSize) printf("#");
	printf("\n");

	return 0;
}


/****************************************公有成员函数**************************************/
FileSystem::FileSystem() {
	int startBlock = getBlock(1);
	if (startBlock == -1) {
		return;
	}
	rootDirTable = (dirTable*)getBlockAddr(startBlock);
	rootDirTable->dirUnitAmount = 0;
	currentDirTable = rootDirTable;
	path[0] = '\\';
	path[1] = '\0';
}
void FileSystem::showDir()
{
	int unitAmount = currentDirTable->dirUnitAmount;
	printf("total:%d\n", unitAmount);
	printf("name\ttype\tsize\tFCB\tdataStartBlock\n");
	//遍历所有表项
	for (int i = 0; i < unitAmount; i++)
	{
		//获取目录项
		dirUnit unitTemp = currentDirTable->dirs[i];
		printf("%s\t%d\t", unitTemp.fileName, unitTemp.type);
		//该表项是文件，继续输出大小和起始盘块号
		if (unitTemp.type == 1)
		{
			int FCBBlock = unitTemp.startBlock;
			FCB* fileFCB = (FCB*)getBlockAddr(FCBBlock);
			printf("%d\t%d\t%d\n", fileFCB->fileSize, FCBBlock, fileFCB->blockOrder);
		}
		else {
			int dirBlock = unitTemp.startBlock;
			dirTable* myTable = (dirTable*)getBlockAddr(dirBlock);
			printf("%d\t%d\n", myTable->dirUnitAmount, unitTemp.startBlock);
		}
	}
}

//切换目录 cd
int FileSystem::changeDir(char dirName[])
{
	//目录项在目录位置
	int unitIndex = findUnitInTable(dirName);
	//不存在
	if (unitIndex == -1)
	{
		printf("file not found\n");
		return -1;
	}
	if (currentDirTable->dirs[unitIndex].type == 1)
	{
		printf("not a dir\n");
		return -1;
	}
	//修改当前目录
	int dirBlock = currentDirTable->dirs[unitIndex].startBlock;
	currentDirTable = (dirTable*)getBlockAddr(dirBlock);
	//修改全局绝对路径
	if (strcmp(dirName, "..") == 0)
	{
		//回退绝对路径
		int len = strlen(path);
		for (int i = len - 2; i >= 0; i--)
			if (path[i] == '\\')
			{
				path[i + 1] = '\0';
				break;
			}
	}
	else {
		strcat(path, dirName);
		strcat(path, "\\");
	}

	return 0;
}
//修改文件名或者目录名 mv
int FileSystem::changeName(char oldName[], char newName[])
{
	int unitIndex = findUnitInTable(oldName);
	if (unitIndex == -1)
	{
		printf("file not found\n");
		return -1;
	}
	strcpy(currentDirTable->dirs[unitIndex].fileName, newName);
	return 0;
}
int FileSystem::createFile(char fileName[], int fileSize) {
	if (strlen(fileName) >= 59) {
		printf("file name is too long\n");
		return -1;
	}
	//申请空间
	int FCBBlockOrder = getBlock(1);
	if (FCBBlockOrder == -1) return -1;

	int fileBlockOrder = getBlock(fileSize);
	if (fileBlockOrder == -1) {
		releaseBlock(FCBBlockOrder, 1);//收回刚才分配的fcb表的盘块
		return -1;
	}
	//创建FCB表
	createFCB(FCBBlockOrder, fileBlockOrder, fileSize);

	//在目录项中添加
	if (addDirUnit(fileName, 1, FCBBlockOrder) == -1) {
		return -1;
	}
}
int FileSystem::deleteFile(char fileName[]) {
	if (strcmp(fileName, "..") == 0) {
		printf("Can not delete the father file");
		return -1;
	}
	int index = findUnitInTable(fileName);
	if (index == -1) {
		printf("Can not find this file in current directory table\n");
		return -1;
	}

	if (currentDirTable->dirs[index].type == 0) {
		printf("this is a directory, not file, so you can't delete this\n");
		return -1;
	}
	releaseFile(index);
	deleteUnitInTable(index);
}
//写文件：找到文件（找不到返回,是目录返回）->根据FCB表信息，往file里面写
int FileSystem::write(char fileName[], char content[]) {
	int index = findUnitInTable(fileName);
	if (index == -1) {
		printf("Can not find this file in current directory table\n");
		return -1;
	}
	if (currentDirTable->dirs[index].type == 0) {
		printf("this file is a directory, you can't wirte");
		return -1;
	}
	FCB* FCBStart = (FCB*)(getBlockAddr(currentDirTable->dirs[index].startBlock));
	doWrite(FCBStart, content);
	return 0;
}
//重写文件
int FileSystem::reWrite(char fileName[], char content[]) {
	int index = findUnitInTable(fileName);
	if (index == -1) {
		printf("Can not find this file in current directory table\n");
		return -1;
	}
	if (currentDirTable->dirs[index].type == 0) {
		printf("this file is a directory, you can't wirte");
		return -1;
	}
	FCB* FCBStart = (FCB*)(getBlockAddr(currentDirTable->dirs[index].startBlock));
	FCBStart->readPtr= 0;					//重置读指针和已写入大小
	FCBStart->dataSize = 0;
	doWrite(FCBStart, content);
	return 0;
}
//读文件
int FileSystem::read(char fileName[], int length) {
	int index = findUnitInTable(fileName);
	if (index == -1) {
		printf("Can not find this file in current directory table\n");
		return -1;
	}
	if (currentDirTable->dirs[index].type == 0) {
		printf("this file is a directory, you can't wirte");
		return -1;
	}
	FCB* FCBStart = (FCB*)(getBlockAddr(currentDirTable->dirs[index].startBlock));
	doRead(FCBStart, length);
}
int FileSystem::reRead(char fileName[], int length) {
	int index = findUnitInTable(fileName);
	if (index == -1) {
		printf("Can not find this file in current directory table\n");
		return -1;
	}
	if (currentDirTable->dirs[index].type == 0) {
		printf("this file is a directory, you can't wirte");
		return -1;
	}
	FCB* FCBStart = (FCB*)(getBlockAddr(currentDirTable->dirs[index].startBlock));
	FCBStart->readPtr = 0;
	doRead(FCBStart, length);
}
int FileSystem::createDirectory(char directoryName[]) {
	if (strlen(directoryName) >= 59) {
		printf("file name is too long\n");
		return -1;
	}
	//申请空间
	int dirBlock = getBlock(1);
	if (dirBlock == -1) return -1;

	addDirUnit(directoryName, 0, dirBlock);//现添加到本层目录里面

	//为新建目录建立目录表
	dirTable* dirTablePtr = (dirTable*)getBlockAddr(dirBlock);

	dirTablePtr->dirUnitAmount = 0;
	char parent[] = "..";

	if (addDirUnitForNew(dirTablePtr,parent, 0, getBlockOrder((char*)currentDirTable)) == -1) {
		printf("parent file did not success");
		return -1;
	}
	return 0;
}
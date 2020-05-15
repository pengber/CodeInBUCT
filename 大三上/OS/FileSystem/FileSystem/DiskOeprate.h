#pragma once
#include <stdio.h>
#include <stdlib.h>
#define SYSTEM_SIZE 100 * 1024 * 1024 //假设系统空间100MB
#define BLOCK_SIZE 1024						//规定块大小为1024B
#define BLOCK_NUM SYSTEM_SIZE/BLOCK_SIZE	//盘块总数量

//初始化系统
void initSystem();

//根据所需盘块大小分配盘块，返回分配盘块的起始盘块号
int getBlock(int blockSize);

//得到盘块号对应的物理空间位置
char* getBlockAddr(int blockOrder);

//得到物理空间地址对应的盘块号
int getBlockOrder(char* blockAddr);

//根据起始盘块号和总盘块数量释放盘块们
int releaseBlock(int blockOrder, int blockSize);

//退出系统
void exitSystem();


char* systemStartAddr;  //系统起始地址

//初始化系统
void initSystem()
{
	//创建空间
	systemStartAddr = (char*)malloc(SYSTEM_SIZE * sizeof(char));
	//初始化盘块的位示图
	for (int i = 0; i < BLOCK_NUM; i++)
		systemStartAddr[i] = '0';
	//用于存放位示图的空间已被占用
	int bitMapSize = BLOCK_NUM * sizeof(char) / BLOCK_SIZE;//位示图占用盘块数:100
	for (int i = 0; i < bitMapSize; i++)//从零开始分配
		systemStartAddr[i] = '1';   //盘块已被使用
}
//退出系统
void exitSystem()
{
	free(systemStartAddr);
}
//磁盘分配
int getBlock(int blockSize)
{
	int startBlock = 0;
	int sum = 0;
	for (int i = 0; i < BLOCK_NUM; i++)
	{
		if (systemStartAddr[i] == '0')//可用盘块
		{
			if (sum == 0)//刚开始，设置开始盘块号
				startBlock = i;
			sum++;
			if (sum == blockSize)//连续盘块是否满足需求
			{
				//满足分配，置1
				for (int j = startBlock; j < startBlock + blockSize; j++)
					systemStartAddr[j] = '1';
				return startBlock;
			}

		}
		else//已被使用,连续已经被打断
			sum = 0;
	}
	printf("not found such series memory Or memory is full\n");
	return -1;
}
//获得盘块的物理地址
char* getBlockAddr(int blockNum)
{
	return systemStartAddr + blockNum * BLOCK_SIZE; //偏移量单位为字节
}
//获得物理地址的盘块号
int getBlockOrder(char* addr)
{
	return (addr - systemStartAddr) / BLOCK_SIZE;
}
//释放盘块、
int releaseBlock(int blockNum, int blockSize)
{
	int endBlock = blockNum + blockSize;
	//修改位示图盘块的位置为0
	for (int i = blockNum; i < endBlock; i++)
		systemStartAddr[i] = '0';
	return 0;
}

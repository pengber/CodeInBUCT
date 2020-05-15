/*************************************************************************************
*Author	:Pengber
*Version	:1.0
*Date		:2018/11/28
**************************************************************************************/
/*************************************************************************************
*Problem	:

*Tips:		:

*************************************************************************************/
/*************************************************************************************
*History	:
**************************************************************************************/
#ifndef HUFFMANCOMPRESS_H_INCLUDE
#define HUFFMANCOMPRESS_H_INCLUDE

#include "BufferType.h"
#include "HuffmanTree.h"
#include <ios>
#include <iostream>
class HuffmanCompress {
private:
	HuffmanTree<char, unsigned long> * m_pHuffmanTree;			//p代表指针
	FILE * m_infp, *m_outfp;
	BufferType m_buffer;

	void write(unsigned int bit);
	void writeOutfp();
public:

	HuffmanCompress();

	~HuffmanCompress();

	void enCompress();

	void deCompress();
};
/************************************私有成员函数**************************************/
void HuffmanCompress::write(unsigned int bit) {
	m_buffer.m_bits++;
	m_buffer.m_character = (m_buffer.m_character << 1) | bit;

	if (m_buffer.m_bits == 8) {
		fputc(m_buffer.m_character, m_outfp);
		m_buffer.initBuffer();
	}
}
void HuffmanCompress::writeOutfp() {
	unsigned int len = m_buffer.m_bits;     // 当前缓存中实际比特数目

	if (len > 0)     // 只要缓冲区不是空的
	{   // 就将缓存周边的比特数目增加到8, 自动写入文件中
		for (unsigned int i = 0; i < 8 - len; i++)
		{
			write(0);
		}
	}
}
void HuffmanCompress::enCompress() {
	const unsigned long maxSize = 256;
	char infName[maxSize], outfName[maxSize];

	std::cout << "请输入文件名:" << std::endl;
	std::cin >> infName;

	if ((this->m_infp = fopen(infName, "rb")) == NULL) {
		std::cout << "文件名有误,请重新输入!" << std::endl;
		return;
	}

	rewind(m_infp);

	std::cout << "请输入目标文件名:" << std::endl;
	std::cin >> outfName;                 // 输入目标文件名
	if ((this->m_outfp = fopen(outfName, "wb")) == NULL) {
		std::cout << "输出文件名有误,请重新输入!" << std::endl;
		return;
	}

	std::cout << "正在编码,请稍后..." << std::endl;

	char chars[maxSize];
	unsigned long weight[maxSize] = { 0 };
	unsigned long i, size;					//size表示输入文件里面的字符数
	char charType;

	rewind(m_infp);
	for (i = 0; i < maxSize; i++) {
		chars[i] = (char)(i);
	}

	while ((charType = fgetc(m_infp)) != EOF) {
		weight[(unsigned char)charType]++;
		size++;
	}

	if (m_pHuffmanTree != NULL) {
		m_pHuffmanTree = NULL;
	}

	this->m_pHuffmanTree->createHuffmanTree(chars, weight, maxSize);

	m_buffer.initBuffer();
	rewind(m_infp);
	rewind(m_outfp);

	while ((charType = fgetc(m_infp)) != EOF) {
		std::string stringTemp = this->m_pHuffmanTree->enCode(charType);

		for (i = 0; i < stringTemp.size(); i++) {
			if (stringTemp[i] == 0) {
				write(0);
			}
			else if (stringTemp[i] == 1) {
				write(1);
			}
		}
	}
	this->writeOutfp();
	fclose(this->m_infp);       // 关闭源文件
	fclose(this->m_outfp);      // 关闭目标文件
	std::cout << "处理结束..." << std::endl;
}
/*===============================私有成员函数实现完毕=================================*/
#endif // !HUFFMANCOMPRESS_H_INCLUDE

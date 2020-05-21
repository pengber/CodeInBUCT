/*************************************************************************************
*Author	:Pengber
*Version	:1.0
*Date		:2018/10/16
**************************************************************************************/
/*************************************************************************************
*Problem	:
			1.未将已得出的编码存入charCodes中,需了解string类的有关知识
			2.解码啥的都没有编写
			3.deCode返回的是函数内创建对象的指针,我觉得有些不合适
*Tips:		:

*************************************************************************************/
/*************************************************************************************
*History	:
**************************************************************************************/
#ifndef HUFFMANTREE_H_INCLUDE
#define HUFFMANTREE_H_INCLUDE
#include "HuffmanTreeNode.h"
#include "SimpleLinkList.h"					//暂存字符编码需要
#include <assert.h>
#include <iostream>
#include <string>

#define DEBUG
#define SHOW

template <class CharType, class WeightType>
class HuffmanTree {
protected:
	HuffmanTreeNode<WeightType> * m_nodes;
	CharType * m_leafChars;
	std::string * m_leafCharCodes;
	int m_curPos;
	int m_size;

	void selectHelp(int cur, int & minOne, int & minTwo);
	void createHuffmanTreeHelp(CharType * chars, WeightType * weight, int size);
public:
	HuffmanTree();
	HuffmanTree(CharType * chars, WeightType * weight, int size);
	virtual ~HuffmanTree();

	void createHuffmanTree(CharType * chars, WeightType * weight, int size);
	std::string enCode(CharType  ch);
	std::string deCode(std::string strCode);

};
template <class CharType, class WeightType>
void HuffmanTree<CharType, WeightType>::selectHelp(int cur, int & minOne, int & minTwo) {
#ifndef DEBUG
	std::cout << "FUN:" << __func__ << ",LINE:" << __LINE__ << std::endl;
#endif // !DEBUG
	minOne = minTwo = 0;

	for (int pos = 1; pos <= cur; pos++) {
		if (m_nodes[pos].m_parent != 0) {		//结点parent!=0的结点都是新形成的霍夫曼树结点
			continue;						//已经形成的就不用参加新的霍夫曼树结点再次生成了
		}

		if (minOne == 0) {
			minOne = pos;
		}

		if (m_nodes[pos].m_weight < m_nodes[minOne].m_weight) {
			minOne = pos;
		}
	}

	for (int pos = 1; pos <= cur; pos++) {
		if (m_nodes[pos].m_parent != 0) {
			continue;
		}
		if (minTwo == 0 && m_nodes[minOne].m_weight != m_nodes[pos].m_weight) {
			minTwo = pos;
		}
		else if (m_nodes[pos].m_weight < m_nodes[minTwo].m_weight && pos != minOne) {
			minTwo = pos;
		}
	}
}
template <class CharType, class WeightType>
void HuffmanTree<CharType, WeightType>::createHuffmanTreeHelp(CharType * chars, WeightType * weight, int size) {
#ifdef DEBUG
	std::cout << "FUN:" << __func__ << ",LINE:" << __LINE__ << std::endl;
#endif // DEBUG

	int m_size = size;
	int nodeCount = 2 * size - 1;

	m_nodes = new HuffmanTreeNode<WeightType>[nodeCount + 1];
	assert(m_nodes);
	m_leafChars = new CharType[m_size + 1];
	assert(m_leafChars);
	m_leafCharCodes = new std::string[m_size + 1];
	assert(m_leafCharCodes);

	int pos, minOne, minTwo;
	for (pos = 1; pos <= size; pos++) {
		m_leafChars[pos] = chars[pos - 1];
		m_nodes[pos].m_weight = weight[pos - 1];
	}

	for (pos = size + 1; pos <= nodeCount; pos++) {
		selectHelp(pos - 1, minOne, minTwo);

		m_nodes[pos].m_weight = m_nodes[minOne].m_weight + m_nodes[minTwo].m_weight;
		m_nodes[minOne].m_parent = m_nodes[minTwo].m_parent = pos;
		m_nodes[pos].m_leftChild = minOne;
		m_nodes[pos].m_rightChild = minTwo;
	}

	for (pos = 1; pos <= m_size; pos++) {
		SimpleLinkList<char> charCode;

		for (unsigned int child = pos, parent = m_nodes[child].m_parent;
			parent != 0; child = parent, parent = m_nodes[child].m_parent) {
			
			if (m_nodes[parent].m_leftChild == child) {
				charCode.insertBeforeAll('0');
			}
			else {
				charCode.insertBeforeAll('1');
			}
		}
		for (int i = 1; i <= charCode.getLength(); i++) {
			char tempElem;
			charCode.getElem(i, tempElem);
			charCode[pos] += tempElem;
		}
		std::cout << charCode[pos];
		std::cout << std::endl;
		//m_leafCharCodes[pos] = charCode;
	}
	m_curPos = nodeCount;

}

template <class CharType, class WeightType>
HuffmanTree<CharType, WeightType>::HuffmanTree() {
	this->m_nodes = NULL;
	this->m_leafChars = NULL;
	this->m_leafCharCodes = NULL;
	this->m_curPos = 0;
	this->m_size = 0;
}

template <class CharType, class WeightType>
HuffmanTree<CharType, WeightType>::HuffmanTree(CharType * leafChars, WeightType * weight, int size) {
#ifdef DEBUG
	std::cout << "FUNC:" << __func__ << ",LINE:" << __LINE__ << endl;
#endif // DEBUG

	createHuffmanTree(leafChars, weight, size);
}

template <class CharType, class WeightType>
HuffmanTree<CharType, WeightType>::~HuffmanTree() {
#ifndef DEBUG
	std::cout << "FUNC:" << __func__ << ",LINE:" << __LINE__ << endl;
#endif // !DEBUG

	delete[] m_nodes;
	delete[] m_leafChars;
	delete[] m_leafCharCodes;
}
template <class CharType, class WeightType>
void HuffmanTree<CharType, WeightType>::createHuffmanTree(CharType * leafChars, WeightType * weight, int size) {
#ifndef DEBUG
	std::cout << "FUNC:" << __func__ << ",LINE:" << __LINE__ << endl;
#endif // !DEBUG
	createHuffmanTreeHelp(leafChars, weight, size);
}
template <class CharType, class WeightType>
std::string HuffmanTree<CharType, WeightType>::enCode(CharType ch) {
#ifdef DEBUG
	std::cout << "FUNC:" << __func__ << ",LINE:" << __LINE__ << std::endl;
#endif // DEBUG

	for (int pos = 1; pos <= m_size; pos++) {
		if (ch == m_leafChars[pos]) {
			return m_leafCharCodes[pos];
		}
	}

	std::cout << "无此字符编码" << std::endl;
}
template <class CharType, class WeightType>
std::string HuffmanTree<CharType, WeightType>::deCode(std::string strCode) {
	char charStr[81];						//这个来存储解码后的字符,因为不知道类型,所以用一个字符数组来存储
	int charPos = 0;

	for (unsigned int pos = 0; pos < strCode.size(); pos++) {
		if (strCode[pos] == 0) {
			this->m_curPos = this->m_nodes[m_curPos].leftChild;
		}
		else {
			this->m_curPos = this->m_nodes[m_curPos].rightChild;
		}

		if (this->m_nodes[m_curPos].leftChild == 0) {
			charStr[curPos++] = this->m_leafChars[m_curPos];
			m_curPos = 2 * m_size - 1;
		}
	}

	charStr[curPos] = '\0';
	return &charStr[0];
}
#endif // !HUFFMANTREE_H_INCLUDE

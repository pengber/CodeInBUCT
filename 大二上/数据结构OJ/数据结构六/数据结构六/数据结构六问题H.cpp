/*************************************************************************************
*Author	:Pengber
*Version	:1.0
*Date		:2018/10/16
**************************************************************************************/
/*************************************************************************************
*Problem	:
1.未将已得出的编码存入charCodes中,需了解string类的有关知识√用char数组循环搞定了
2.解码啥的都没有编写
3.deCode返回的是函数内创建对象的指针,我觉得有些不合适
*Tips:		:

*************************************************************************************/
/*************************************************************************************
*History	:
**************************************************************************************/
#ifndef HUFFMANTREE_H_INCLUDE
#define HUFFMANTREE_H_INCLUDE

/*************************************************************************************
*Author	:Pengber
*Version	:1.0
*Date		:2018/10/16
**************************************************************************************/
/*************************************************************************************
*Problem	:
*Tips:		:
1.Q为什么连权重的类型都得定义模板类
A.因为权重有可能是整数也有可能是小数
*************************************************************************************/
/*************************************************************************************
*History	:
**************************************************************************************/
#ifndef HUFFMANTREENODE_H_INCLUDE
#define	HUFFMANTREENODE_H_INCLUDE

template <class WeightType>
struct HuffmanTreeNode {
	WeightType m_weight;
	unsigned int m_parent, m_leftChild, m_rightChild;

	HuffmanTreeNode();
	HuffmanTreeNode(WeightType weigth, int parent = 0, int leftChild = 0, int rightChild = 0);
	HuffmanTreeNode(const HuffmanTreeNode<WeightType> & copy);
	virtual ~HuffmanTreeNode();
};
template <class WeightType>
HuffmanTreeNode<WeightType>::HuffmanTreeNode() {
	this->m_parent = 0;
	this->m_leftChild = 0;
	this->m_rightChild = 0;
}
template <class WeightType>
HuffmanTreeNode<WeightType>::HuffmanTreeNode(WeightType weight, int parent/*= 0*/, int leftChild/*= 0*/, int rightChild/*=0*/) {
	this->m_weight = weight;
	this->m_parent = parent;
	this->m_leftChild = leftChild;
	this->m_rightChild = rightChild;
}
template <class WeightType>
HuffmanTreeNode<WeightType>::HuffmanTreeNode(const HuffmanTreeNode<WeightType> & copy) {
	this->m_weight = copy.weight;
	this->m_parent = copy.parent;
	this->m_leftChild = copy.leftChild;
	this->m_rightChild = copy.rightChild;
}
template <class WeightType>
HuffmanTreeNode<WeightType>::~HuffmanTreeNode() {

}


#endif // !HUFFMANTREENODE_H_INCLUDE

/*******************************************************************************
*Author	: Pengber
*Version	: 1.0
*Day		: 2018.10.12
*Problem	:
1.将判断元素是否存在并返回其位置得函数名称改为getElemPos
*			2.特殊函数未定义
*			3.调试信息和DEBUG信息未定义
*			4.友元函数返回存储交并结果的线性表时调用构造函数,所以利用引用调用传值
5.将insertBehindAll()改名为insertAfterAll();
*Tips		:
1.setElem()和insertElem()函数的上下边界均为(1,length+1);
********************************************************************************/

/********************************************************************************
*history	:
1.将insertBehindAll()函数建立在insert函数上
2.将增改为插
*********************************************************************************/
#include<iostream>
//#define DEBUG								//如果调试将这条注释打开
//#define REMIND							//如果显示提示信息打开这条
template <class ElemType>
class SqList {
	/**************************友元函数声明*********************/
	template <class ElemType2>
	friend void Union(const SqList<ElemType2> & listA, const SqList<ElemType2> & listB, SqList<ElemType2> & listC);
	template <class ElemType2>
	friend void Common(const SqList<ElemType2> & listA, const SqList<ElemType2> & listB, SqList<ElemType2> & listC);
	/*========================友元函数声明结束==================*/


	/**************************公共接口*************************/
public:
	//模板类基本成员函数声明								
	SqList(int capacity = 100);				//带参数的构造函数
	SqList(const SqList & copy);
	virtual ~SqList();
	//模板类特征成员函数声明
	//得
	int getLength() const;

	int getCapacity() const;

	bool getElem(int pos, ElemType & elem) const;			//按位置查找的值

															//判
	bool isEmpty() const;									//判断线性表是否为空

	bool isExitByVal(int & pos, const ElemType & elem) const;//按值查找得位置


															 //插 
	bool insert(int pos, const ElemType & elem);			//按位置插入

	bool insertByVal(const ElemType & elem);				//按值插入

	bool insertBehindAll(const ElemType & elem);			//在表尾插入

															//改
	bool setElem(int pos, const ElemType & elem);			//设pos位置的值为elem

	bool reset(int capacity);								//重置线性表

															//删
	bool deleteElem(int pos, ElemType & elem);				//按位置删除

	bool deleteElemByVal(const ElemType & elem);			//按值删除

	void clean();											//清空线性表
															//模板类重载函数声明
	SqList<ElemType> & operator =(const SqList<ElemType> & copy);
	//模板类特殊函数声明
	//未定义
	/*==================公共接口函数声明完毕=============*/

	/********************私有成员声明********************/
private:

	void init(int capacity = 100);

	int length;

	int capacity;

	ElemType * elems;

	/*=======================私有成员声明完毕================*/
};

/************************友元函数实现****************/

//函数名称:void Union(const SqList<ElemType> & listA, const SqList<ElemType> & listB, SqList<ElemType> & listC);
//初始条件:listA与listB均存在,listC已创建
//操作结果:将listA与listB的并集结果由listC存储
//子函数:getElem(),getLength(),insetBehindAll();
template <class ElemType2>
void Union(const SqList<ElemType2> & listA, const SqList<ElemType2> & listB, SqList<ElemType2> & listC) {
	ElemType2 temp;
	int tempPos;

	for (int i = 1; i <= listA.getLength(); i++) {
		listA.getElem(i, temp);
		listC.insertBehindAll(temp);
	}
	for (int i = 1; i <= listB.getLength(); i++) {
		listB.getElem(i, temp);
		if (listC.isExitByVal(tempPos, temp));
		else {
			listC.insertBehindAll(temp);
		}
	}
}
//函数名称:void Common(const SqList<ElemType> & listA, const SqList<ElemType> & listB, SqList<ElemType2> & listC);
//初始条件:listA与listB均存在,listC已创建
//操作结果:将listA与listB的交集结果由listC存储
//其子函数:getElem(),getLength(),insetBehindAll()
template <class ElemType2>
void Common(const SqList<ElemType2> & listA, const SqList<ElemType2> & listB, SqList<ElemType2> & listC) {
	ElemType2 temp;
	int tempPos;

	for (int i = 1; i <= listA.getLength(); i++) {
		listA.getElem(i, temp);
		if (listB.isExitByVal(tempPos, temp)) {
			listC.insertBehindAll(temp);
		}
	}
}

/*==================友元函数实现结束==============*/

/*******************基本成员函数实现***************/

//函数名称:SqList<int capacity = 100)
//初始条件:无重名类对象
//操作结果:构造一个容量为capacity的线性表
template <class ElemType>
SqList<ElemType>::SqList(int capacity) {
	this->length = 0;
	this->capacity = capacity;
	this->elems = new ElemType[capacity];
}

//函数名称:SqList<const SqList<ElemType> & copy)
//初始条件:线性表copy已经创建
//操作结果:建立一个与copy内容相同的新线性表
//其子函数:init(),getElem(),inserBehindAll();
template <class ElemType>
SqList<ElemType>::SqList(const SqList<ElemType> & copy) {
	ElemType temp;
	this->init(copy.capacity);
	for (int i = 1; i <= copy.getLength(); i++) {
		copy.getElem(i, temp);
		this->insertBehindAll(temp);
	}
}

//函数名称:vitual ~SqList();
//初始条件:已创建类对象
//操作结果:释放对象所用空间
//注意事项:数据成员length和capacity不用改变,当相应对象效实时会自动回收这部分空间
template <class ElemType>
SqList<ElemType>::~SqList() {
	if (elems != NULL) {
		delete[] elems;
	}
}
/*==================基本成员函数实现结束================*/

/*******************特称成员函数实现********************/
/*
int getLength() const;
int getCapacity() const;
bool getElem(int pos, ElemType & elem) const ;				//按位置查找的值
bool isEmpty() const;
bool isExitByVal(int & pos, const ElemType & elem) const;	//按值查找得位置
bool insert(int pos, const ElemType & elem);
bool insertByVal(const ElemType & elem);
bool insertBehindAll(const ElemType & elem);
bool setElem(int pos, const ElemType & elem);
bool reset(int capacity);
bool deleteElem(int pos, ElemType & elem);
bool deleteElemByVal(const ElemType & elem);				//按值删除
void clean();
*/

//函数名称:int getLength() const
//初始条件:线性表对象已经创建
//操作结果:返回线性表对象的长度
//无子函数
template <class ElemType>
int SqList<ElemType>::getLength() const {
	return this->length;
}
//函数名称:int getCapacity() const
//初始条件:线性表对象已经创建
//操作结果:返回线性表对象的容量
//无子函数
template <class ElemType>
int SqList<ElemType>::getCapacity() const {
	return this->capacity;
}
//函数名称:bool getElem(int pos, ElemType & elem)
//初始条件:线性表对象已经创建
//操作结果:如果线性表为空或pos<1 || pos > length返回0,成功返回1;
//无子函数
template <class ElemType>
bool SqList<ElemType>::getElem(int pos, ElemType & elem) const {
	if (length == 0) {
		return false;
	}
	if (pos < 1 && pos > length) {
		return false;
	}
	else {
		elem = this->elems[pos - 1];
		return true;
	}
}
//函数名称:bool isEmpty() const
//初始条件:线性表对象已经创建
//操作结果:如果线性表为空返回1,否则返回0
//无子函数
template <class ElemType>
bool SqList<ElemType>::isEmpty() const {
	return length == 0;
}
//函数名称:bool isExitByVal(int & pos, const ElemType & elem) const
//初始条件:线性表对象已经创建
//操作结果:线性表为空或者无此元素则返回0,pos为0,有此元素返回1,并将其位置由pos得出
//无子函数
template <class ElemType>
bool SqList<ElemType>::isExitByVal(int & pos, const ElemType & elem) const {
	if (length == 0) {
		pos = 0;
		return false;
	}

	for (int curPos = 1; curPos <= length; curPos++) {
		if (elems[curPos - 1] == elem) {
			pos = curPos;
			return true;
		}
	}
	pos = 0;
	return false;
}
//函数名称:bool insert(int pos, const ElemType & elem)
//初始条件:线性表对象已经创建
//操作结果:表满或者pos < 1 || pos > length + 1返回假,其余情况插入返回真
//其子函数:getElem(),setElem()
template <class ElemType>
bool SqList<ElemType>::insert(int pos, const ElemType & elem) {
	ElemType temp;

	if (length == capacity) {
		return false;
	}
	else {
		if (pos < 1 || pos > length + 1) {
			return false;
		}
		else {
			for (int curPos = length; curPos >= pos; curPos--) {
				this->getElem(curPos, temp);
				this->setElem(curPos + 1, temp);
			}
			this->setElem(pos, elem);
			this->length++;
			return true;
		}
	}
}
//函数名称:bool insertByVal(const ElemType & elem)
//初始条件:线性表已创建
//操作结果:把elem元素按值得大小插入到第一个大于它值的前面
//其子函数:getElem(),insert()
template <class ElemType>
bool SqList<ElemType>::insertByVal(const ElemType & elem) {
	int temPos;
	ElemType temp;

	temPos = 1;
	this->getElem(temPos, temp);
	while (temp < elem && temPos <= length) {
		this->getElem(++temPos, temp);
	}
	temPos;
	this->insert(temPos, elem);
	return 1;
}
//函数名称:bool insertBehindAll(const ElemType & elem)
//初始条件:线性表对象已经创建
//操作结果:在表尾插入elem元素
//其子函数:insert(); 
template <class ElemType>
bool SqList<ElemType>::insertBehindAll(const ElemType & elem) {
	if (length == capacity) {
		return false;
	}
	else {
		this->insert(length + 1, elem);
		/*
		elems[length] = elem;
		this->length++;
		*/
		return true;
	}
}
//函数名称:bool setElem(int pos, const ElemType & elem)
//初始条件:线性表对象已经创建
//操作结果:pos < 1 || pos > length返回假,否则设置pos位置上的元素为elem返回真 
//无子函数
template <class ElemType>
bool SqList<ElemType>::setElem(int pos, const ElemType & elem) {
	//将下面代码注释掉的原因时因为当线性表长度为0时,可以设置1位置的元素为elem
	/*
	if (length == 0) {
	return false;
	}
	*/
	if (pos < 1 || pos > length + 1) {
		return false;
	}
	else {
		elems[pos - 1] = elem;
		return true;
	}
}
//函数名称:bool reset(int capacity)
//初始条件:线性表已创建
//操作结果:将此线性表重置为容量为capacity的线性表
//其子函数:私有成员函数init()
template <class ElemType>
bool SqList<ElemType>::reset(int capacity) {
	this->init(capacity);
	return true;
}
//函数名称:bool deleteElem(int pos, ElemType & elem)
//初始条件:线性表已创建并且位置合法
//操作结果:删除该位置元素,其值由引用调用参数传递出来
//其子函数:getElem(),setElem()
template <class ElemType>
bool SqList<ElemType>::deleteElem(int pos, ElemType & elem) {
	if (length == 0) {
		return false;
	}
	else {
		if (pos < 1 || pos > length) {
			return false;
		}
		else {
			ElemType temp;

			this->getElem(pos, elem);
			for (int curPos = pos + 1; curPos <= length; curPos++) {
				this->getElem(curPos, temp);
				this->setElem(curPos - 1, temp);
			}
			this->length--;
			return true;
		}
	}
}
//函数名称:bool deleteElemByVal(const ElemType & elem)
//初始条件:线性表已创建
//操作结果:如果有这个值则删除,没有则返回0
//其子函数:deleteElem()
template <class ElemType>
bool SqList<ElemType>::deleteElemByVal(const ElemType & elem) {
	int tempPos;
	ElemType temp;

	while (this->isExitByVal(tempPos, elem)) {
		this->deleteElem(tempPos, temp);
	}
	return 1;
}
//函数名称:void clean()
//初始条件:线性表已创建
//操作结果:将线性表元素内容清空
//无子函数
template <class ElemType>
void SqList<ElemType>::clean() {
	length = 0;
}
/*======================特征成员函数实现完毕==============*/

/***********************私有成员函数实现****************/
//函数名称:void init(int capacity)
//初始条件:线性表已创建
//操作结果:将线性表内容清空后重新申请一个容量为capacity大小的线性表
//无子函数
template <class ElemType>
void SqList<ElemType>::init(int capacity) {
	if (elems != NULL) {
		delete[] elems;
	}
	elems = new ElemType[capacity];
	this->capacity = capacity;
	this->length = 0;
}
/*=====================私有成员函数实现结束===================*/

/*********************重载函数实现*****************************/
//函数名称:SqList<ElemType> &operator=(const SqList<ElemType> & copy)
//初始条件:=号的初始条件
//操作结果:使左边的线性表等于右边的线性表
//其子函数:getCapacity(),getLength(),getElem(),setElem()
template <class ElemType>
SqList<ElemType> & SqList<ElemType>::operator=(const SqList<ElemType> & copy) {
	ElemType temp;

	if (copy.isEmpty() == true) {
		this->init(copy.getCapacity());
		return *this;
	}

	this->init(copy.getCapacity());
	this->length = copy.getLength();

	for (int i = 1; i <= length; i++) {
		copy.getElem(i, temp);
		this->setElem(i, temp);
	}
	return *this;
}
/*==========================重载运算符函数实现完毕===============*/


#include <assert.h>
#include <iostream>
#include <string>
//#define DEBUG
//#define SHOW
using namespace std;
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
	//std::string deCode(std::string strCode);

};
template <class CharType, class WeightType>
void HuffmanTree<CharType, WeightType>::selectHelp(int cur, int & minOne, int & minTwo) {
	minOne = minTwo = 0;

	for (int pos = 1; pos <= cur; pos++) {
		if (m_nodes[pos].m_parent != 0) {		//结点parent!=0的结点都是新形成的霍夫曼树结点
			continue;						//已经形成的就不用参加新的霍夫曼树结点再次生成了
		}

		if (minOne == 0) {
			minOne = pos;
		}
		else if (m_nodes[pos].m_weight < m_nodes[minOne].m_weight) {
			minOne = pos;
		}
	}
	m_nodes[minOne].m_parent = 1;
	for (int pos = 1; pos <= cur; pos++) {
		if (m_nodes[pos].m_parent != 0) {		//结点parent!=0的结点都是新形成的霍夫曼树结点
			continue;						//已经形成的就不用参加新的霍夫曼树结点再次生成了
		}

		if (minTwo == 0) {
			minTwo = pos;
		}
		else if (m_nodes[pos].m_weight < m_nodes[minTwo].m_weight && minOne != minTwo) {
			minTwo = pos;
		}
	}


	if (minOne > minTwo) {
		int temp;
		temp = minOne;
		minOne = minTwo;
		minTwo = temp;
	}
}
template <class CharType, class WeightType>
void HuffmanTree<CharType, WeightType>::createHuffmanTreeHelp(CharType * chars, WeightType * weight, int size) {


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
		SqList<char> charCode;

		for (unsigned int child = pos, parent = m_nodes[child].m_parent;
			parent != 0; child = parent, parent = m_nodes[child].m_parent) {

			if (m_nodes[parent].m_leftChild == child) {
				charCode.insert(1, '0');
			}
			else {
				charCode.insert(1, '1');
			}
		}
		for (int i = 1; i <= charCode.getLength(); i++) {
			char tempElem;
			charCode.getElem(i, tempElem);
			m_leafCharCodes[pos] += tempElem;
		}
		charCode.clean();
		//cout << m_leafCharCodes[pos];
		//cout << endl;
	}
	for (int i = 1; i <= m_size; i++) {
		cout << m_leafCharCodes[i] << endl;
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
	createHuffmanTree(leafChars, weight, size);
}

template <class CharType, class WeightType>
HuffmanTree<CharType, WeightType>::~HuffmanTree() {
	delete[] m_nodes;
	delete[] m_leafChars;
	delete[] m_leafCharCodes;
}
template <class CharType, class WeightType>
void HuffmanTree<CharType, WeightType>::createHuffmanTree(CharType * leafChars, WeightType * weight, int size) {
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
/*template <class CharType, class WeightType>
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
}*/
using namespace std;
#endif // !HUFFMANTREE_H_INCLUDE

using namespace std;
int main() {
	char ch[100] = { 'a' };
	int weight[100];
	int num;
	cin >> num;

	for (int i = 0; i < num; i++) {
		cin >> weight[i];
	}
	HuffmanTree<char, int> huffmanTree;
	huffmanTree.createHuffmanTree(ch, weight, num);
	return 0;
}

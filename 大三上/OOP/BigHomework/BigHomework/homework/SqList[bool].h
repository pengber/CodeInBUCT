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

#pragma once
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

	bool getElem(int pos, ElemType & elem) const ;			//按位置查找的值

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
		if (listB.isExitByVal(tempPos,temp)) {
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


/************************************************************
*Author		:Pengber
*Version	:1.0
*Date		:2018/10/17
**************************************************************/
/***********************************************************
*Problem	:
			1.乘法未定义
			
*Tips:		:
			1.减法并不是很简单,仔细琢磨琢磨
			
*************************************************************/
/************************************************************
*History	:

*************************************************************/
#ifndef POLYNOMIAL_H_INCLUDE
#define POLYNOMIAL_H_INCLUDE
#include <iostream>
#include "SimpleLinkList.h"
#include "PolyItem.h"

//#define DEBUG
//#define REMIND

class Polynomial {
	/***************************公共接口**********************/
public:
//基本成员函数
	Polynomial();

	Polynomial(const SimpleLinkList<PolyItem> & copyList);

	Polynomial(const Polynomial & copyPolynomial);

	virtual ~Polynomial();
//特征成员函数
	int getLength() const;

	bool isZero() const;

	void insert(const PolyItem & item);

	bool setZero();

	void display();

//重载
	Polynomial operator+(const Polynomial & polynomialB) const ;

	Polynomial operator-(const Polynomial & polynomialB) const;

	//Polynomial operator*(const Polynomial & polynomialB) const;

	Polynomial & operator=(const Polynomial & polynomialB);

	/*========================公共接口结束======================*/

	/***************************保护接口**********************/
protected:
	SimpleLinkList<PolyItem> polyList;

	/*************************保护接口结束**********************/ 
};
/****************************基本成员函数实现************************/
Polynomial::Polynomial()
	: polyList() {

}

Polynomial::Polynomial(const SimpleLinkList<PolyItem> & copyList)
	: polyList(copyList) {

}

Polynomial::Polynomial(const Polynomial & copyPolynomial)
	: polyList(copyPolynomial.polyList) {

}
Polynomial::~Polynomial() {

}
/**************************基本成员函数实现完毕************************/

/****************************特征成员函数实现************************/
//函数名称:int getLength()
//函数功能:得到一元多项式的长度,即项数
//无子函数
inline int Polynomial::getLength() const {
	return polyList.getLength();
}
//函数名称:bool isZero()
//函数功能:判断一元多项式是否为0,是返回真,不是返回假
//无子函数:
bool Polynomial::isZero() const {
#ifdef DEBUG
	std::cout << "isZero...." << std::endl;
#endif
	int length = this->getLength();
	PolyItem tempItem;

	if (length == 0) {
#ifdef REMIND
		std::cout << "此多项式为空" << std::endl;
#endif
		return false;
	}
	for (int i = 1; i <= length; i++) {
		polyList.getElem(i, tempItem);
		if (tempItem.mCoef != 0)
			return false;
	}

	return true;
}
//函数名称:void insert()
//函数功能:在多项式中插入一项
//无子函数:
void Polynomial::insert(const PolyItem & item) {
#ifdef DEBUG
	std::cout << "insert..." << std::endl;
#endif
	PolyItem tempItem;
	int tempPos = 1;
	bool flag = polyList.getElem(tempPos, tempItem);			
	//必须设置标志位,因为如果不设置标志位,要插入的项的系数最小的话,tempItem的值
	//不会变,尽管线性表走到末尾,while循环还是会一直为真,陷入死循环

	while (flag && item.mExpn < tempItem.mExpn) {
		flag = polyList.getElem(++tempPos, tempItem);
	}

	polyList.insert(tempPos, item);
}
//函数名称:bool setZero()
//函数功能:将多项式置于0,如果多项式为空返回假,否则删除所有项后将第一项系数
//			置于0,指数置于-1返回真;
//其子函数:
bool Polynomial::setZero() {
#ifdef DEBUG
	std::cout << "setZero..." << std::endl;
#endif
	int length = polyList.getLength();

	if (length == 0) {
#ifdef REMIND
		std::cout << "多项式为空,无法置零" << std::endl;
#endif
		return false;
	}
	else {
		PolyItem tempItem(0, 0);
		polyList.clean();
		polyList.insertAfterAll(tempItem);
		return true;
	}
}
//函数名称:void display()
//函数功能:输出一元多项式系数和指数,系数为0则只输出0,不输出指数
void Polynomial::display() {
#ifdef DEBUG
	std::cout << "display..." << std::endl;
#endif
	PolyItem tempItem;
	if (this->isZero()) {
		std::cout << 0 << std::endl;
	}
	else {
		for (int i = 1; i <= this->getLength(); i++) {
			polyList.getElem(i, tempItem);
			if (i == 1) {
				if (tempItem.mCoef == 0) {
				}
				else {
					std::cout << tempItem.mCoef << " " << tempItem.mExpn;
				}
			}
			else {
				if (tempItem.mCoef == 0) {
				}
				else {
					std::cout << " " << tempItem.mCoef << " " << tempItem.mExpn;
				}
			}
		}
		std::cout << std::endl;
	}
}
/*************************特征成员函数实现完毕*************************/
/****************************重载函数实现***********************/
//函数名称:Polynomial operator+(const Polynomial & polynomialB)
//函数功能:减法的重载
Polynomial Polynomial::operator+(const Polynomial & polynomialB) const {
	/*我这个代码还是比较繁琐,更简洁的是定义一个链表A,B,C,然后将A,B相加的值存储到
	  C中,然后将C的值赋给多项式里面的polyList即可*/
	Polynomial polynomialC;
	PolyItem itemA, itemB, itemC;
	int aPos = 1, bPos = 1;
	bool aFlag, bFlag;						//标志从A,B两个多项式是否能取出item

	aFlag = this->polyList.getElem(aPos, itemA);
	bFlag = polynomialB.polyList.getElem(bPos, itemB);

	while (aFlag && bFlag) {
		if (itemA.mExpn < itemB.mExpn) {
			polynomialC.polyList.insertAfterAll(itemB);
			bFlag = polynomialB.polyList.getElem(++bPos, itemB);
		}
		else if (itemA.mExpn > itemB.mExpn) {
			polynomialC.polyList.insertAfterAll(itemA);
			aFlag = this->polyList.getElem(++aPos, itemA);
		}
		else {
			itemC.mCoef = itemA.mCoef + itemB.mCoef;
			itemC.mExpn = itemA.mExpn;
			polynomialC.polyList.insertAfterAll(itemC);
			bFlag = polynomialB.polyList.getElem(++bPos, itemB);
			aFlag = this->polyList.getElem(++aPos, itemA);
		}
	}
	while (aFlag) {
		polynomialC.polyList.insertAfterAll(itemA);
		aFlag = this->polyList.getElem(++aPos, itemA);
	}
	while (bFlag) {
		polynomialC.polyList.insertAfterAll(itemB);
		bFlag = polynomialB.polyList.getElem(++bPos, itemB);
	}

	return polynomialC;
}
//函数名称:Polynomial operator-(const Polynomial & polynomialB)
//函数功能:减法的重载
Polynomial Polynomial::operator-(const Polynomial & polynomialB) const {
	PolyItem itemB;
	int bPos = 1;
	bool bFlag;
	SimpleLinkList<PolyItem> polyListB = polynomialB.polyList;

	bFlag = polyListB.getElem(bPos, itemB);

	while (bFlag) {
		itemB.mCoef = - itemB.mCoef;
		polyListB.setElem(bPos, itemB);
		bFlag = polyListB.getElem(++bPos, itemB);
	}
	Polynomial polynomialA(polyList), nagativePolynomialB(polyListB),polynomialC;
	
	polynomialC = polynomialA + nagativePolynomialB;

	return polynomialC;
}
//函数名称:Polynomial operator*(const Polynomial & polynomialB)
//函数功能:乘法的重载
//Polynomial Polynomial::operator*(const Polynomial & polynomialB) const {}

Polynomial & Polynomial::operator=(const Polynomial & polynomialB) {
	this->polyList = polynomialB.polyList;
	return *this;
}
/*========================重载函数实现完毕=======================*/
#endif
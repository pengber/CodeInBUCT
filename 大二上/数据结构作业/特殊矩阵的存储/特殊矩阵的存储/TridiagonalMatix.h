/************************************************************************************
*Author		:Pengber
*Version	:1.0
*Date		:2018/11/4
************************************************************************************/
/************************************************************************************
*Problem	:
*Tips:		:
************************************************************************************/
/************************************************************************************
*History	:

************************************************************************************/
#ifndef TRIDIAGONAL_MATRIX_H_INCLUDE
#define TRIDIAGONAL_MATRIX_H_INCLUDE
#include <iostream>

template <class ElemType>
class TridiagonalMatrix {
/***********************************公共接口声明*******************************/
public:
//基本成员函数
	TridiagonalMatrix(int order);

	TridiagonalMatrix(TridiagonalMatrix<ElemType> & copy);

	virtual ~TridiagonalMatrix();
//特征函数
	//得
	int getOrder() const;

	bool getElem(int row, int col, ElemType & elemVal) const;
	
	//判无
	//增无

	//改
	bool setElem(int row, int col, ElemType & elemVal);

	//删无
//特殊函数
	void display() const;
//重载函数
	ElemType & operator()(int row, int col);	
/*=================================公共接口声明完毕============================*/
/***********************************保护接口声明*******************************/
protected:
	ElemType * elems;
	
	int order;								//矩阵的阶数
/*=================================保护接口声明完毕============================*/
};

template <class ElemType>
TridiagonalMatrix<ElemType>::TridiagonalMatrix(int order) {
	elems = new ElemType[3 * order - 2];
	this->order = order;
}
template <class ElemType>
TridiagonalMatrix<ElemType>::TridiagonalMatrix(TridiagonalMatrix<ElemType> & copy) {
	ElemType tempElemVal;

	this->order = copy.getOrder();
	elems = new ElemType[3 * order - 2];
	for (int row = 1; row <= order; row++) {
		for (int col = 1; col <= order; col++) {
			copy.getElem(row, col, tempElemVal);
			this->setElem(row, col, tempElemVal);
		}
	}
}
template <class ElemType>
TridiagonalMatrix<ElemType>::~TridiagonalMatrix() {
	delete[] elems;
}

template <class ElemType>
int TridiagonalMatrix<ElemType>::getOrder() const {
	return order;
}

template <class ElemType>
bool TridiagonalMatrix<ElemType>::getElem(int row, int col, ElemType & elemVal) const {
	if (row < 1 || row > order || col < 1 || col > order) {
#ifdef REMIND
		std::cout << "Overflow!" << std::endl;
#endif
		return false;
	}
	else {
		if (row - col == 1) elemVal = elems[2 * order + row - 2];		//order + order - 1 + i -1
		else if (row == col) return elemVal = elems[order - 1 + row];			//主对角线
		else if (row - col == -1) return elemVal = elems[row];				//高对角线
		else return elemVal = elems[0];
	}
}

template <class ElemType>
bool TridiagonalMatrix<ElemType>::setElem(int row, int col, ElemType & elemVal) {
	if (row < 1 || row > order || col < 1 || col > order) {
#ifdef REMIND
		std::cout << "Overflow!" << std::endl;
#endif
		return false;
	}
	else {
		if (row - col == 1) {
			elems[2 * order + row - 2] = elemVal;
		}
		else if (row == col) {
			elems[order + row - 1] = elemVal;
		}
		else if (row - col == -1) {
			elems[row] = elemVal;
		}
		else
			elems[0] = elemVal;
	}
}
template <class ElemType>
void TridiagonalMatrix<ElemType>::display() const {
	for (int i = 0; i <= 3 * order - 2; i++) {
		std::cout << elems[i] << std::endl;
	}
}
template <class ElemType>
ElemType & TridiagonalMatrix<ElemType>::operator()(int row, int col) {
	if (row < 1 || row > order || col < 1 || col > order) {
#ifdef REMIND
		std::cout << "Overflow!" << std::endl;
#endif
		return false;
	}
	else {
		if (row - col == 1) return elems[2 * order + row - 2];		//order + order - 1 + i -1
		else if (row == col) return elems[order - 1 + row];			//主对角线
		else if (row - col == -1) return elems[row];				//高对角线
		else return elems[0];
	}
}



#endif
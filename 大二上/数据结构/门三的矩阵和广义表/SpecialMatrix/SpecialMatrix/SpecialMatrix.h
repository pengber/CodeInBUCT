#ifndef SPECIALMATRIX_H_INCLUDE
#define SPECIALMATRIX_H_INCLUDE

template <class ElemType>
class TriMatrix {
private:
	ElemType * elems;
	int rank;

public:
	TriMatrix();
	TriMatrix(int n);
	~TriMatrix();
	bool getElem(int i, int j, ElemType & elem);
	void display();
};
template<class ElemType>
inline TriMatrix<ElemType>::TriMatrix()
{
	elems = NULL;
}
template<class ElemType>
inline TriMatrix<ElemType>::TriMatrix(int n)
{
	rank = n;
	elems = new int[3 * rank - 1];
	int k;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (i == j + 1) std::cin >> elems[n - 1 + n + i - 1];
			else if (i == j) std::cin >> elems[n - 1 + i];
			else if (i == j - 1) std::cin >> elems[i];
			else std::cin >> elems[0];
		}
	}
}
template<class ElemType>
inline TriMatrix<ElemType>::~TriMatrix()
{
	delete[] matrix;
}
template<class ElemType>
bool TriMatrix<ElemType>::getElem(int i, int j, ElemType & elem)
{
	int n = rank;
	if (i < 1 || i > rank || j < 1 || j > rank) return false;
	if (i == j + 1) elem = elems[n - 1 + n + i - 1];
	else if (i == j) elem = elems[n - 1 + i];
	else if (i == j - 1) elem = elems[i];
	else elem = elems[0];
	return true;
}
template<class ElemType>
void TriMatrix<ElemType>::display()
{
	ElemType elem;
	for (int i = 1; i <= rank; i++) {
		for (int j = 1; j <= rank; j++) {
			this->getElem(i, j, elem);
			std::cout << elem << " ";
		}
		std::cout << endl;
	}
}


// 下三角矩阵类
template<class ElemType>
class LowerTriangularMatrix
{
protected:
	//  下三角矩阵的数据成员:
	ElemType * elems;				// 存储矩阵元素
	int n;							// 下三角矩阵阶数

public:
	// 抽象数据类型方法声明及重载编译系统默认方法声明:
	LowerTriangularMatrix(int sz);	// 构造一个sz行sz列的下三角矩阵
	~LowerTriangularMatrix();		// 析构函数
	int GetSize() const;			//返回下三角矩阵阶数
	ElemType &operator()(int i, int j);	// 重载函数运算符
	LowerTriangularMatrix(const LowerTriangularMatrix<ElemType> &copy);		// 复制构造函数
	
	// 赋值语句重载
};

// 下三角矩阵类的实现部分
template <class ElemType>
LowerTriangularMatrix<ElemType>::LowerTriangularMatrix(int sz)
// 操作结果：构造一个sz行sz列的下三角矩阵
{
	if (sz < 1)
		throw Error("行数或列数无效!");	// 抛出异常
	n = sz;								// sz为矩阵阶数
	elems = new ElemType[n * (n + 1) / 2 + 1];	// 分配存储空间
}

template <class ElemType>
LowerTriangularMatrix<ElemType>::~LowerTriangularMatrix()
// 操作结果：释放下三角矩阵所占用空间
{
	if (elems != NULL) delete[]elems;
}

template <class ElemType>
int LowerTriangularMatrix<ElemType>::GetSize() const
// 操作结果：返回下三角矩阵阶数
{
	return n;
}

template <class ElemType>
ElemType &LowerTriangularMatrix<ElemType>::operator()(int i, int j)
// 操作结果：重载函数运算符
{
	if (i < 1 || i > n || j < 1 || j > n)
		throw Error("下标出界!");					// 抛出异常
	if (i >= j)	return elems[i * (i - 1) / 2 + j];	// 元素在下三角中
	else return elems[0];							// 元素在其它位置
}

template <class ElemType>
LowerTriangularMatrix<ElemType>::LowerTriangularMatrix(const LowerTriangularMatrix<ElemType> &copy)
// 操作结果：由下三角矩阵copy构造新下三对角矩阵——复制构造函数
{
	n = copy.n;							// 复制下三对角矩阵阶数
	elems = new ElemType[n * (n + 1) / 2 + 1];	// 为数据元素分配存储空间
	for (int i = 0; i < n * (n + 1) / 2 + 1; i++)
	{	// 复制数据元素值
		elems[i] = copy.elems[i];
	}
}


// 对称矩阵类
template<class ElemType>
class SymmtryMatrix
{
protected:
	//  对称矩阵的数据成员:
	ElemType * elems;			// 存储矩阵元素
	int n;						// 对称矩阵阶数

public:
	// 抽象数据类型方法声明及重载编译系统默认方法声明:
	SymmtryMatrix(int sz);		// 构造一个sz行sz列的对称矩阵
	~SymmtryMatrix();			// 析构函数
	int GetSize() const;		// 返回对称矩阵阶数
	ElemType &operator()(int i, int j);	// 重载函数运算符
	// 赋值语句重载
};

// 对称矩阵类的实现部分
template <class ElemType>
SymmtryMatrix<ElemType>::SymmtryMatrix(int sz)
// 操作结果：构造一个sz行sz列的对称矩阵
{
	if (sz < 1)
		throw Error("行数或列数无效!");	// 抛出异常
	n = sz;								// sz为矩阵阶数
	elems = new ElemType[n * (n + 1) / 2];	// 分配存储空间
}

template <class ElemType>
SymmtryMatrix<ElemType>::~SymmtryMatrix()
// 操作结果：释放对称矩阵所占用空间
{
	if (elems != NULL) delete[]elems;
}

template <class ElemType>
int SymmtryMatrix<ElemType>::GetSize() const
// 操作结果：返回对称矩阵阶数
{
	return n;
}

template <class ElemType>
ElemType &SymmtryMatrix<ElemType>::operator()(int i, int j)
// 操作结果：重载函数运算符
{
	if (i < 1 || i > n || j < 1 || j > n)
		throw Error("下标出界!");						// 抛出异常
	if (i >= j)	return elems[i * (i - 1) / 2 + j - 1];	// 元素在下三角中
	else return elems[j * (j - 1) / 2 + i - 1];			// 元素在上三角中
}
#endif // !SPECIALMATRIX_H_INCLUDE

#include "Triple.h"

template <class ElemType>
class TriSparseMatrix {
protected:
	Triple<ElemType> * m_elems;
	int m_rows, m_cols, m_num, m_maxSize;

public:
	TriSparseMatrix();
	TriSparseMatrix(int rows, int cols, int maxSize);
	//TriSparseMatrix(const TriSparseMatrix<ElemType> & copy);
	~TriSparseMatrix();
	bool setElem(int row, int col, const ElemType & value);
	ElemType getElem(int row, int col);
	int getRows();
	int getCols();
	void display();
	void display(int row, int col);
	void transpose(TriSparseMatrix<ElemType> & matrix);
	TriSparseMatrix<ElemType> mutiple(TriSparseMatrix<ElemType> & matrix);

};
template <class ElemType>
TriSparseMatrix<ElemType>::TriSparseMatrix() {
	m_elems = NULL;
	m_rows = 0;
	m_cols = 0;
	m_num = 0;
	m_maxSize = 0;
}

/*template<class ElemType>
TriSparseMatrix<ElemType>::TriSparseMatrix(const TriSparseMatrix<ElemType>& copy)
{
	m_rows = copy.getRows();
	m_cols = copy.getCols();
	m_maxSize = m_rows * m_cols;
	m_num = 0;

}
*/
template <class ElemType>
TriSparseMatrix<ElemType>::~TriSparseMatrix() {
	delete[] m_elems;
}
template <class ElemType>
TriSparseMatrix<ElemType>::TriSparseMatrix(int rows, int cols, int maxSize) {
	m_elems = new Triple<ElemType>[maxSize];
	m_rows = rows;
	m_cols = cols;
	m_num = 0;
	m_maxSize = maxSize;
}
template<class ElemType>
bool TriSparseMatrix<ElemType>::setElem(int row, int col, const ElemType & value)
{
	if (row > m_rows || col > m_cols || row < 1 || col < 1) {//row已1为下标
		return false;
	}

	int i, j;

	for (j = m_num - 1; (j >= 0 &&(row < m_elems[j].m_row || row == m_elems[j].m_row
		&& col < m_elems[j].m_col)); j--);//j >０　＆＆

	if (j >= 0 && m_elems[j].m_col == col && m_elems[j].m_row == row) {
		if (m_elems[j].m_value == 0) {
			for (i = j; i < m_num - 1; i++) {
				m_elems[i] = m_elems[i + 1];
			}
			m_num--;
		}
		else {
			m_elems[j].m_value = value;
		}
		return true;
	}
	else if (value != 0) {

		if (m_num < m_maxSize) {
			for (i = m_num - 1; i > j; i--) {
				m_elems[i + 1] = m_elems[i];
			}
			m_elems[j + 1].m_row = row;
			m_elems[j + 1].m_col = col;
			m_elems[j + 1].m_value = value;
			m_num++;
			return true;
		}
		else {
			std::cout << "Overflow!" << endl;
			return false;
		}
	}
	return false;
}
template <class ElemType>
ElemType TriSparseMatrix<ElemType>::getElem(int row, int col) {
	for (int i = 0; i < m_num; i++) {
		if (m_elems[i].m_row == row && m_elems[i].m_col == col) {
			return m_elems[i].m_value;
		}
	}
	return 0;
}
template <class ElemType>
int TriSparseMatrix<ElemType>::getRows() {
	return this->m_rows;
}
template <class ElemType>
int TriSparseMatrix<ElemType>::getCols() {
	return this->m_cols;
}
template<class ElemType>
inline void TriSparseMatrix<ElemType>::display()
{
	for (int i = 0; i < m_num; i++) {//i以0为下标标开始存储
		std::cout << m_elems[i].m_row << " " << m_elems[i].m_col << " " << m_elems[i].m_value << endl;
	}
}
template<class ElemType>
inline void TriSparseMatrix<ElemType>::display(int row, int col)
{
	for (int i = 0; i < m_num; i++) {
		if (m_elems[i].m_row == row && m_elems[i].m_col == col) {
			std::cout << m_elems[i].m_value << " ";
			return;
		}
	}
	std::cout << 0 << " ";
}
template<class ElemType>
inline void TriSparseMatrix<ElemType>::transpose(TriSparseMatrix<ElemType>& matrix)
{
	int cNum[m_cols+1] = { 0 };
	int cPos[m_cols+1];
	cPos[1] = 1;
	for (int i = 0; i < m_num; i++) {
		cNum[m_elems[i].m_col]++;
	}

	for (int i = 2; i <= m_cols; i++) {
		cPos[i] = cPos[i - 1] + cNum[i - 1];
	}

	matrix.m_cols = this->m_rows;
	matrix.m_rows = this->m_cols;
	matrix.m_num = this->m_num;
	matrix.m_maxSize = this->m_maxSize;
	delete[] matrix.m_elems;
	matrix.m_elems = new Triple[m_maxSize];

	for (int i = 0; i < m_num; i++) {
		int q = cPos[this->m_elems[i].m_col];//int q = cPos[i];
		matrix.m_elems[q].m_row = this->m_elems[i].m_col;
		matrix.m_elems[q].m_col = this->m_elems[i].m_row;
		matrix.m_elems[q].m_value = this->m_elems[i].m_value;
		++cPos[this->m_elems[i].m_col];
	}

	delete[] cNum;
	delete[] cPos;
}
template<class ElemType>
 TriSparseMatrix<ElemType> TriSparseMatrix<ElemType>::mutiple(TriSparseMatrix<ElemType> & matrix)
{
	 TriSparseMatrix<ElemType> matrixResult(m_rows, matrix.getCols(), m_rows *  matrix.getCols());
	 int i, j, k;
	
	 for (i = 1; i <= m_rows; i++) {
		 for (k = 1; k <= matrix.getCols(); k++) {
			 ElemType temp = 0;
			 for (j = 1; j <= this->m_cols; j++) {
				 temp += this->getElem(i, j) * matrix.getElem(j, k);
			 }
			 matrixResult.setElem(i, k, temp);
		 }
	 }

	 for (i = 1; i <= matrixResult.getRows(); i++) {
		 for (j = 1; j <= matrixResult.getCols(); j++) {
			 matrixResult.display(i, j);
		 }
		 cout << endl;
	 }
	 return matrixResult;		
}
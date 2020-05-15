#include <iostream>
using namespace std;

template <class ElemType>
class Triple {
public:
	ElemType m_value;
	int m_row, m_col;

	Triple();
	Triple(int row, int col, ElemType value);
	~Triple();
};
template<class ElemType>
Triple<ElemType>::Triple() {
	m_row = 0;
	m_col = 0;
}
template <class ElemType>
Triple<ElemType>::Triple(int row, int col, ElemType value) {
	m_row = row;
	m_col = col;
	m_value = value;
}
template <class ElemType>
Triple<ElemType>::~Triple() {

}

template <class ElemType>
class TriSparseMartrix {
protected:
	Triple<ElemType> * m_elems;
	int m_rows, m_cols, m_num, m_maxSize;

public:
	TriSparseMartrix();
	TriSparseMartrix(int rows, int cols, int maxSize);
	~TriSparseMartrix();
	bool setElem(int row, int col, const ElemType & value);
	void setMartrix(int rows, int cols, int maxSize);
	void display();
	void display(int row, int col);
};
template <class ElemType>
TriSparseMartrix<ElemType>::TriSparseMartrix() {
	m_elems = NULL;
	m_rows = 0;
	m_cols = 0;
	m_num = 0;
	m_maxSize = 0;
}
template <class ElemType>
TriSparseMartrix<ElemType>::~TriSparseMartrix() {
	delete[] m_elems;
}
template <class ElemType>
TriSparseMartrix<ElemType>::TriSparseMartrix(int rows, int cols, int maxSize) {
	m_elems = new Triple<ElemType>[maxSize];
	m_rows = rows;
	m_cols = cols;
	m_num = 0;
	m_maxSize = maxSize;
}
template<class ElemType>
bool TriSparseMartrix<ElemType>::setElem(int row, int col, const ElemType & value)
{
	if (row > m_rows || col > m_cols || row < 1 || col < 1) {
		return false;
	}

	int i, j;

	for (j = m_num - 1; (j >= 0 && (row < m_elems[j].m_row || row == m_elems[j].m_row
		&& col < m_elems[j].m_col)); j--);

	if (j >= 0 && m_elems[j].m_col == col && m_elems[j].m_row == row) {
		if (value == 0) {
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
}
template<class ElemType>
void TriSparseMartrix<ElemType>::setMartrix(int rows, int cols, int maxSize)
{
	m_rows = rows;
	m_cols = cols;
	m_maxSize = maxSize;

	if (m_elems != NULL) {
		delete[] m_elems;
	}

	m_elems = new Triple<ElemType>[maxSize];
}
template<class ElemType>
inline void TriSparseMartrix<ElemType>::display()
{
	for (int i = 0; i < m_num; i++) {
		std::cout << m_elems[i].m_row << " " << m_elems[i].m_col << " " << m_elems[i].m_value << endl;
	}
}
template<class ElemType>
inline void TriSparseMartrix<ElemType>::display(int row, int col)
{
	for (int i = 0; i < m_num; i++) {
		if (m_elems[i].m_row == row && m_elems[i].m_col == col) {
			std::cout << m_elems[i].m_value << " ";
			return;
		}
	}
	std::cout << 0 << " ";
}

int main() {

	int row, col;
	int i, j;
	int tempElem;
	TriSparseMartrix<int> martrix;
	cin >> row >> col;

		martrix.setMartrix(row, col, row * col);
		for (i = 1; i <= row; i++) {
			for (j = 1; j <= col; j++) {
				cin >> tempElem;
				if (tempElem != 0) {
					martrix.setElem(i, j, tempElem);
				}
			}
		}
	
	for (i = 1; i <= col; i++) {
		for (j = 1; j <= row; j++) {
			martrix.display(j, i);
		}
		cout << endl;
	}

	return 0;
}

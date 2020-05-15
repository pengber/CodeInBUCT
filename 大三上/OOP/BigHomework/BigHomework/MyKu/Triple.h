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
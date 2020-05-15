#ifndef KRUSKAL_HELP_H_INCLUDE
#define KRUSKAL_HELP_H_INCLUDE
#define INFINITY 10000;

class kruskalForest {
public:
	int * m_treeNo;
	int m_vexNum;

	kruskalForest(int vexNum);
	~kruskalForest();
	bool isSameTree(int vex1, int vex2);
	void unionTree(int vex1, int vex2);
};
kruskalForest::kruskalForest(int vexNum) {
	m_treeNo = new int[vexNum];
	m_vexNum = vexNum;

	for (int i = 0; i < m_vexNum; i++) {
		m_treeNo[i] = i;
	}
}
inline kruskalForest::~kruskalForest()
{
	delete[] m_treeNo;
}
inline bool kruskalForest::isSameTree(int vex1, int vex2)
{
	return m_treeNo[vex1] == m_treeNo[vex2];
}
inline void kruskalForest::unionTree(int vex1, int vex2)
{
	int treeNo1 = m_treeNo[vex1];
	int treeNo2 = m_treeNo[vex2];

	for (int i = 0; i < m_vexNum; i++) {
		if (m_treeNo[i] == treeNo2) {
			m_treeNo[i] = treeNo1;
		}
	}
}

template <class WeightType>
class kruskalEdge {
public:
	int m_vex1, m_vex2;
	WeightType m_weight;
	kruskalEdge(int vex1 = -1, int vex2 = -1, WeightType weight = INFINITY);
};
template<class WeightType>
kruskalEdge<WeightType>::kruskalEdge(int vex1, int vex2, WeightType weight)
{
	m_vex1 = vex1;
	m_vex2 = vex2;
	m_weight = weight;
}
#endif // !KRUSKAL_HELP_H_INCLUDE

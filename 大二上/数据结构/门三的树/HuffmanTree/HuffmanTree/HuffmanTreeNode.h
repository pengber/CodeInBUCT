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

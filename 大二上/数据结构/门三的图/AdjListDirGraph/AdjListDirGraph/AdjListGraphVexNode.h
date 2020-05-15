/************************************************************************************
*Author	:Pengber
*Version	:1.0
*Date		:2018/11/25
************************************************************************************/
/************************************************************************************
*Problem	:

*Tips:		:
************************************************************************************/
/************************************************************************************
*History	:
************************************************************************************/
#ifndef ADJLISTGRAPHVEXNODE_H_INCLUDE
#define ADJLISTGRAPHVEXNODE_H_INCLUDE

#include "SimpleLinkList.h"
template <class ElemType>
class AdjListGraphVexNode {
public:
	ElemType m_data;
	SimpleLinkList<int> * m_adjList;

	AdjListGraphVexNode();
	AdjListGraphVexNode(ElemType data, SimpleLinkList<int> * m_adjList = NULL);
	virtual ~AdjListGraphVexNode();
};
template <class ElemType>
AdjListGraphVexNode<ElemType>::AdjListGraphVexNode() {
	m_adjList = NULL;
}
template <class ElemType>
AdjListGraphVexNode<ElemType>::AdjListGraphVexNode(ElemType data, SimpleLinkList<int> * m_adjList) {
	m_data = data;
	m_adjList = adjList;
}
template <class ElemType>
AdjListGraphVexNode<ElemType>::~AdjListGraphVexNode() {
	delete m_adjList;
	m_adjList = NULL;
}
#endif // !ADJLISTGRAPHVEXNODE_H_INCLUDE

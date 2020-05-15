/************************************************************************************
*Author	:Pengber
*Version	:1.0
*Date		:2018/10/16
************************************************************************************/
/************************************************************************************
*Problem	:
			1.在destroy中将指向vertexNode的指针至于NULL的话,vertexNode成员的指针会怎么办?
*Tips:		:
			1.邻接矩阵里面用int ** m_matrix和int * elems两个变量存储图,而邻接表是用
			一个AdjListDirGraph<ElemType> * m_vertexTable来存储图;其他不变
************************************************************************************/
/************************************************************************************
*History	:
************************************************************************************/
#ifndef ADJLISTDIRGRAPH_H_INCLUDE
#define ADJLISTDIRGRAPH_H_INCLUDE

#include "AdjListGraphVexNode.h"
#include "LinkQueue.h"
#include <iostream>
#ifndef INVISITED_DEFINE_INCLUDE
#define INVISITED_DEFINE_INCLUDE
#define UNVISITED false;
#define VISITED true;
#endif // !INVISITED_DEFINE_INCLUDE

//#define DEBUG
//#define REMIND

template <class ElemType>
class AdjListDirGraph {
private:
	int m_vertexSize;
	int m_edgeSize;
	AdjListGraphVexNode<ElemType> * m_vertexTable;
	mutable bool * m_visited;

	void destroyHelp();

	void DFSHelp(int vertex, void(*visit)(ElemType &));

	void BFSHelp(int vertex, void(*visit)(ElemType &));
public:
//基本成员函数
	AdjListDirGraph();
	AdjListDirGraph(ElemType * vertex, int vexNum);
	~AdjListDirGraph();
//特征函数
	//得
	int getVertexCount();					//得到顶点数目

	int getEdgeCount();						//得到边的数目

	int getVertex(ElemType & elem);			//得到元素在原图中得位置

	ElemType getVertexElem(int vertex);		//得到顶点元素值

	bool getVisited(int vertex);			//得到结点访问信息

	int getFirstAdjVertex(int vertex);		//得到vertex的第一个邻接点

	int getNextAdjVertex(int vertex1, int vertex2);			//得到vertex1相对于vertex2的第一个临界点

	//判无
	//插
	bool insertEdge(int vertex1, int vertex2);

	//改
	void setGraph(ElemType * vertex, int vexNum);

	bool setElem(int vertex, ElemType elem);

	bool setVisited(int vertex);
	//删
	bool deleteEdge(int vertex1, int vertex2);

	//遍历
	void DFSTraverse(int vertex, void(*visit)(ElemType &));

	void BFSTraverse(int vertex, void(*visit)(ElemType &));
	//特殊函数
	void display();
};
/***********************************私有成员函数实现**********************************/
template <class ElemType>
void AdjListDirGraph<ElemType>::destroyHelp() {
	this->m_visited = NULL;
	for (int i = 0; i < m_vertexSize; i++) {
		if (this->m_vertexTable[i]->m_adjList != NULL) {
			delete this->m_vertexTable[i]->m_adjList;
		}
	}
}
template<class ElemType>
void AdjListDirGraph<ElemType>::DFSHelp(int vertex, void(*visit)(ElemType &))
{

	this->m_visited[vertex] = VISITED;
	(*visit)(this->m_vertexTable[vertex].m_data);

	for (int vexTemp = this->getFirstAdjVertex(vertex);
		vexTemp != -1; 
		vexTemp = this->getNextAdjVertex(vextex, vexTemp)) {
		
		if (this->m_visited[vexTemp] == UNVISITED) {
			DFSHelp(vexTemp, visit);
		}
	}

}
template <class ElemType>
void AdjListDirGraph<ElemType>::BFSHelp(int vertex, void(*visit)(ElemType &)) {
	
	this->m_visited[vertex] = VISITED;
	(*visit)(this->m_vertexTable[vertex].m_data);

	LinkQueue<int> queue;
	queue.inQueue(vertex);

	while (!queue.isEmpty()) {

	}

}

/*=================================私有成员函数实现完毕================================*/
/***********************************基本成员函数实现**********************************/
/*
int getVertexCount();					//得到顶点数目
int getEdgeCount();						//得到边的数目
int getVertex(ElemType * elem);			//得到元素在原图中得位置
ElemType getVertexElem(int vertex);		//得到顶点元素值
bool getVisited(int vertex);			//得到结点访问信息
int getFirstAdjVertex(int vertex);		//得到vertex的第一个邻接点
int getNextAdjVertex(int vertex1, int vertex2)				//得到vertex1相对于vertex2的第一个临界点
bool insertEdge(int vertex1, int vertex2);
void setGraph(ElemType * vertex, int vexNum);
bool setElem(int vertex, ElemType elem);
bool setVisited(int vertex);
bool deleteEdge(int vertex1, int vertex2);
void DFSTraverse(int vertex, void(*visit)(ElemType &));
void BFSTraverse(int vertex, void(*visit)(ElemType &));
*/
template <class ElemType>
AdjListDirGraph<ElemType>::AdjListDirGraph() {
	this->m_vertexSize = 0;
	this->m_edgeSize = 0;
	this->m_vertexTable = NULL;
	this->m_visited = NULL;
}
template <class ElemType>
AdjListDirGraph<ElemType>::AdjListDirGraph(ElemType * vertex, int vexNum) {
	this->m_vertexSize = vexNum;
	this->m_edgeSize = 0;
	this->m_vertexTable = new AdjListGraphVexNode<ElemType>[m_vertexSize];
	this->m_visited = new bool[m_vertexSize];

	for (int i = 0; i < m_vertexSize; i++) {
		m_vertexTable[i].m_data = vertex[i];
		m_visited = UNVISITED;
	}
}
template <class ElemType>
AdjListDirGraph<ElemType>::~AdjListDirGraph() {
	destroyHelp();
}

template<class ElemType>
 int AdjListDirGraph<ElemType>::getFirstAdjVertex(int vertex)
{
	 if (vertex < 0 || vertex >= this->m_vertexSize)
	 {
		 std::out_of_range("查找不到当前小标的顶点信息\n");
	 }

	if (this->m_vertexTable[vertex].m_adjList == NULL) {
		return -1;
	}
	else {
		int vex;
		this->m_vertexTable[vertex].m_adjList.getElem(1, vex);
		return vex;
	}
}
template<class ElemType>
 int AdjListDirGraph<ElemType>::getNextAdjVertex(int vertex1, int vertex2)
{
#ifdef DEBUG    // 插桩调试信息
	 std::cout << "FUN:" << __func__ << ", LINE:" << __LINE__ << std::endl;   // 输出函数信息
#endif
																			  // 函数实现部分
	 if (vertex1 < 0 || vertex1 >= this->m_vertexSize)
	 {
		 throw std::out_of_range("第1个参数不在正常范围!");// 抛出异常
	 }
	 if (vertex2 < 0 || vertex2 >= this->m_vertexSize)
	 {
		 throw std::out_of_range("第2个参数不在正常范围!");// 抛出异常
	 }

	 if (vertex1 == vertex2)
	 {
		 throw std::out_of_range("两个参数不能等于!");				// 抛出异常
	 }

	 if (this->m_vertexTable[vertex1].m_adjList == NULL) {
		 return -1;
	 }
	 
	 int vex;
	 this->m_vertexTable[vertex1].m_adjList.getElemPos(vex, vertex2);

	 if (vex < this->m_vertexTable[vertex1].m_adjList.getLengh()) {
		 
		 return this->m_vertexTable[vertex1].m_adjList.getElem(vex + 1);
	 }
	 else {
		 return -1;
}
template<class ElemType>
inline bool AdjListDirGraph<ElemType>::insertEdge(int vertex1, int vertex2) {
#ifdef DEBUG    // 插桩调试信息
	std::cout << "FUN:" << __func__ << ", LINE:" << __LINE__ << std::endl;   // 输出函数信息
#endif
																			 // 函数实现部分
	if (vertex1 < 0 || vertex1 >= this->m_vertexSize)
	{
		throw std::out_of_range("第1个参数不在正常范围!");// 抛出异常
	}
	if (vertex2 < 0 || vertex2 >= this->m_vertexSize)
	{
		throw std::out_of_range("第2个参数不在正常范围!");// 抛出异常
	}
	//system("pause");
	if (vertex1 == vertex2)
	{
		throw std::out_of_range("两个参数不能等于!");				// 抛出异常
	}

	int vex;

	if (this->m_vertexTable[vertex1].adjList == NULL) {
		this->m_vertexTable[vertex1].adjList = new SimpleLinkList<int>;
	}

	this->m_vertexTable[vertex1].adjList.getElemPos(vex, vertex2);

	if (vex == -1) {
		this->m_vertexTable[vertex1].adjList.insertAfterAll(vertex2);
	}
	else {
		return false;
	}

	if (this->vertexTable[vertex2].adjList == NULL) {
		this->m_vertexTable[vertex1].adjList = new SimpleLinkList<int>;
	}

	this->m_vertexTable[vertex1].adjList.getElemPos(vex, vertex1);

	if (vex == -1) {
		this->m_vertexTable[vertex2].adjList.insertAfterAll(vertex1);
	}
	else {
		return false;
	}

	m_edgeSize++;
	return true;
}
#endif // !ADJLISTDIRGRAPH_H_INCLUDE
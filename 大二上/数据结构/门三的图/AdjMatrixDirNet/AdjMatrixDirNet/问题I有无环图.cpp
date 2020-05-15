#ifndef NODE_H_INCLUDE
#define NODE_H_INCLUDE
#include <iostream>
using namespace std;
template <class ElemType>
struct Node {
public:
	Node();
	Node(const ElemType & elem, Node<ElemType> * link = NULL);
	virtual ~Node();
	ElemType data;
	Node<ElemType> * next;
};
//函数名称:Node()
//函数功能:默认构造函数
//操作结果:返回一个指针域指向NULL的结点
template <class ElemType>
Node<ElemType>::Node() {
	this->next = NULL;
}
//函数名称:Node(const ElemType & elem, Node<ElemType> * link)
//函数功能:赋值构造函数
//操作结果:创建一个由数据信息的结点
template <class ElemType>
Node<ElemType>::Node(const ElemType & elem, Node<ElemType> * link) {
	this->data = elem;
	this->next = link;
}
//函数名称:virtual ~Node()
//函数功能:析构函数
template <class ElemType>
Node<ElemType>::~Node() {

}
#endif // !NODE_H_INCLUDE

#ifndef LINKSTACK_H_INCLUDE
#define LINKSTACK_H_INCLUDE

#include <iostream>
//#include "Node.h"
//#define DEBUG
//#define REMIND                            //输出提示信息将这条语句打开

template <class ElemType>
class LinkStack {
	/********************************公共接口**********************************/
public:
	//基本成员函数:
	LinkStack();

	virtual ~LinkStack();
	//特征函数:
	int getLength() const;

	bool getTopElem(ElemType & elem) const;

	//判
	bool isEmpty() const;

	//插
	bool push(const ElemType & elem);

	//改
	//无

	//删
	bool pop(ElemType & elem);

	void clean();
	//特殊函数
	void display() const;

	void traverse(void(*visit)(const ElemType &)) const;
	//重载函数
	//LinkStack<ElemType> & operator(const LinkStack<ElemType> & copy);
	/*================================公共接口声明完毕==============================*/
protected:
	Node<ElemType> * top;
};
/*******************************基本成员函数实现*********************************/
template <class ElemType>
LinkStack<ElemType>::LinkStack() {
	top = NULL;
}
template <class ElemType>
LinkStack<ElemType>::~LinkStack() {
	this->clean();
}
/*==============================基本成员函数实现完毕==============================*/
/*******************************基本成员函数实现*********************************/
//函数名称: int getLength() const
//函数功能: 返回链表长度
//无子函数
template <class ElemType>
int LinkStack<ElemType>::getLength() const {
	Node<ElemType> * tempPtr;
	tempPtr = top;
	int length = 0;

	while (tempPtr != NULL) {
		length++;
		tempPtr = tempPtr->next;
	}

	return length;
}
//函数名称: bool getTopElem(ElemType & elem) const
//函数功能: 返回栈顶首元素
template <class ElemType>
bool LinkStack<ElemType>::getTopElem(ElemType & elem) const {
	if (this->isEmpty()) {
#ifdef REMIND
		std::cout << "链栈为空,无法查询栈顶元素" << endl;
#endif
		return false;
	}
	else {
		elem = top->data;
		return true;
	}
}
//函数名称: bool isEmpty() const
//函数功能: 判断链表是否为空,空则返回1,为空返回0
template <class ElemType>
bool LinkStack<ElemType>::isEmpty() const {
	return top == NULL;
}
//函数名称: bool push(const ElemType & elem)
//函数功能: 进行push操作
//无子函数
//注意事项: 将第一个元素当成普通元素就行
template <class ElemType>
bool LinkStack<ElemType>::push(const ElemType & elem) {
	Node<ElemType> * tempPtr;

	tempPtr = new Node<ElemType>(elem, top);
	top = tempPtr;
	return true;

}
//函数名称: bool pop(ElemType & elem)
//函数功能: 进行pop操作,值由引用调用得回
template <class ElemType>
bool LinkStack<ElemType>::pop(ElemType & elem) {
	if (this->isEmpty()) {
#ifdef REMIND
		std::cout << "链表为空,不能进行pop操作" << std::endl;
#endif
		return false;
	}
	else {
		Node<ElemType> * tempPtr;

		tempPtr = top;
		elem = top->data;
		top = top->next;
		delete tempPtr;
		return true;
	}
}

//函数名称: void clean()
//函数功能: 将链栈清空
//其子函数: bool pop();
template <class ElemType>
void LinkStack<ElemType>::clean() {
	ElemType tempElem;

	while (top != NULL) {
		this->pop(tempElem);
	}
}
//函数名称: void display()
//函数功能: 显示栈内元素
template <class ElemType>
void LinkStack<ElemType>::display() const {
	Node<ElemType> * tempPtr;
	tempPtr = top;
	while (tempPtr != NULL) {
		cout << tempPtr->data << endl;
		tempPtr = tempPtr->next;
	}
}
/*================================公共接口声明完毕==============================*/
#endif
#ifndef AdjMatrixDirNet_H_INCLUDE
#define AdjMatrixDirNet_H_INCLUDE
#include <iostream>
#include <stdexcept>                          //out_of_range需要
#include <iomanip>                            //display函数需要
//#include "LinkQueue.h"                        //深度优先搜索需要
//#include "LinkStack.h"                        //拓扑排序需要
#include "assert.h"

#define INFINITY 10000
#ifndef INVISITED_DEFINE_INCLUDE
#define INVISITED_DEFINE_INCLUDE
#define UNVISITED false
#define VISITED true
#endif

//#define REMIND
//#define DEBUG
template <class ElemType, class WeightType>
class AdjMatrixDirNet {
public:
	AdjMatrixDirNet();
	AdjMatrixDirNet(ElemType * vertex, int vexNum);
	~AdjMatrixDirNet();
	//特征函数
	//得
	int getVertexCount();                   //得到顶点数目

	int getEdgeCount();                     //得到边的数目

	int getVertex(ElemType & elem);         //得到元素在原图中得位置

	ElemType getVertexElem(int vertex);     //得到顶点元素值

	bool getVisited(int vertex);            //得到结点访问信息

	int getFirstAdjVertex(int vertex);      //得到vertex的第一个邻接点

	int getNextAdjVertex(int vertex1, int vertex2);         //得到vertex1相对于vertex2的第一个临界点

	WeightType getWeight(int vertex1, int vertex2);
	//判
	//插
	bool insertEdge(int vertex1, int vertex2, WeightType weight);

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

	void input();

	void shortestPathDij(int vertex, WeightType *path);

	bool topologicalSort();
protected:
	int m_vertexSize;                       //顶点个数
	int m_edgeSize;                         //边数
	WeightType **m_matrix;                      //邻接矩阵
	mutable bool * m_visited;               //是否访问过标志位
	ElemType * m_elems;

	void destroyGraphHelp();

	void DFSHelp(int vertex, void(*visit)(ElemType &));
	void BFSHelp(int vertex, void(*visit)(ElemType &));
};
template <class ElemType, class WeightType>
void AdjMatrixDirNet<ElemType, WeightType>::destroyGraphHelp() {
	delete[] m_elems;
	m_elems = NULL;

	delete[] m_visited;
	m_visited = NULL;

	for (int i = 0; i < m_vertexSize; i++) {
		delete[] m_matrix[i];
	}
	delete[] m_matrix;
	m_matrix = NULL;
}
//函数名称: void DFSHelp(int vertex, void(*visit)(ElemType &))
//函数功能: 深度优先搜索辅助函数
template <class ElemType, class WeightType>
void AdjMatrixDirNet<ElemType, WeightType>::DFSHelp(int vertex, void(*visit)(ElemType &)) {
#ifdef DEBUG
	std::cout << "FUNC:" << __func__ << ",LINE:" << __LINE__ << std::endl;
#endif // DEBUG
	if (vertex < 0 || vertex >= this->m_vertexSize) {
		throw std::out_of_range("vertex参数范围不正确!");
	}
	if (m_visited[vertex] == UNVISITED) {
		ElemType elem = this->getVertexElem(vertex);
		(*visit)(elem);
		this->m_visited[vertex] = VISITED;
	}
	int vextemp;
	for (vextemp = this->getFirstAdjVertex(vertex); vextemp != -1; vextemp = this->getNextAdjVertex(vertex, vextemp)) {
		if (this->m_visited[vextemp] == UNVISITED) {
			DFSHelp(vextemp, visit);
		}
	}

}
//函数名称: void BFSHelp(int vertex, void(*visit)(ElemType &))
//函数功能: 实现广度优先搜索
/*template <class ElemType, class WeightType>
void AdjMatrixDirNet<ElemType, WeightType>::BFSHelp(int vertex, void(*visit)(ElemType &)) {
#ifdef DEBUG
std::cout << "FUNC:" << __func__ << ",LINE:" << __LINE__ << std::endl;
#endif // DEBUG
if (m_visited[vertex] == UNVISITED) {
ElemType elem = this->getVertexElem(vertex);
(*visit)(elem);
this->setVisited(vertex);
}

LinkQueue<int> queue;
int vexTemp;
queue.inQueue(vertex);
ElemType elem;
while (!queue.isEmpty()) {
queue.outQueue(vertex);

for (vexTemp = this->getFirstAdjVertex(vertex);
vexTemp != -1;
vexTemp = this->getNextAdjVertex(vertex, vexTemp))
{
if (this->m_visited[vexTemp] == UNVISITED) {
this->m_visited[vexTemp] = VISITED;
elem = getVertexElem(vexTemp);
(*visit)(elem);
queue.inQueue(vexTemp);
}
}
}
}
*/
/***********************************基本成员函数实现**********************************/
/*
int getVertexCount();                   //得到顶点数目
int getEdgeCount();                     //得到边的数目
int getVertex(ElemType * elem);         //得到元素在原图中得位置
ElemType getVertexElem(int vertex);     //得到顶点元素值
bool getVisited(int vertex);            //得到结点访问信息
int getFirstAdjVertex(int vertex);      //得到vertex的第一个邻接点
int getNextAdjVertex(int vertex1, int vertex2)              //得到vertex1相对于vertex2的第一个临界点
bool insertEdge(int vertex1, int vertex2);
void setGraph(ElemType * vertex, int vexNum);
bool setElem(int vertex, ElemType elem);
bool setVisited(int vertex);
bool deleteEdge(int vertex1, int vertex2);
void DFSTraverse(int vertex, void(*visit)(ElemType &));
void BFSTraverse(int vertex, void(*visit)(ElemType &));
*/
template <class ElemType, class WeightType>
AdjMatrixDirNet<ElemType, WeightType>::AdjMatrixDirNet() {
	this->m_vertexSize = 0;
	this->m_edgeSize = 0;
	this->m_elems = NULL;
	this->m_visited = NULL;
	this->m_matrix = NULL;
}
template <class ElemType, class WeightType>
AdjMatrixDirNet<ElemType, WeightType>::AdjMatrixDirNet(ElemType * vertex, int vexNum) {
#ifdef DEBUG
	std::cout << "FUNC:" << __func__ << ",LINE:" << __LINE__ << std::endl;
#endif // DEBUG
	if (vexNum < 0) {
		throw std::out_of_range("vexNum参数不能为负数!");
	}
	this->m_vertexSize = vexNum;
	this->m_edgeSize = 0;

	this->m_elems = new ElemType[m_vertexSize];
	assert(this->m_elems);
	this->m_visited = new bool[m_vertexSize];
	assert(this->m_visited);
	this->m_matrix = (int **)new int *[m_vertexSize];

	for (int i = 0; i < m_vertexSize; i++) {
		m_elems[i] = vertex[i];
		m_visited[i] = UNVISITED;
		m_matrix[i] = new int[m_vertexSize];
		assert(m_matrix[i]);
	}
	int i; int j;
	for (i = 0; i < m_vertexSize; i++) {
		for (j = 0; j < m_vertexSize; j++) {
			m_matrix[i][j] = INFINITY;
		}
	}
}
template <class ElemType, class WeightType>
AdjMatrixDirNet<ElemType, WeightType>::~AdjMatrixDirNet() {
#ifdef DEBUG
	std::cout << "FUNC:" << __func__ << ",LINE:" << __LINE__ << std::endl;
#endif // DEBUG
	destroyGraphHelp();
}
/*===================================基本成员函数实现完毕============================*/
/************************************特征成员函数实现********************************/
//函数名称: int getVertexCount()
//函数功能: 返回顶点个数
template <class ElemType, class WeightType>
int AdjMatrixDirNet<ElemType, WeightType>::getVertexCount() {
#ifdef DEBUG
	std::cout << "FUNC:" << __func__ << ",LINE:" << __LINE__ << std::endl;
#endif // DEBUG
	return m_vertexSize;
}
//函数名称: int getEdgeCount()
//函数功能: 返回边数
template <class ElemType, class WeightType>
int AdjMatrixDirNet<ElemType, WeightType>::getEdgeCount() {
#ifdef DEBUG
	std::cout << "FUNC:" << __func__ << ",LINE:" << __LINE__ << std::endl;
#endif // DEBUG
	return m_edgeSize;
}
//函数名称: int getVertex(ElemType & elem)
//函数功能: 返回元素的顶点位置,若无,则返回-1;
template <class ElemType, class WeightType>
int AdjMatrixDirNet<ElemType, WeightType>::getVertex(ElemType & elem) {
#ifdef DEBUG
	std::cout << "FUNC:" << __func__ << ",LINE:" << __LINE__ << std::endl;
#endif // DEBUG
	for (int i = 0; i < this->m_vertexSize; i++) {
		if (this->m_elems[i] == elem) {
			return i;
		}
	}
	return -1;
}
//函数名称: ElemType getVertexElem(int vertex)
//函数功能: 返回顶点元素值
template <class ElemType, class WeightType>
ElemType AdjMatrixDirNet<ElemType, WeightType>::getVertexElem(int vertex) {
#ifdef DEBUG
	std::cout << "FUNC:" << __func__ << ",LINE:" << __LINE__ << std::endl;
#endif // DEBUG
	if (vertex < 0 || vertex >= this->m_vertexSize) {
		throw std::out_of_range("vertex参数范围不合法!");
	}

	return this->m_elems[vertex];
}
//函数名称: bool getVisited(int vertex)
//函数功能: 得到某顶点的访问信息
template <class ElemType, class WeightType>
bool AdjMatrixDirNet<ElemType, WeightType>::getVisited(int vertex) {
#ifdef DEBUG
	std::cout << "FUNC:" << __func__ << ",LINE:" << __LINE__ << std::endl;
#endif // DEBUG
	if (vertex < 0 || vertex >= this->m_vertexSize) {
		throw std::out_of_range("vertex参数范围不合法!");
	}
	return m_visited[vertex];
}
//函数名称: int getFirstAdjVertex(int vertex)
//函数功能: 返回vertex的第一个邻接点
template <class ElemType, class WeightType>
int AdjMatrixDirNet<ElemType, WeightType>::getFirstAdjVertex(int vertex) {
#ifdef DEBUG
	std::cout << "FUNC:" << __func__ << ",LINE:" << __LINE__ << std::endl;
#endif // DEBUG
	if (vertex < 0 || vertex >= m_vertexSize) {
		throw std::out_of_range("vertex参数范围不合法!");
	}
	for (int i = 0; i < m_vertexSize; i++) {
		if (m_matrix[vertex][i] != INFINITY) {
			return i;
		}
	}
	return -1;
}
//函数名称: int getNextAdjVertex(int vertex1, int vertex2) 
//函数功能: 返回vertex1行和vertex2+1列以后的邻接顶点
template <class ElemType, class WeightType>
int AdjMatrixDirNet<ElemType, WeightType>::getNextAdjVertex(int vertex1, int vertex2) {
#ifdef DEBUG
	std::cout << "FUNC:" << __func__ << ",LINE:" << __LINE__ << std::endl;
#endif // DEBUG
	if (vertex1 < 0 || vertex1 >= m_vertexSize) {
		throw std::out_of_range("vertex1参数范围不合法!");
	}
	if (vertex2 < 0 || vertex2 >= m_vertexSize) {
		throw std::out_of_range("vertex2参数范围不合法!");
	}
	if (vertex1 == vertex2) {
		throw std::out_of_range("vertex1和vertex2不能相等!");
	}

	for (int i = vertex2 + 1; i < m_vertexSize; i++) {
		if (m_matrix[vertex1][i] != INFINITY) {
			return i;
		}
	}
	return -1;
}
//函数名称: WeightType getWeight();
template<class ElemType, class WeightType>
inline WeightType AdjMatrixDirNet<ElemType, WeightType>::getWeight(int vertex1, int vertex2)
{
#ifdef DEBUG
	std::cout << "FUNC:" << __func__ << ",LINE:" << __LINE__ << std::endl;
#endif // DEBUG
	if (vertex1 < 0 || vertex1 >= m_vertexSize) {
		throw std::out_of_range("vertex1参数范围不合法!");
	}
	if (vertex2 < 0 || vertex2 >= m_vertexSize) {
		throw std::out_of_range("vertex2参数范围不合法!");
	}
	if (vertex1 == vertex2) {
		throw std::out_of_range("vertex1和vertex2不能相等!");
	}
	return m_matrix[vertex1][vertex2];
}
//函数名称: bool insertEdge(int vertex1, int vertex2) 
//函数功能: 在vertex1与vertex2之间插入边
template <class ElemType, class WeightType>
bool AdjMatrixDirNet<ElemType, WeightType>::insertEdge(int vertex1, int vertex2, WeightType weight) {
#ifdef DEBUG
	std::cout << "FUNC:" << __func__ << ",LINE:" << __LINE__ << std::endl;
#endif // DEBUG
	if (vertex1 < 0 || vertex1 >= m_vertexSize) {
		throw std::out_of_range("vertex1参数范围不合法!");
	}
	if (vertex2 < 0 || vertex2 >= m_vertexSize) {
		throw std::out_of_range("vertex2参数范围不合法!");
	}
	if (vertex1 == vertex2) {
		throw std::out_of_range("vertex1不能等于vertex2!");
	}

	if (this->m_matrix[vertex1][vertex2] == INFINITY) {
		this->m_matrix[vertex1][vertex2] = weight;
		m_edgeSize++;
		return true;
	}
	else {
#ifdef REMIND
		std::cout << "两顶点已经有边,不能设置边了!" << std::endl;
#endif // REMIND
		return false;                       //这个返回false我觉得返回的没有意义
	}
}
//函数名称: void setGraph(ElemType * vertex, int vexNum)
//函数功能: 重新设置图的顶点元素和个数,将边置为0
template <class ElemType, class WeightType>
void AdjMatrixDirNet<ElemType, WeightType>::setGraph(ElemType * vertex, int vexNum) {
#ifdef DEBUG
	std::cout << "FUNC:" << __func__ << ",LINE:" << __LINE__ << std::endl;
#endif // DEBUG
	destroyGraphHelp();

	if (vexNum < 0) {
		throw std::out_of_range("vexNum参数不能为负数!");
	}
	this->m_vertexSize = vexNum;
	this->m_edgeSize = 0;

	this->m_elems = new ElemType[m_vertexSize];
	assert(this->m_elems);
	this->m_visited = new bool[m_vertexSize];
	assert(this->m_visited);
	this->m_matrix = (int **)new int *[m_vertexSize];

	for (int i = 0; i < m_vertexSize; i++) {
		m_elems[i] = vertex[i];
		m_visited[i] = UNVISITED;
		m_matrix[i] = new int[m_vertexSize];
		assert(m_matrix[i]);
	}
	int i; int j;
	for (i = 0; i < m_vertexSize; i++) {
		for (j = 0; j < m_vertexSize; j++) {
			m_matrix[i][j] = INFINITY;
		}
	}
}
//函数名称: bool setElem(int vertex, ElemType elem)
//函数功能: 设置顶点元素,参数范围不合法返回false
template <class ElemType, class WeightType>
bool AdjMatrixDirNet<ElemType, WeightType>::setElem(int vertex, ElemType elem) {
#ifdef DEBUG
	std::cout << "FUNC:" << __func__ << ",LINE:" << __LINE__ << std::endl;
#endif // DEBUG
	if (vertex < 0 || vertex >= m_vertexSize) {
#ifdef REMIND
		std::cout << "vertex参数范围不合法!" << std::endl;
#endif // REMIND
		return false;
	}
	else {
		m_elems[vertex] = elem;
		return true;
	}
}
//函数名称: bool setVisited(int vertex)
//函数功能: 设置vertex为访问过,已经为访问过的返回假
template <class ElemType, class WeightType>
bool AdjMatrixDirNet<ElemType, WeightType>::setVisited(int vertex) {
#ifdef DEBUG
	std::cout << "FUNC:" << __func__ << ",LINE:" << __LINE__ << std::endl;
#endif // DEBUG
	if (vertex < 0 || vertex >= m_vertexSize) {
		throw std::out_of_range("vertex参数不合法!");
	}

	if (m_visited[vertex]) {
#ifdef REMIND
		std::cout << "该顶点已经访问过,返回假!" << endl;
#endif // REMIND
		return false;
	}
	else {
		m_visited[vertex] = VISITED;
		return true;
	}
}
//函数名称: bool deleteEdge<int vertex1, int vertex2)
//函数功能: 删除vertex1指向vertex2之间的边,没有边返回失败
template <class ElemType, class WeightType>
bool AdjMatrixDirNet<ElemType, WeightType>::deleteEdge(int vertex1, int vertex2) {
#ifdef DEBUG
	std::cout << "FUNC:" << __func__ << ",LINE:" << __LINE__ << std::endl;
#endif // DEBUG
	if (vertex1 < 0 || vertex1 >= m_vertexSize) {
		throw std::out_of_range("vertex1参数范围不合法!");
	}
	if (vertex2 < 0 || vertex2 >= m_vertexSize) {
		throw std::out_of_range("vertex2参数范围不合法!");
	}
	if (vertex1 == vertex2) {
		throw std::out_of_range("vertex1不能等于vertex2!");
	}

	if (m_matrix[vertex1][vertex2] != INFINITY) {
		m_matrix[vertex1][vertex2] = INFINITY;
		m_edgeSize--;
		return true;
	}
	else {
#ifdef REMIND
		std::cout << "vertex1与vertex2原本就没有边!无法删除!" << std::endl;
#endif // REMIND
		return false;
	}
}
//函数名称: void DFSTraverse(int vertex, void(*visit)(ElemType &))
//函数功能: 深度优先搜索
template <class ElemType, class WeightType>
void AdjMatrixDirNet<ElemType, WeightType>::DFSTraverse(int vertex, void(*visit)(ElemType &)) {
#ifdef DEBUG
	std::cout << "FUNC:" << __func__ << ",LINE:" << __LINE__ << std::endl;
#endif // DEBUG
	for (int i = vertex; i < m_vertexSize; i++) {
		DFSHelp(i, visit);
	}
}
template <class ElemType, class WeightType>
void AdjMatrixDirNet<ElemType, WeightType>::BFSTraverse(int vertex, void(*visit)(ElemType &)) {
#ifdef DEBUG
	std::cout << "FUNC:" << __func__ << ",LINE:" << __LINE__ << std::endl;
#endif // DEBUG
	for (int i = vertex; i < m_vertexSize; i++) {
		BFSHelp(i, visit);
	}
}
/*=================================特征成员函数实现完毕===============================*/
//函数名称: void display()
//函数功能: 显示图的信息
template <class ElemType, class WeightType>
void AdjMatrixDirNet<ElemType, WeightType>::display() {
#ifdef DEBUG
	std::cout << "FUNC:" << __func__ << ",LINE:" << __LINE__ << std::endl;
#endif // DEBUG
	std::cout << "此图的顶点数:" << this->getVertexCount() << "个" << std::endl;
	std::cout << "此图的边数:" << this->getEdgeCount() << "条" << std::endl;
	/*****************输出邻接矩阵的列标*************/
	std::cout << "\\";
	for (int i = 0; i < m_vertexSize; i++) {
		std::cout << std::setw(4) << m_elems[i];
	}
	std::cout << std::endl;
	/*==============================================*/
	/***************输出邻接矩阵的行标和矩阵*********/
	for (int i = 0; i < m_vertexSize; i++) {
		std::cout << m_elems[i];
		for (int j = 0; j < m_vertexSize; j++) {
			std::cout << std::setw(4) << m_matrix[i][j];
		}
		std::cout << std::endl;
		std::cout << std::endl;
	}
	/*=============================================*/
}
template <class ElemType, class WeightType>
void AdjMatrixDirNet<ElemType, WeightType>::input() {
	int num, elems[1000];
	std::cin >> num;
	for (int i = 0; i < num; i++) {
		elems[i] = i;
	}
	this->setGraph(elems, num);
}
//函数名称: shortestPathDij(int vertex, WeightType * &path)
//函数功能: 利用引用传递返回vertex对于每个点的最短路径
//注意事项: WeightType path[],bool p[][],m_visited[]
template <class ElemType, class WeightType>
void AdjMatrixDirNet<ElemType, WeightType>::shortestPathDij(int vertex, WeightType * path) {
	bool p[1000][1000];                             //privotal关键的,表征是否为vertex到达某一点的必经点
	for (int i = 0; i < m_vertexSize; i++) {
		m_visited[i] = UNVISITED;
		path[i] = m_matrix[vertex][i];
		for (int j = 0; j < m_vertexSize; j++) p[i][j] = false;

		if (path[i] < INFINITY) {
			p[i][vertex] = true;                    //表示vertex经过vertex到达i为vertex为必经点
			p[vertex][vertex] = true;               //vertex到自己为必经点
		}
	}

	this->setVisited(vertex);
	path[vertex] = 0;
	int v;                                          //这个v暂时存储每一次得出的最短路径的新结点
	for (int i = 1; i < m_vertexSize; i++) {
		WeightType min = INFINITY;
		for (int j = 0; j < m_vertexSize; j++) {
			if (!m_visited[j] && path[j] < min) {
				min = path[j];
				v = j;
			}
		}
		m_visited[v] = VISITED;
		//经历上一个循环后,得出第一个最短路径的结点<vertex, v>中的v,下面更新最短路径数组
		for (int w = 0; w < m_vertexSize; w++) {
			if (!m_visited[w] && (min + m_matrix[v][w] < path[w])) {
				path[w] = min + m_matrix[v][w];
				for (int i = 0; i < m_vertexSize; i++) {
					p[w][i] = p[v][i];
				}
				p[w][w] = true;
			}
		}


	}
}
template <class ElemType, class WeightType>
bool AdjMatrixDirNet<ElemType, WeightType>::topologicalSort() {
	LinkStack<int> stack;
	int count = 0;                          //及拓扑排序中输出的顶点数
	int degree[1000] = { 0 };
	int tempVertex;
	int coutIndex = 0;
	int coutArray[1000] = { 0 };
	int p;
	//求度
	for (int i = 0; i < m_vertexSize; i++) {
		for (int j = 0; j < m_vertexSize; j++) {
			if (m_matrix[j][i] != INFINITY) {
				degree[i]++;
			}
		}
	}
	for (int i = 0; i < m_vertexSize; i++) {
		if (degree[i] == 0) {
			stack.push(i);
		}
	}

	while (!stack.isEmpty()) {
		stack.pop(tempVertex);
		coutArray[coutIndex++] = tempVertex;
		count++;
		//更新输出图中度为0的顶点后的度为0
		for (p = this->getFirstAdjVertex(tempVertex); p != -1; p = this->getNextAdjVertex(tempVertex, p)) {
			if ((--degree[p]) == 0) {
				stack.push(p);
			}
		}
	}

	if (count == m_vertexSize) {
		std::cout << "NO" << std::endl;
		return true;
	}
	else {
		std::cout << "YES" << std::endl;
		return false;
	}

}
#endif // !AdjMatrixDirNet_H_INCLUDE

using namespace std;

int main() {
	
	int num, elems[1000];
	int  temp1, temp2;

	int edgeNum;

	while (cin >> num >> edgeNum&& num || edgeNum) {		//注意用或
		AdjMatrixDirNet<int, int> net;
		for (int i = 0; i < num; i++) {
			elems[i] = i;
		}
		net.setGraph(elems, num);

		for (int i = 0; i < edgeNum; i++) {
			cin >> temp1 >> temp2;
			net.insertEdge(temp1 - 1, temp2 - 1, 1);		//注意题意
		}

		net.topologicalSort();

	}
	return 0;
}
#include <iostream>
#include <stdexcept>							//out_of_range需要
#include <iomanip>							//display函数需要
#include "assert.h"

#define INFINITY 1000						//自己连自己的和无连接的都为INFINITY
#ifndef INVISITED_DEFINE_INCLUDE
#define INVISITED_DEFINE_INCLUDE
#define UNVISITED false
#define VISITED	true
#endif
int low[1000] = { 0 };
int visited[1000] = { 0 };
int countt = 0;
int order[1000] = { 0 };
int index = 0;
//#define REMIND
//#define DEBUG

#ifndef NODE_H_INCLUDE
#define NODE_H_INCLUDE
#include <iostream>
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

#ifndef LINKQUEUE_H_INCLUDE
#define LINKQUEUE_H_INCLUDE


//#define REMIND
//#define DEBUG

template <class ElemType>
class LinkQueue {
	/***********************************公共接口声明*******************************/
public:
	//基本成员函数
	LinkQueue();

	LinkQueue(const LinkQueue<ElemType> & copy);

	virtual ~LinkQueue();
	//特征函数
	//得
	int getLength() const;

	bool getFrontElem(ElemType & elem) const;
	//判
	bool isEmpty() const;

	//插
	void inQueue(const ElemType & elem);

	//改
	//无

	//删
	bool outQueue(ElemType & elem);

	void clean();
	//特殊函数

	void display() const;

	//重载函数

	LinkQueue<ElemType> & operator=(const LinkQueue<ElemType> & copy);
	/*=================================公共接口声明完毕============================*/
	/***********************************保护接口声明*******************************/
private:
	Node<ElemType> * head, *rear;

	/*=================================保护接口声明完毕============================*/
};

/***********************************公共接口实现*******************************/
template <class ElemType>
LinkQueue<ElemType>::LinkQueue() {
	head = rear = new Node<ElemType>;
}
//函数功能: 赋值构造函数
template <class ElemType>
LinkQueue<ElemType>::LinkQueue(const LinkQueue<ElemType> & copy) {
	head = rear = new Node<ElemType>;

	for (Node<ElemType> * tempNode = copy.head->next; tempNode != NULL; tempNode = tempNode->next) {
		this->inQueue(tempNode->data);
	}

}
//函数功能: 析构函数
template <class ElemType>
LinkQueue<ElemType>::~LinkQueue() {
	this->clean();
	delete head;

	//因为clean()后head 和 rear 指向的是同一块空间,所以释放head之后释放rear就访问出错
	//delete rear;							//错误的语句
}
//函数名称: int getLength() const;
//函数功能: 队列为空则返回长度0，否则遍历队列得长度返回
//注意事项: 因为每求一次长度便会遍历指针,所以如果需要多次用到长度得话会增加时间复杂度
template <class ElemType>
int LinkQueue<ElemType>::getLength() const {
	int length = 0;

	if (this->isEmpty()) {
		return length;
	}
	else {
		for (Node<ElemType> * tempNode = this->head->next; tempNode != NULL; tempNode = tempNode->next) {
			length++;
		}
		return length;
	}
}
//函数名称: bool getFrontElem(ElemType & elem) const
//函数功能: 队列为空返回假，否则取队头元素利用引用调用带回
//其子函数: bool isEmpty() const
template <class ElemType>
bool LinkQueue<ElemType>::getFrontElem(ElemType & elem) const {
	if (this->isEmpty()) {
		return false;
	}
	else {
		elem = head->next->data;
		return true;
	}
}
//函数名称: bool isEmpty() const
//函数功能: 若队头等于队尾返回真，否则返回假
template <class ElemType>
bool LinkQueue<ElemType>::isEmpty() const {
	if (head == rear) {
		return true;
	}
	else {
		return false;
	}
}
//函数名称: void inQueue(const ElemType & elem)
//函数功能：将elem入队，并不存在失败问题，因为链表不会满
template <class ElemType>
void LinkQueue<ElemType>::inQueue(const ElemType & elem) {
	Node<ElemType> * tempNode = new Node<ElemType>(elem);
	rear->next = tempNode;
	rear = tempNode;
}
//函数名称: bool outQueue(ElemType & elem) 
//函数功能: 队为空返回假，否则将队头出队由引用调用传出返回真，并且检测若出队后无元素
//			的话将rear == front；
//其子函数: bool isEmpty() const;
template <class ElemType>
bool LinkQueue<ElemType>::outQueue(ElemType & elem) {
	if (this->isEmpty()) {
#ifdef REMIND
		std::cout << "队列为空，不能出队！" << std::endl;
#endif
		return false;
	}
	else {
		Node<ElemType> * tempNode;

		tempNode = head->next;
		elem = tempNode->data;
		head->next = tempNode->next;

		if (head->next == NULL) {			//此时rear指向的空间已被销毁
			rear = head;
		}

		delete tempNode;					//应该先将rear 指向 head后再释放rear和tempNode所指向的空间
		return true;
	}
}
//函数名称: void clean()
//函数功能：将队列清空
//其子函数: bool outQueue(ElemType & elem)
template <class ElemType>
void LinkQueue<ElemType>::clean() {
	ElemType tempElem;

	while (this->getLength() > 0) {
		this->outQueue(tempElem);
	}
}
//函数名称: void display() const
//函数功能: 输出队列相关信息
template <class ElemType>
void LinkQueue<ElemType>::display() const {
	if (this->isEmpty()) {
		std::cout << "队列为空" << std::endl;
	}
	else {
		std::cout << "队列长度为：" << this->getLength() << std::endl;
		std::cout << "队头至队尾元素分别为：" << std::endl;
		for (Node<ElemType> * tempNode = head->next; tempNode != NULL; tempNode = tempNode->next) {
			std::cout << tempNode->data << std::endl;
		}
	}
}
//函数名称: LinkQueue<ElemType> & operator=(const LinkQueue<ElemType> & copy)
//函数功能: 重载运算符=
//其子函数: void clean()
template <class ElemType>
LinkQueue<ElemType> & LinkQueue<ElemType>::operator=(const LinkQueue<ElemType> & copy) {
	this->clean();

	for (Node<ElemType> * tempNode = copy.head->next; tempNode != NULL; tempNode = tempNode->next) {
		this->inQueue(tempNode->data);
	}

	return *this;
}
#endif // !LINKQUEUE_H_INCLUDE

template <class ElemType>
class AdjMatrixUndirGraph {
public:
	AdjMatrixUndirGraph();
	AdjMatrixUndirGraph(ElemType * vertex, int vexNum);
	~AdjMatrixUndirGraph();
	//特征函数
	//得
	int getVertexCount();					//得到顶点数目

	int getEdgeCount();						//得到边的数目

	int getVertex(ElemType & elem);			//得到元素在原图中得位置

	ElemType getVertexElem(int vertex);		//得到顶点元素值

	bool getVisited(int vertex);			//得到结点访问信息

	int getFirstAdjVertex(int vertex);		//得到vertex的第一个邻接点

	int getNextAdjVertex(int vertex1, int vertex2);			//得到vertex1相对于vertex2的第一个临界点
															//判
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

	void FindArticul();

	void DFSArticul(int vertext);
protected:
	int m_vertexSize;						//顶点个数
	int m_edgeSize;							//边数
	int **m_matrix;						//邻接矩阵
	mutable bool * m_visited;				//是否访问过标志位
	ElemType * m_elems;

	void destroyGraphHelp();

	void DFSHelp(int vertex, void(*visit)(ElemType &));
	void BFSHelp(int vertex, void(*visit)(ElemType &));
};
template <class ElemType>
void AdjMatrixUndirGraph<ElemType>::destroyGraphHelp() {
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
template <class ElemType>
void AdjMatrixUndirGraph<ElemType>::DFSHelp(int vertex, void(*visit)(ElemType &)) {
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
template <class ElemType>
void AdjMatrixUndirGraph<ElemType>::BFSHelp(int vertex, void(*visit)(ElemType &)) {
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
AdjMatrixUndirGraph<ElemType>::AdjMatrixUndirGraph() {
	this->m_vertexSize = 0;
	this->m_edgeSize = 0;
	this->m_elems = NULL;
	this->m_visited = NULL;
	this->m_matrix = NULL;
}
template <class ElemType>
AdjMatrixUndirGraph<ElemType>::AdjMatrixUndirGraph(ElemType * vertex, int vexNum) {
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
template <class ElemType>
AdjMatrixUndirGraph<ElemType>::~AdjMatrixUndirGraph() {
#ifdef DEBUG
	std::cout << "FUNC:" << __func__ << ",LINE:" << __LINE__ << std::endl;
#endif // DEBUG
	destroyGraphHelp();
}
/*===================================基本成员函数实现完毕============================*/
/************************************特征成员函数实现********************************/
//函数名称: int getVertexCount()
//函数功能: 返回顶点个数
template <class ElemType>
int AdjMatrixUndirGraph<ElemType>::getVertexCount() {
#ifdef DEBUG
	std::cout << "FUNC:" << __func__ << ",LINE:" << __LINE__ << std::endl;
#endif // DEBUG
	return m_vertexSize;
}
//函数名称: int getEdgeCount()
//函数功能: 返回边数
template <class ElemType>
int AdjMatrixUndirGraph<ElemType>::getEdgeCount() {
#ifdef DEBUG
	std::cout << "FUNC:" << __func__ << ",LINE:" << __LINE__ << std::endl;
#endif // DEBUG
	return m_edgeSize;
}
//函数名称: int getVertex(ElemType & elem)
//函数功能: 返回元素的顶点位置,若无,则返回-1;
template <class ElemType>
int AdjMatrixUndirGraph<ElemType>::getVertex(ElemType & elem) {
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
template <class ElemType>
ElemType AdjMatrixUndirGraph<ElemType>::getVertexElem(int vertex) {
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
template <class ElemType>
bool AdjMatrixUndirGraph<ElemType>::getVisited(int vertex) {
#ifdef DEBUG
	std::cout << "FUNC:" << __func__ << ",LINE:" << __LINE__ << std::endl;
#endif // DEBUG
	if (vertex < 0 || vertex >= this->m_vertexSize) {
		throw std::out_of_range("vertex参数范围不合法!");
	}
	return m_visited[vertex];
}
//函数名称: int getFirstAdjVertex(int vertex)
//函数功能:	返回vertex的第一个邻接点
template <class ElemType>
int AdjMatrixUndirGraph<ElemType>::getFirstAdjVertex(int vertex) {
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
template <class ElemType>
int AdjMatrixUndirGraph<ElemType>::getNextAdjVertex(int vertex1, int vertex2) {
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
//函数名称: bool insertEdge(int vertex1, int vertex2) 
//函数功能: 在vertex1与vertex2之间插入边
template <class ElemType>
bool AdjMatrixUndirGraph<ElemType>::insertEdge(int vertex1, int vertex2) {
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
		this->m_matrix[vertex1][vertex2] = 1;
		this->m_matrix[vertex2][vertex1] = 1;
		m_edgeSize++;
		return true;
	}
	else {
#ifdef REMIND
		std::cout << "两顶点已经有边,不能设置边了!" << std::endl;
#endif // REMIND
		return false;						//这个返回false我觉得返回的没有意义
	}
}
//函数名称: void setGraph(ElemType * vertex, int vexNum)
//函数功能: 重新设置图的顶点元素和个数,将边置为0
template <class ElemType>
void AdjMatrixUndirGraph<ElemType>::setGraph(ElemType * vertex, int vexNum) {
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
template <class ElemType>
bool AdjMatrixUndirGraph<ElemType>::setElem(int vertex, ElemType elem) {
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
template <class ElemType>
bool AdjMatrixUndirGraph<ElemType>::setVisited(int vertex) {
#ifdef DEBUG
	std::cout << "FUNC:" << __func__ << ",LINE:" << __LINE__ << std::endl;
#endif // DEBUG
	if (vertex < 0 || vertex >= m_vertexSize) {
		throw std::out_of_range("vertex参数不合法!");
	}

	if (m_visited[vertex] == VISITED) {
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
template <class ElemType>
bool AdjMatrixUndirGraph<ElemType>::deleteEdge(int vertex1, int vertex2) {
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
		m_matrix[vertex2][vertex1] = INFINITY;
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
template <class ElemType>
void AdjMatrixUndirGraph<ElemType>::DFSTraverse(int vertex, void(*visit)(ElemType &)) {
#ifdef DEBUG
	std::cout << "FUNC:" << __func__ << ",LINE:" << __LINE__ << std::endl;
#endif // DEBUG
	for (int i = vertex; i < m_vertexSize; i++) {
		DFSHelp(i, visit);
	}
}
template <class ElemType>
void AdjMatrixUndirGraph<ElemType>::BFSTraverse(int vertex, void(*visit)(ElemType &)) {
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
template <class ElemType>
void AdjMatrixUndirGraph<ElemType>::display() {
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
template<class ElemType>
void AdjMatrixUndirGraph<ElemType>::FindArticul()
{
	countt = 1;
	visited[0] = 1;

	for (int i = 1; i < m_vertexSize; i++) {
		visited[i] = 0;
	}
	int v = this->getFirstAdjVertex(0);
	DFSArticul(v);

	if (countt < this->m_vertexSize) {
		order[index++] = 0;
		for (v = this->getFirstAdjVertex(0); v != -1; v = this->getNextAdjVertex(0, v)) {
			if (visited[v] == 0) {
				DFSArticul(v);
			}
		}
	}
	std::cout << index << std::endl;
	int temp;
	for (int i = 0; i < index - 1; i++) {
		for (int j = 0; j < index - 1 - i; j++) {
			if (order[j] > order[j + 1]) {
				temp = order[j];
				order[j] = order[j + 1];
				order[j + 1] = temp;
			}
		}
	}
	for (int i = 0; i < index; i++) {
		std::cout << order[i] << " ";
	}
}
template<class ElemType>
void AdjMatrixUndirGraph<ElemType>::DFSArticul(int vertex) {
	int min = ++countt;
	visited[vertex] = min;

	int vexTemp;
	for (vexTemp = this->getFirstAdjVertex(vertex); vexTemp != -1; vexTemp = this->getNextAdjVertex(vertex, vexTemp)) {
		if (visited[vexTemp] == 0) {
			DFSArticul(vexTemp);
			if (low[vexTemp] < min) min = low[vexTemp];
			if (low[vexTemp] >= visited[vertex]) order[index++] = vertex;
		}
		else if (visited[vexTemp] < min) min = visited[vexTemp];
	}

	low[vertex] = min;
}

void write(int &);
using namespace std;
int main() {
	AdjMatrixUndirGraph<int> graph;
	int length, temp;
	int vertex[1000];
	cin >> length;
	for (int i = 0; i < length; i++) {
		vertex[i] = i;
	}
	graph.setGraph(vertex, length);
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < length; j++) {
			cin >> temp;
			if (temp != 0) {
				graph.insertEdge(i, j);
			}
		}
	}

	graph.BFSTraverse(0, write);
	cout << endl;
	
}

void write(int & elem) {
	cout << elem << " ";
}
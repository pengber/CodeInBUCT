/*链表的方法中,只要注意"链子"在哪里,链子P永远指向哪个位置就很好理解了,"链子"经常指向
 *(1)第一个节点(2)最后一个节点(3)后继
 *方法的通用模板为
 *函数名称(){
	第一条:语句先定义链子,并将链子初始化
	第二条语句:然后如果复杂方法比如需要知道位置的话再定义一个指向链子位置的变量count
	while(循环条件的核心是判断链子是否满足某个条件或者是count满足什么条件){
	循环体中最重要的是对链子进行操作完后再将下一条应该指向的结点再赋给链子,好让链子运
	动起来
	}
 }*/
#include<iostream>
#include"assert.h"
#include"node.h"
/*LinkList类模板*/
template <class ElemType>
class LinkList {
private:
	Node<ElemType> * head;
	int length;
public:
	LinkList();
	LinkList(ElemType v[], int n);
	~LinkList();							//destructor
	int getLength() const;					//get the length of linked list 
	bool isEmpty() const;					//判断链表是否为空
	void clear();							//清空链表
/*以下函数都是线性表不需要方法就可以做到的,但是链表得定义方法才能做到*/
	int locateElem(const ElemType & e)const;		//定位指定元素
	bool getElem(int n,ElemType & e);		//求指定位置元素
	bool setElem(int n, const ElemType &e);	//修改指定位置的元素
/*以下函数是线性表实现起来不方便的,但是链表实现方便的*/
	bool deleteElem(int n);					//删除指定位置元素
	bool deleteElemByVal(const ElemType & e);//删除指定元素
	bool insertElem(int n,const ElemType &e);//在任意位置插入指定元素
	bool insertElemByVal(const ElemType & e);//按值的大小插入指定元素
	bool insertElemBehindAll(const ElemType & e);//在表尾插入指定元素
	bool insertElemBeforeALL(const ElemType & e);//在表头插入指定元素
	void priLinkList() const;
};
//默认构造函数
template <class ElemType>
LinkList<ElemType>::LinkList() {
	head = new Node<ElemType>;
	assert(head);
	length = 0;
}
//根据数组内容构造链表
template <class ElemType>
LinkList<ElemType>::LinkList(ElemType v[],int n) {
	Node<ElemType> *p;
	p = head = new Node<ElemType>;
	for (int i = 0; i < n; i++) {
		p->next = new Node<ElemType>(v[i],NULL);
		assert(p);							//保持程序健壮性
		p = p->next;						//链子,链接后指向新结点,也就是最后一个结点
	}
	length = n;
}
//析构函数
template <class ElemType>
LinkList<ElemType>::~LinkList() {
	clear();
	delete head;
}
/*获取链表长度*/
template <class ElemType>
int LinkList<ElemType>::getLength() const{
	return length;
}
//判断线性表是否为空
template <class ElemType>
bool LinkList<ElemType>::isEmpty() const {
	return length == 0;
}
//清空单链表
template <class ElemType>
void LinkList<ElemType>::clear() {
	Node<ElemType> *p;
	p = head->next;							//链子永远指向第一个结点
	while (p != NULL) {
		head->next = p->next;				//链接第一个结点变成链接原先第二个结点
		delete p;							//删除原先第一个结点
		p = head->next;						//将p重新指向第一个结点;
	}
	length = 0;
}
//元素定位,返回这个元素所处的第一个位置,如果没有,则返回0;
template <class ElemType>
int LinkList<ElemType>::locateElem(const ElemType & e)const{
	Node<ElemType> *p;
	p = head->next;							//p表示所需元素的结点
	int count = 1;							//count表示结点的位置
	while (p != NULL && p->data != e) {
		count++;
		p = p->next;						//count位置都++了,链子也要向后链接一下
	}
	return (p != NULL) ? count : 0;			//结点为空则无此元素
}
/*取指定位置的值,若果没有该位置,则返回假,若取出,则返回真,值由引用调用得到*/
template <class ElemType>
bool LinkList<ElemType>::getElem(int n,ElemType & e) {
	Node<ElemType> *p = head->next;
	int count;
	if (n < 1 || n > length) return 0;
	for (count = 1; count < n; count++) {
		p = p->next;						//p永远指向count + 1个结点
	}
	e = p->data;
	return 1;
}
/*函数功能:修改指定位置元素的值*/
template <class ElemType>
bool LinkList<ElemType>::setElem(int n,const ElemType & e) {
	Node<ElemType> *p = head->next;
	int count;
	if (n < 1 || n > length) return 0;
	for (count = 1; count < n; count++) {
		p = p->next;
	}
	p->data = e;
	return 1;
}
/*函数功能:删除链表长度范围内指定位置元素,成功返回1,位置非法返回0*/
template <class ElemType>
bool LinkList<ElemType>::deleteElem(int n) {
	Node<ElemType> *p, *q;
	p = head;
	int count;
	if (n < 1 || n > length) return 0;
	for (count = 1; count < n; count++) {
		p = p->next;						//结束后p指向n-1个结点
	}
	q = p->next;							//q指向第n个结点
	p->next = q->next;						//将n-1与n+1链接起来
	delete q;								//应该删除q结点
	length--;								//链表长度减一
	return 1;
}
template <class ElemType>
bool LinkList<ElemType>::deleteElemByVal(const ElemType & e) {
	int tempPos = this->locateElem(e);

	while (tempPos) {
		this->deleteElem(tempPos);
		tempPos = this->locateElem(e);
	}
	return 1;
}
/*函数功能:在长度范围内的任意位置插入元素,链表长度+1,若位置非法返回0,合法成功返回1*/
template <class ElemType>
bool LinkList<ElemType>::insertElem(int n, const ElemType & e) {
	Node<ElemType> *p = head, *q;
	if (n < 1 || n > length) return 0;
	for (int count = 1; count < n; count++) {
		p = p->next;						//结束后p指向第n-1个结点
	}
	q = new Node<ElemType>(e, p->next);/*把n-1个结点原来指向的第n个结点的指针交
											  *要插入的现在的第n个结点*/
	assert(q);
	p->next = q;
	length++;
	return 1;
}
/*函数功能:按值插入*/
template <class ElemType>
bool LinkList<ElemType>::insertElemByVal(const ElemType & e) {
	int temPos;
	ElemType temp;

	temPos = 1;
	this->getElem(temPos, temp);
	while (temp < e && temPos <= length) {
		this->getElem(++temPos, temp);
	}
	temPos;
	this->insertElem(temPos, e);
	return 1;
}
/*函数功能:在表尾插入元素,不存在位置合法问题,故只要程序执行则返回1*/
template <class ElemType>
bool LinkList<ElemType>::insertElemBehindAll(const ElemType & e) {
	Node<ElemType> *p = head, *q;
	q = new Node<ElemType>(e, NULL);
	while (p->next != NULL) {
		p = p->next;
	}
	p->next = q;
	length++;
	return 1;
}
/*函数功能:在表头插入指定元素*/
template <class ElemType>
bool LinkList<ElemType>::insertElemBeforeALL(const ElemType & e) {
	Node<ElemType> * p = new Node<ElemType>(e, head->next);
	head->next = p;
	length++;
	return 1;
}
/*函数功能:输出链表的相关信息*/
template <class ElemType>
void LinkList<ElemType>::priLinkList() const{
	cout << "链表的长度为:" << length << endl;
	cout << "链表的元素为:" << endl;
	Node<ElemType> *p = head->next;
	for (int count = 1; count <= length; count++) {
		cout << "第" << count << "个元素为:" << p->data << endl;
		p = p->next;
	}
	return;
}
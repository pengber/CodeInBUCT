/************************************************************
 *Author	:Pengber
 *Version	:1.0
 *Date		:2018/10/16
**************************************************************/
/***********************************************************
 *Problem	:
 *Tips:		:
			1.数据和指针不要设置为protected,要不然就设置方法
			2.我觉得Node更适合用struct来设计,因为它本来就更符合
			结构的风格
*************************************************************/
/************************************************************
 *History	:
			1.将class Node{}修改为struct Node{};

*************************************************************/

#ifndef NODE_H_INCLUDE
#define NODE_H_INCLUDE

template <class ElemType>
struct Node {
public://struct默认都是public，而class默认为private，这里只是显示的指出都是Public。
	Node();
	Node(const ElemType & elem, Node<ElemType> * link = NULL);//默认值在声明里指出，而在定义中不用。
	virtual ~Node();//虚析构函数，如果有子类的话为了在动态联编时能准确的释放内存空间
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

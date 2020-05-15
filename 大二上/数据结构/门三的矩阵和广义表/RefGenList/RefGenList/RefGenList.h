#ifndef REFGENLIST_H_INCLUDE
#define REFGENLIST_H_INCLUDE
#include "RefGenListNode.h"
#include <iostream>
#include <string>

template <class ElemType>
class RefGenList {
protected:
	RefGenListNode<ElemType> *head;

	void createHelp(RefGenListNode<ElemType> * &);
	int getDepthHelp(RefGenListNode<ElemType> *);
public:

	RefGenList();
	~RefGenList();
	void input ();
	int  getDepth();
};
template<class ElemType>
void RefGenList<ElemType>::createHelp(RefGenListNode<ElemType>*& first)
{
	char ch = getchar();

	switch (ch)
	{
	case ')':
		return;
	case '(':
		first = new RefGenListNode<ElemType>(LIST);
		RefGenListNode<ElemType> * subHead;
		subHead = new RefGenListNode<ElemType>(HEAD);
		subHead->ref = 1;
		first->subList = subHead;
		createHelp(subHead->nextLink);
		ch = getchar();
		if (ch != ',') std::cin.putback(ch);
		createHelp(first->nextLink);
		break;
	default:
		std::cin.putback(ch);
		ElemType atomData;
		
		std::cin >> atomData;
		first = new RefGenListNode<ElemType>(ATOM);
		first->atom = atomData;
		ch = getchar();
		if (ch != ',') std::cin.putback(ch);
		createHelp(first->nextLink);
		break;
	}
}
template <class ElemType>
int RefGenList<ElemType>::getDepthHelp(RefGenListNode<ElemType> * hd) {
	if (hd == NULL) return 1;
	int subMaxDepth = 0;

	RefGenListNode<ElemType> * temp = hd->nextLink;
	for (temp; temp != NULL; temp = temp->nextLink) {
		if (temp->tag == LIST) {
			int tempDepth = getDepthHelp(temp->subList);
			subMaxDepth = subMaxDepth > tempDepth ? subMaxDepth : tempDepth;
		}
	}

	return subMaxDepth + 1;
}
template <class ElemType>
RefGenList<ElemType>::RefGenList() {
	head = new RefGenListNode<ElemType>(HEAD);
	head->ref = 1;
}
template <class ElemType>
RefGenList<ElemType>::~RefGenList() {
	delete head;
}
template<class ElemType>
inline int RefGenList<ElemType>::getDepth()
{
	return getDepthHelp(this->head);
}
template <class ElemType>
void RefGenList<ElemType>::input() {
	head = new RefGenListNode<ElemType>(HEAD);
	head->ref = 1;

	char ch = getchar();
	RefGenList<ElemType>::createHelp(head->nextLink);
}


#endif // !REFGENLIST_H_INCLUDE

#ifndef REFGENLISTNODE_H_INCLUDE
#define REFGENLISTNODE_H_INCLUDE

#ifndef REFGENLISTNODETYPE
#define REFGENLISTNODETYPE
enum RefGenListNodeType{HEAD, ATOM, LIST};
#endif // !REFGENLISTNODETYPE
#include <istream>

template <class ElemType>
struct RefGenListNode
{
	RefGenListNodeType tag;
	RefGenListNode<ElemType> * nextLink;
	union {
		int ref;
		ElemType atom;
		RefGenListNode<ElemType> * subList;
	};

	RefGenListNode(RefGenListNodeType tag = HEAD, RefGenListNode<ElemType> * nextList = NULL);
	~RefGenListNode();
};
template <class ElemType>
RefGenListNode<ElemType>::RefGenListNode(RefGenListNodeType tag, RefGenListNode<ElemType> * nextLink) {
	this->tag = tag;
	this->nextLink = nextLink;
}
template <class ElemType>
RefGenListNode<ElemType>::~RefGenListNode() {
	this->nextLink = NULL;
}
#endif // !REFGENLISTNODE_H_INCLUDE

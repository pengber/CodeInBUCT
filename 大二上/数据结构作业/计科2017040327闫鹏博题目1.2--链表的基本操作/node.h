#include<iostream>
using namespace std;

template <class ElemType>
struct Node {
	ElemType data;
	Node<ElemType> *next;

	Node();
	Node(ElemType e, Node<ElemType> * link = NULL);
};
template  <class ElemType>
Node<ElemType>::Node() {
	next = NULL;
};
template <class ElemType>
Node<ElemType>::Node(ElemType e, Node <ElemType> *link) {
	data = e;
	next = link;
};

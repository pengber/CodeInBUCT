#include <iostream>
using namespace std;

struct Node {
	int data;
	Node * last;
	Node * next;
};

class cList {
private:
	Node * head;
	int length;
public:
	cList(int num);
	void deleteCurrent(Node * current);
	int getLength();
	int deleteCircle(int n);
	void priList();
};

cList::cList(int num) {
	Node * p, *q;
	length = num;
	head = new Node;
	head->data = 1;
	p = head;
	for (int i = 2; i <= num; i++) {
		q = new Node;
		q->data = i;
		p->next = q;
		q->last = p;
		p = q;
	}
	p->next = head;
	head->last = p;
}

void cList::deleteCurrent(Node * current) {
	current->last->next = current->next;
	current->next->last = current->last;
	length--;
}

int cList::getLength() {
	return length;
}

int  cList::deleteCircle(int n) {
	Node * current = head;
	int i = 1;
	while (length != 1) {
		if (i == n) {
			this->deleteCurrent(current);
			i = 0;
		}
		current = current->next;
		i++;
	}
	int who = current->data;
	return who;
}

void cList::priList() {
	Node * current = head;
	for (int i = 1; i <= length; i++) {
		cout << current->data << endl;
		current = current->next;
	}
}
int main() {
	int m, n;
	int i = 1;
	while (cin >> m >> n && n != 0 && m != 0) {
		cList L(m);
		cout << L.deleteCircle(n) << endl;
	}

}


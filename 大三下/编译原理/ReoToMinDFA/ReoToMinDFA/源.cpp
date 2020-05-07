#include <iostream>
#include <string>
#include <iterator>
#include <stack>
#include "NFA.h"
#include "Re.h"


int Node::number = 0;
int main() {
	string pNotation;						//波兰式子
	getline(cin, pNotation);

	Re* re = new Re(pNotation);
	re->setRPNotation();
	std::cout << re->getPostRe() << endl;

	NFA* nfa = re->getNFA();

	nfa->setNFAForm();
	nfa->printNFAForm();

	nfa->setDFAForm();
	nfa->printDFAForm();
	nfa->printDFAFormOrder();

	nfa->setMinDFAForm();
	nfa->printMinDFAForm();
	return 0;
}
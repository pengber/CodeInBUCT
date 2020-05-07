#pragma once
#include <string>
#include <stack>
#include "NFA.h"

class Re {
private:
	string re;
	string postRe;
	
	int getPriorityNum(char a);	//获得a的优先级数字
	bool getPriority(char a, char b);//利用a和b的优先级数字返回a是否优先于b，是则返回真
	bool isAlpha(char a);		//检测a是否为字符
	
public:
	Re(string r) { re = r; };
	void setRPNotation();		//设置逆波兰式
	string getRe();				//返回正则表达式
	string getPostRe();			//返回正则表达式的逆波兰式
	NFA* getNFA();				//得到NFA
};


/*-----------------------------------私有函数----------------------------*/
bool Re::isAlpha(char a) {
	if (a == 'a' || a == 'b') return true;
	else return false;
}

int Re::getPriorityNum(char a) {
	if (a == '*') return 4;
	if (a == '.') return 3;
	if (a == '|') return 2;
	if (a == '(') return 1;
}
bool Re::getPriority(char a, char b) {
	//比较 (,|,.,*的优先级
	return getPriorityNum(a) >= getPriorityNum(b);
}
/*-----------------------------------公有函数----------------------------*/

string Re::getRe() {
	return this->re;
}
void Re::setRPNotation() {
	char topChar;							//栈顶字母
	string rpNotation = "";					//逆波兰式
	string::iterator ite;
	stack<char> charStack;

	for (ite = re.begin(); ite != re.end(); ite++) {
		//如果是字母，则输出
		if (isalpha(*ite)) {
			rpNotation += *ite;
		}
		//如果是（，入栈
		else if (*ite == '(') {
			charStack.push(*ite);
		}
		//如果是），出栈，直到遇到（，对（丢弃
		else if (*ite == ')') {
			topChar = charStack.top();
			while (topChar != '(') {
				rpNotation += topChar;
				charStack.pop();
				topChar = charStack.top();
			}
			charStack.pop();				//丢弃（
		}
		//对于其他字符，如果栈空的话直接入栈，否则
		//比较栈顶元素和该字符优先级，如果栈顶优先此字符，则出栈直到不优先，然后入栈此字符，否则直接入栈此字符
		else {
			if (charStack.empty()) {
				charStack.push(*ite);
				continue;//刚开始如果是空的话直接入栈，否则判断栈顶元素
			}
			else {
				topChar = charStack.top();
			}

			if (getPriority(topChar, *ite)) {
				do {
					rpNotation += topChar;
					charStack.pop();
					if (charStack.empty()) break;
					topChar = charStack.top();
				} while (getPriority(topChar, *ite));
				charStack.push(*ite);
			}
			else {
				charStack.push(*ite);
			}

		}
	}
	while (!charStack.empty()) {
		topChar = charStack.top();
		rpNotation += topChar;
		charStack.pop();
	}
	postRe = rpNotation;
}
string Re::getPostRe() {
	return postRe;
}

NFA* Re::getNFA() {
	stack<NFA*> nfaStack;
	for (int i = 0; i < postRe.size(); i++) {
		if (isAlpha(postRe.at(i))) {
			Node *start = new Node();
			Node *end = new Node();
			Line *line = new Line(postRe.at(i), end);
			start->lines.push_back(line);
			NFA*charNFA = new NFA(start, end);
			nfaStack.push(charNFA);
		}
		else if (postRe.at(i) == '|') {
			NFA* nfa1;
			NFA* nfa2;
			nfa1 = nfaStack.top();
			nfaStack.pop();
			nfa2 = nfaStack.top();
			nfaStack.pop();
			
			Node* start = new Node();
			Node* end = new Node();
			Line* line1 = new Line(space, nfa1->start);
			Line* line2 = new Line(space, nfa2->start);
			Line* line3 = new Line(space, end);
			Line* line4 = new Line(space, end);

			start->lines.push_back(line1);
			start->lines.push_back(line2);
			nfa1->end->lines.push_back(line3);
			nfa2->end->lines.push_back(line3);
			
			NFA* newNFA = new NFA(start, end);
			nfaStack.push(newNFA);
		}
		else if (postRe.at(i) == '.') {
			NFA* nfa1;
			NFA* nfa2;
			nfa1 = nfaStack.top();
			nfaStack.pop();
			nfa2 = nfaStack.top();
			nfaStack.pop();

			Node* start = new Node();
			Node* end = new Node();
			Line* line1 = new Line(space, nfa2->start);
			start->lines.push_back(line1);

			Line* line2 = new Line(space, nfa1->start);
			nfa2->end->lines.push_back(line2);

			Line* line3 = new Line(space, end);
			nfa1->end->lines.push_back(line3);
			NFA* newNFA = new NFA(start, end);
			nfaStack.push(newNFA);
		}
		else if (postRe.at(i) == '*'){
			NFA* nfa1;
			nfa1 = nfaStack.top();
			nfaStack.pop();

			Node* start = new Node();
			Node* end = new Node();
			
			Line* line1 = new Line(space, nfa1->start);
			start->lines.push_back(line1);

			Line* line2 = new Line(space, end);
			start->lines.push_back(line2);

			Line* line3 = new Line(space, nfa1->start);
			nfa1->end->lines.push_back(line3);

			Line* line4 = new Line(space, end);
			nfa1->end->lines.push_back(line4);

			NFA* newNFA = new NFA(start, end);
			nfaStack.push(newNFA);
		}
	}

	NFA* nfa = nfaStack.top();
	nfa->setNFAstring(re);
	return nfa;
}


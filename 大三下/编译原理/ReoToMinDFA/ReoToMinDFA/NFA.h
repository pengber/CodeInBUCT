#pragma once
#include <string>
#include <vector>
#include <iomanip>	//控制NFA和DFA的输出格式
#include <set>
#include <queue>	//DFAForm的构造做辅助
#include <map>		//集合相等判断的辅助结构
const char space = '#';
const int NFAwidth = 5;	//控制NFA的宽度，NFA显示为图的矩阵形式
const int DFAwidth = 10;//控制DFAForm的宽度
using namespace std;

class Pair {
	
public:
	int a;
	int b;
	Pair(int a, int b) {
		this->a = a;
		this->b = b;
	}
	bool operator ==(const Pair& other) const{
		return this->a == other.a && this->b == other.b;
	}
};

class Line;
class Node {
public:
	static int number;
	int num;
	vector<Line*> lines;
	Node() {
		num = number++;
	}
};
class Line {
public:
	char transform;
	Node * next;
	Line(char t, Node*n) {
		transform = t;
		next = n;
	}
};

class NFA {
private:
	vector<int> isVisited;				//用于遍历有环图
	set<int> getJSet(set<int>& I, char a);//得到用来求Closure的J集合
	set<int> getClosure(set<int>& J);	//返回集合J的Closure
	set<char> getTransformSet(string p);//返回波兰式中的字符
	void setNFAFormHelp(Node* n, vector<vector<char>>& form);//用于递归的设置NFAForm
public:
	Node *start;
	Node *end;
	string pNotaion;
	vector<vector<char>> NFAForm;
	vector<vector<set<int>>> DFAForm;//集合形式的DFA
	vector<vector<int>> DFAFormOrder;//重新排序的DFA，用于求MinDFA
	vector<vector<int>> MinDFAForm;//MinDFA
	set<int> MinDFAEndNum;
	NFA() {
		start = NULL;
		end = NULL;
		pNotaion = "";
	}
	NFA(Node*s, Node* e) {
		start = s;
		end = e;
		isVisited.insert(isVisited.begin(), e->num + 1, 0);
	}
	void setNFAstring(string p);//在Re类的getDFA()函数中，设置NFA的原始正则表达式的波兰式
	void setNFAForm();			//
	void printNFAForm();
	void setDFAForm();
	void printDFAForm();
	void printDFAFormOrder();
	void setMinDFAForm();
	void printMinDFAForm();
};
/*******************************************私有方法*****************************/
void NFA::setNFAFormHelp(Node* n, vector<vector<char>>& form) {
	if (isVisited[n->num]) {
		return;
	}
	else {
		isVisited[n->num] = 1;
		for (int i = 0; i < n->lines.size(); i++) {
			if (n->lines[i]->next->lines.size() == 0) {//先避免后一个节点是尾节点而造成vector访问越界
				int x = n->num;
				int y = n->lines[i]->next->num;
				form[x][y] = n->lines[i]->transform;
				continue;
			}
			else {
				int x = n->num;
				int y = n->lines[i]->next->num;
				form[x][y] = n->lines[i]->transform;
				setNFAFormHelp(n->lines[i]->next, form);
			}
		}
	}
}
set<int> NFA::getJSet(set<int>& I, char a) {
	set<int> JSet;
	for (auto iter = I.begin(); iter != I.end(); iter++) {
		for (int j = 0; j <= end->num; j++) {
			if (NFAForm[*iter][j] == a) {
				JSet.insert(j);
				set<int> temp;
				temp.insert(j);
				set<int> result = getJSet(temp, a);

				set_union(result.begin(), result.end(), JSet.begin(), JSet.end(), inserter(JSet, JSet.begin()));		
			}
		}
	}
	return JSet;
}
set<int> NFA::getClosure(set<int>& I) {
	set<int> result;
	set<int> JSet = getJSet(I, space);
	set_union(I.begin(), I.end(),JSet.begin(), JSet.end(), inserter(result, result.begin()));
	return result;
}

set<char> NFA:: getTransformSet(string p) {
	set<char> transformSet;
	for (int i = 0; i < p.size(); i++) {
		if (isalpha(p.at(i))) {
			transformSet.insert(p.at(i));
		}
	}
	return transformSet;
}

/*******************************************公有方法*****************************/
void NFA::setNFAstring(string p) {
	pNotaion = p;
}
void NFA::setNFAForm() {
	int length = end->num;
	vector<vector<char>> form(length+1,vector<char>(length+1));
	
	setNFAFormHelp(start, form);
	this->NFAForm = form;
}
void NFA::printNFAForm() {
	int length = end->num;
	cout << "start status:" << start->num << ",end status:" << end->num << endl;
	cout << setw(NFAwidth) << "NFA" << endl;
	for (int i = 0; i <= length; i++) {
		cout << setw(NFAwidth) << i;
	}
	cout << endl;
	for (int i = 0; i <= length; i++) {
		cout << setw(NFAwidth) << i;
		for (int j = 0; j <= length; j++) {
			cout << setw(NFAwidth) << this->NFAForm[i][j];
		}
		cout << endl;
	}
}

void NFA::setDFAForm() {
	
	queue<set<int>> firstCol;			//第一列，用队列进行计算，由首行首列得出首行全部元素，在第一列中前面的没有出现的则入队，并且入第一列的vector，重复出现的不入队
	set<int> startNum = { start->num };
	set<int> init = getClosure(startNum);
	vector<set<int>> firstColVector;	//由于queue不能遍历并且DFAForm是二维vector遍历太麻烦，所以用这个来存储之前得到的firstCol
	firstCol.push(init);
	firstColVector.push_back(init);
	set<char> transformSet = getTransformSet(this->pNotaion);//字符的集合，不包括空转换符

	while (!firstCol.empty()) {
		set<int> newRowFirst = firstCol.front();
		firstCol.pop();
		vector < set<int>> newRow;
		newRow.push_back(newRowFirst);

		for (auto iter = transformSet.begin(); iter != transformSet.end(); iter++) {
			set<int> Jset = getJSet(newRowFirst, *iter);
			set<int> Ichar = getClosure(Jset);
			int flag = 0;
			if (Ichar.size() == 0) {//如果是空集的话，则不入队列
				flag = 1;
			}
			else {
				for (auto iIter = firstColVector.begin(); iIter != firstColVector.end(); iIter++){
					
					if ((*iIter) == Ichar) {//如果以前得到过的也不入队列（flag控制是否入队列），但是集合相等不能使用==
						flag = 1;
						break;
					}
				}
			}
			if (!flag) {
				firstCol.push(Ichar);
				firstColVector.push_back(Ichar);
			}
			newRow.push_back(Ichar);
		}
		DFAForm.push_back(newRow);
	}

	//初始化DFA序号表格，默认值为-1，也就是不跳转
	DFAFormOrder.resize(DFAForm.size());
	for (int i = 0; i < DFAFormOrder.size(); i++) {
		DFAFormOrder[i].resize(DFAForm[0].size(),-1);
	}
	
	//对DFAset进行编号
	for (int i = 0; i < DFAFormOrder.size(); i++) {//以firstCol为行
		for (int j = 0; j < DFAFormOrder[0].size(); j++) {//以字符集为列
			for (auto iIter = firstColVector.begin(); iIter != firstColVector.end(); iIter++) {
				if ((*iIter) == DFAForm[i][j]) {//如果以前得到过的也不入队列（flag控制是否入队列）
					DFAFormOrder[i][j] = iIter- firstColVector.begin();
				}
			}
		}
	}
}

void NFA::printDFAForm() {
	cout << endl;
	cout << "DFA(set):" << endl;
	cout << setw(DFAwidth) << "";
	set<char> transformSet = getTransformSet(this->pNotaion);
	for (auto iter = transformSet.begin(); iter != transformSet.end(); iter++) {
		cout << setw(DFAwidth) << *iter;
	}
	cout << endl;

	for (auto iIter = DFAForm.begin(); iIter != DFAForm.end(); iIter++) {
		for (auto jIter = (*iIter).begin(); jIter != (*iIter).end(); jIter++) {
			string temp = "";
			temp +="{";
			for (auto setIter = (*jIter).begin(); setIter != (*jIter).end(); setIter++) {
				if (setIter == (*jIter).begin()) {
					temp+= to_string(*setIter);
				}
				else {
					temp += ",";
					temp += to_string(*setIter);
				}
			}
			temp +="}";
			cout << setw(DFAwidth) << temp;
		}
		cout << endl;
	}
	
}

void NFA::printDFAFormOrder() {
	cout << endl;
	cout << "DFA(order):" << endl;
	cout << setw(DFAwidth) << "";
	set<char> transformSet = getTransformSet(this->pNotaion);
	for (auto iter = transformSet.begin(); iter != transformSet.end(); iter++) {
		cout << setw(DFAwidth) << *iter;
	}
	cout << endl;

	for (int i = 0; i < DFAFormOrder.size(); i++) {
		for (int j = 0; j < DFAFormOrder[0].size(); j++) {
			cout << setw(DFAwidth) << DFAFormOrder[i][j];
		}
		cout << endl;
	}
}

 void NFA::setMinDFAForm() {
	 vector<vector<int>> MinDFAFormOrder = DFAFormOrder;//用于得到MinDFAForm的中间变量MinDFAFormOrder
	 vector<Pair> after;
	 int j;
	 int row = MinDFAFormOrder.size();
	 
	 for (j = 3; ; j++) {
		 if (j == 3) {
			 for (int i = 0; i<row;i++) {
				int order = DFAForm[i][0].find(end->num) == DFAForm[i][0].end() ? 0 : 1;//如果某行的第一列集合中找到了最终状态，则将其编号为0，否则编号为1
				MinDFAFormOrder[i].push_back(order);
			 }
		 }
		 else if (j % 3 == 0) {
			 after.clear();
			 for (int i = 0; i<row;i++) {
				 Pair temp(MinDFAFormOrder[i][j - 2], MinDFAFormOrder[i][j - 1]);
				 auto iter = find(after.begin(), after.end(), temp);
				 if ( iter == after.end()) {
					 after.push_back(temp);
					 MinDFAFormOrder[i].push_back(after.size() - 1);
				 }
				 else {
					 MinDFAFormOrder[i].push_back(iter - after.begin());
				 }
			 }
			 
			 int flag = 1;
			 for (int i = 0; i<row;i++) {
				 if (MinDFAFormOrder[i][j] != MinDFAFormOrder[i][j - 3]) flag = 0;
			 }
			 if (flag) break;				//如果连续两次列号相等，则退出循环
		 }
		 else {
			 for (int i = 0; i<row;i++) {
				 if (MinDFAFormOrder[i][(j-1)%3==0?1:2] == -1 ) {
					 MinDFAFormOrder[i].push_back(-1);
					 continue;
				 }
				 else {
					 MinDFAFormOrder[i].push_back(MinDFAFormOrder[MinDFAFormOrder[i][(j - 1) % 3 == 0 ? 1 : 2]][(j / 3) * 3]);
				 }
			}
		 }
	 }
	 
	 MinDFAForm = DFAFormOrder;
	 int lastCol = MinDFAFormOrder[0].size() - 1;
	 for (int i = 0; i<row;i++) {
		 MinDFAForm[i][0] = MinDFAFormOrder[i][lastCol];

		 if (MinDFAFormOrder[i][1] == -1 || MinDFAFormOrder[i][2] == -1) {
			 MinDFAForm[i][1] = -1;

		 }
		 else if (MinDFAFormOrder[i][2] == -1) {
			 MinDFAForm[i][2] = -1;
		 }
		 else {
			 MinDFAForm[i][1] = MinDFAFormOrder[MinDFAFormOrder[i][1]][lastCol];
			 MinDFAForm[i][2] = MinDFAFormOrder[MinDFAFormOrder[i][2]][lastCol];
		 }
	
		
	 }

	 set<vector<int> >temp(MinDFAForm.begin(), MinDFAForm.end());
	 MinDFAForm.assign(temp.begin(), temp.end());

	 cout << endl;
	 cout << "The process of geting MinDFA by DFA:" << endl;
	 cout << setw(DFAwidth) << "";
	 set<char> transformSet = getTransformSet(this->pNotaion);
	 for (auto iter = transformSet.begin(); iter != transformSet.end(); iter++) {
		 cout << setw(DFAwidth) << *iter;
	 }
	 cout << endl;

	 for (int i = 0; i < MinDFAFormOrder.size(); i++) {
		 int endNum = DFAForm[i][0].find(end->num) == DFAForm[i][0].end() ? -1 : MinDFAFormOrder[i][lastCol];//如果某行的第一列集合中找到了最终状态，则将其编号为0，否则编号为1
		 if (endNum > -1) {
			 MinDFAEndNum.insert(endNum);
		 }
		 for (int j = 0; j < MinDFAFormOrder[0].size(); j++) {
			 cout << setw(DFAwidth) << MinDFAFormOrder[i][j];
		 }
		 cout << endl;
	 }
	 
}
void NFA::printMinDFAForm() {
	//输出MinDFA的结束状态集合
	cout << endl;
	cout << "MinDFA:";
	cout << "end state:";
	for (auto iter = MinDFAEndNum.begin(); iter != MinDFAEndNum.end(); iter++) {
		cout << (*iter);
	}
	cout << endl;


	cout << setw(DFAwidth) << "";
	set<char> transformSet = getTransformSet(this->pNotaion);
	for (auto iter = transformSet.begin(); iter != transformSet.end(); iter++) {
		cout << setw(DFAwidth) << *iter;
	}
	cout << endl;

	for (int i = 0; i < MinDFAForm.size(); i++) {
		for (int j = 0; j < MinDFAForm[0].size(); j++) {
			cout << setw(DFAwidth) << MinDFAForm[i][j];
		}
		cout << endl;
	}
	
}
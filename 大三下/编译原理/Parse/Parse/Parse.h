#pragma once
#include <iomanip>
#include <vector>
#include <set>
#include <string>
#include <map>
#include <queue>				//DFA时用
#include <iostream>
#include <algorithm>
using namespace std;


const string space = "#";

class Parse {
protected:
	vector<vector<string>> m_grammar;
	vector<vector<string>> m_ex_grammar;
	map<string, set<string>> m_first;
	map<string, set<string>> m_follow;
	vector<string> m_terminal;
	vector<string> m_non_terminal;
	int extend_char = 0;					//扩展字符时使用
	set<string> special_string = { "->", "|" ,space};//不是终结符也不是非终结符的字符串
	int m_whether_parse = 1;					//这个文法能否正常分析，LL1得分析表如果有两项就置此为0，再parse得时候直接退出报错
	Parse(vector< vector<string>> g);
	//virtual void set_ex_grammar();
	void set_first();
	set<string> get_first(vector<string> gamma);	//求一个串的first集合，follow要用
	void set_follow();
	void set_nonTerminal_and_terminal();
public:
	void print_grammar();
	void print_ex_grammar();
	void print_terminal_and_nonTerminal();
	void print_first();
	void print_fllow();
	//virtual void set_DFA();
	//virtual void set_parse_table();


	
};

Parse::Parse(vector< vector<string>> grammar) {
	this->m_grammar = grammar;
}
void Parse::set_nonTerminal_and_terminal() {
	for (auto iIter = m_grammar.begin(); iIter != m_grammar.end(); iIter++) {
		if (find(m_non_terminal.begin(), m_non_terminal.end(), (*((*iIter).begin()))) == m_non_terminal.end()) {
			m_non_terminal.push_back(*((*iIter).begin()));
		}
			//剔除重复的

	}
	for (auto iIter = m_grammar.begin(); iIter != m_grammar.end(); iIter++) {
		for (auto jIter = (*iIter).begin(); jIter != (*iIter).end(); jIter++) {
			if (find(m_non_terminal.begin(), m_non_terminal.end(), (*jIter)) == m_non_terminal.end() && special_string.find(*jIter) == special_string.end()) {
				//如果不是非终结符和特殊字符的话，就是终结符
				if (find(m_terminal.begin(), m_terminal.end(),(*jIter)) == m_terminal.end()) //剔除重复的
				m_terminal.push_back(*jIter);
			}
		}
	}
}
void Parse::set_first() {
	//终结符的first集合就是它本身
	for (auto iIter = m_terminal.begin(); iIter != m_terminal.end(); iIter++) {
		set< string > tempSet;
		tempSet.insert(*iIter);
		this->m_first[(*iIter)] = tempSet;
	}
	this->m_first[space] = set<string> { space };//空的first也是空
	this->m_first["$"] = set<string>{ "$" };	//美元符号的first也是first，这个是为LR1求标志串做准备
	//非终结符的first集合初始化为空
	for (auto iIter = m_non_terminal.begin(); iIter != m_non_terminal.end(); iIter++) {
		set< string > tempSet;
		this->m_first[(*iIter)] = tempSet;
	}

	int if_change = 1;//任何一个非终结符是否变化的标志，初始化为1进入循环，进入循环后赋值为0，以后如果有变化则置1
	int k;								//产生式右边串的子符号的下标
	bool continue_flag;
	while (if_change) {
		if_change = 0;
		int old_num = 0;
		int new_num = 0;
		for (auto iIter = this->m_first.begin(); iIter != this->m_first.end(); iIter++) {//未遍历所有符号first前的first的Map的second（也就是真正集合）的长度总和
			old_num += (*iIter).second.size();
		}
		for (auto iIter = m_ex_grammar.begin(); iIter != m_ex_grammar.end(); iIter++) {
			k = 2;
			continue_flag = true;
			while (continue_flag && k < (*iIter).size()) {
				string A = *(*iIter).
					begin();
				string Xk = *((*iIter).begin() + k);
				if (find(m_first[Xk].begin(), m_first[Xk].end(), space) == m_first[Xk].end()) {	//如果空不在first(Xk)里面
					m_first[A].insert(m_first[Xk].begin(), m_first[Xk].end());
					continue_flag = false;
				}
				else {
					m_first[A].insert(m_first[Xk].begin(), m_first[Xk].end());//先全部插入
					m_first[A].erase(find(m_first[A].begin(), m_first[A].end(), space));//再删除空
				}

				k = k + 1;
			}
			if (continue_flag) {
					m_first[*(*iIter).begin()].insert(space);
			}
		}

		for (auto iIter = this->m_first.begin(); iIter != this->m_first.end(); iIter++) {//经过一次遍历后的长度，如果增加，则改变
			new_num += (*iIter).second.size();
		}
		if (new_num != old_num) {
			if_change = 1;
		}
	}
}
set<string> Parse::get_first(vector<string> gamma) {
	set<string> result;
	int space_num = 0;		//记录空符号个数
	for (auto iter = gamma.begin(); iter != gamma.end(); iter++) {
		if (find(m_first[*iter].begin(),m_first[*iter].end(),space) != m_first[*iter].end()) {//如果有空
			//先加此符号的first，再删除空
			result.insert(m_first[*iter].begin(), m_first[*iter].end());
			result.erase(space);
			space_num++;
		}
		else {
			result.insert(m_first[*iter].begin(), m_first[*iter].end());
			return result;
		}

		if (space_num == gamma.size()) {//表明全部都有空
			result.insert(space);
		}
	}

	return result;
}
void Parse::set_follow() {
	//非终结符的follow集合初始化为空
	for (auto iIter = m_non_terminal.begin(); iIter != m_non_terminal.end(); iIter++) {
		set< string > tempSet;
		this->m_follow[(*iIter)] = tempSet;
	}
	int if_change = 1;
	while (if_change) {
		if_change = 0;
		int old_num = 0;
		int new_num = 0;
		for (auto iIter = this->m_follow.begin(); iIter != this->m_follow.end(); iIter++) {//未遍历所有符号first前的first的Map的second（也就是真正集合）的长度总和
			old_num += (*iIter).second.size();
		}

		for (auto iIter = m_non_terminal.begin(); iIter != m_non_terminal.end(); iIter++) {
			string A = (*iIter);
			if (A == (*m_non_terminal.begin())) {
				m_follow[A].insert("$");
			}

			//pro是production的缩写，也就是遍历所有的production
			for (auto proIter = m_ex_grammar.begin(); proIter != m_ex_grammar.end(); proIter++) {
				auto positionIter = find((*proIter).begin() + 2, (*proIter).end(), A);
				vector<string>::iterator afterPositionIter;

				if (positionIter == (*proIter).end()) {//如果没有找到A的话，则continue;
					continue;
				}
				else if (positionIter == (*proIter).end() - 1) {//如果找到但是A是最后一个的话，则将这个production的左边非终结符的follow加入到A的fllow中
					m_follow[A].insert(m_follow[*(*proIter).begin()].begin(), m_follow[*(*proIter).begin()].end());//增加
				}
				else {
					vector<string> gamma;
					gamma.insert(gamma.end(), positionIter + 1, (*proIter).end());
					set<string> firstOfGamma = get_first(gamma);

					if (firstOfGamma.find(space) != firstOfGamma.end()) {
						//先加入firstOfGamma-{space}
						m_follow[A].insert(firstOfGamma.begin(), firstOfGamma.end());
						m_follow[A].erase(space);

						//再加入产生式首部的非终结符的follow
						m_follow[A].insert(m_follow[*(*proIter).begin()].begin(), m_follow[*(*proIter).begin()].end());
					}
					else {
						//如果没有空的话只加入firstOfGamma
						m_follow[A].insert(firstOfGamma.begin(), firstOfGamma.end());
					
						
					}
				}
			}
		}

		for (auto iIter = this->m_follow.begin(); iIter != this->m_follow.end(); iIter++) {//经过一次遍历后的长度，如果增加，则改变
			new_num += (*iIter).second.size();
		}
		if (new_num != old_num) {
			if_change = 1;
		}
	}
}
void Parse::print_grammar() {
	std::cout << endl;
	std::cout << "grammar is:" << endl;
	for (auto iter = m_grammar.begin(); iter != m_grammar.end(); iter++) {
		for (auto jIter = (*iter).begin(); jIter != (*iter).end(); jIter++) {
			std::cout << (*jIter) << " ";
		}
		std::cout << endl;
	}
}

void Parse::print_ex_grammar() {
	std::cout << endl;
	std::cout << "Extent grammar is:" << endl;
	for (auto iter = m_ex_grammar.begin(); iter != m_ex_grammar.end(); iter++) {
		std::cout << iter - m_ex_grammar.begin() << " ";
		for (auto jIter = (*iter).begin(); jIter != (*iter).end(); jIter++) {
			std::cout << (*jIter) << " ";
		}
		std::cout << endl;
	}


}
void Parse::print_terminal_and_nonTerminal() {
	std::cout << endl;
	std::cout << "This grammar has nonterminal as these:" << endl;
	for (auto iter = m_non_terminal.begin(); iter != m_non_terminal.end(); iter++) {
		std::cout << (*iter) << " ";
	}

	std::cout << endl;
	std::cout << "This grammar has terminial as these:" << endl;
	for (auto iter = m_terminal.begin(); iter != m_terminal.end(); iter++) {
		std::cout << (*iter) << " ";
	}
	std::cout << endl;
}
void Parse::print_first() {
	std::cout << endl;
	std::cout << "First sets list:" << endl;

	for (auto iIter = m_first.begin(); iIter != m_first.end(); iIter++) {
		if (find(m_non_terminal.begin(), m_non_terminal.end(), (*iIter).first) != m_non_terminal.end()) {//如果是非终结符的话
			std::cout << "first(";
			std::cout << (*iIter).first << ")={";
			for (auto jIter = (*iIter).second.begin(); jIter != (*iIter).second.end(); jIter++) {
				if (jIter == (*iIter).second.begin());
				else {
					std::cout << " ";
				}
				std::cout << (*jIter);
			}
			std::cout << "}";
			std::cout << endl;
		}
	}
}
void Parse::print_fllow() {
	std::cout << endl;
	std::cout << "Follow sets list:" << endl;

	for (auto iIter = m_follow.begin(); iIter != m_follow.end(); iIter++) {
		if (find(m_non_terminal.begin(), m_non_terminal.end(), (*iIter).first) != m_non_terminal.end()) {//如果是非终结符的话
			std::cout << "follow(";
			std::cout << (*iIter).first << ")={";
			for (auto jIter = (*iIter).second.begin(); jIter != (*iIter).second.end(); jIter++) {
				if (jIter == (*iIter).second.begin());
				else {
					std::cout << " ";
				}
				std::cout << (*jIter);
			}
			std::cout << "}";
			std::cout << endl;
		}
	}
}

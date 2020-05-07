#pragma once
#include "Parse.h"
#define PARSE_WIDTH 19	//定义分析栈的宽度
#define ACTION_WIDTH 10	//定义动作的宽度，输入串宽度由输出串决定
//未消除左因子
//终结符中有空，不知道是不显示它还是将空从物理中去除
class LL1 :public Parse {
private:
	vector<vector<string>> m_grammar_without_recursion;

	vector <vector<int> >m_parse_table;
	map<string, int> m_N;
	map<string, int> m_T;

	vector<vector<string>> erase_direct_left_reverse(const vector<string> &p);
	void erase_left_reverse();
	vector<vector<string>> erase_production_left_factor(vector<string> p);//消除一个产生式的左因子
	vector<string> CommonVectorString(vector<vector<string>> right_prodution);//产生式右侧串的最长公共子前缀
	void erase_left_factor();
	void set_grammar_without_recursion();	//调用消除左递归和消除左因子，得到没有m_grammar_without_recursion；
	void set_ex_grammar();					//从grammar_without_recursion设置ex_grammar,也就是分解后的文法
	void set_parse_row_and_col();			//设置分析表表头，因为分析表是二维向量，但是其行号是由非终结符和终结符加美元符号确定的，所以要存储字符与下标的对应关系，用map，
	void set_parse_table();

public:
	LL1(vector<vector<string>> grammar) :Parse(grammar) {
		this->set_nonTerminal_and_terminal();//先设置终结符和非终结符，由于消除左递归和左因子增加的终结符在他们自己的函数里面对成员变量进行修改,并且必须放在得到没有左递归和左因子操作的前面，因为他们需要用到
		this->set_grammar_without_recursion();
		this->set_ex_grammar();				//利用消除左因子和左递归的产生式们得到分离后的扩展文法
		this->set_first();					//设置first集合。
		this->set_follow();					//设置follow集合
		this->set_parse_row_and_col();
		this->set_parse_table();
	};
	
	bool parse_string(vector<string> input);
	void print_grammar_without_recursion();
	void print_parse_table();

};
vector<vector<string>> LL1::erase_direct_left_reverse(const vector<string>& p) {
	vector<int> alpha;
	vector<int> belta;						//存储非递归项下标
	vector<vector<string>> right_production;//存储产生式右侧
	vector<string> right_production_item;	//产生式右侧的项，不包含“|”
	
	for (auto iIter = p.begin() + 2; iIter != p.end(); iIter++) {
		if ((*iIter) != "|") {
			right_production_item.push_back(*iIter);
		}
		else if (right_production_item.size() != 0){
			right_production.push_back(right_production_item);
			right_production_item.clear();
		}
	}
	right_production.push_back(right_production_item);//最后一个因为end（）跳出了，所以再push_back一下

	for (auto iIter = right_production.begin(); iIter != right_production.end(); iIter++) {
		if ((*(*iIter).begin()) == (*p.begin())) {
			alpha.push_back(iIter - right_production.begin());
		}
		else {
			belta.push_back(iIter - right_production.begin());	//非左递归项的指针下标
		}
	}

	if (alpha.size() == 1 && belta.size() == 0) {	//无法消除左递归A -> Aa43
		this->m_whether_parse = 0;
		std::cout << "This production will circulate forever";
		vector<vector<string>> temp_result;
		temp_result.push_back(p);
		return temp_result;
	}
	else if (alpha.size() == 0 && belta.size() > 0) { //没有左递归项，直接返回原来的式子
		vector<vector<string>> temp_result;
		temp_result.push_back(p);
		return temp_result;
	}
	else{
		string extend_name = (*p.begin()) + to_string(extend_char++);
		this->m_non_terminal.push_back(extend_name);//对非终结符也要进行修正
		vector <string>first_production;
		

		first_production.push_back((*p.begin()));
		first_production.push_back("->");
		for (auto iIter = belta.begin(); iIter != belta.end(); iIter++) {
			if (iIter == belta.begin()) {}
			else first_production.push_back("|");

			first_production.insert(first_production.end(), (*(right_production.begin() + (*iIter))).begin(), (*(right_production.begin() + (*iIter))).end());//将βi追加到第一个新产生式的后面
			first_production.push_back(extend_name);
			
		}

		vector<string> second_production;
		second_production.push_back(extend_name);
		second_production.push_back("->");

		
		for (auto iIter = alpha.begin(); iIter != alpha.end(); iIter++) {
			if (iIter == alpha.begin()) {}
			else second_production.push_back("|");

			second_production.insert(second_production.end(), (*(right_production.begin() + (*iIter))).begin()+1, (*(right_production.begin() + (*iIter))).end());//将βi追加到第一个新产生式的后面,+1是因为第一个非终结符不插入第二列
			second_production.push_back(extend_name);
			
		}
		second_production.push_back("|");
		second_production.push_back(space);
		
		vector<vector<string>> temp_result;
		temp_result.push_back(first_production);
		temp_result.push_back(second_production);
		return temp_result;
	}

}
void LL1::set_grammar_without_recursion() {
	this->erase_left_reverse();			//消除一般左递归，其中调用了消除直接左递归,注意，在LL这个程序种不能不消除左递归然后求first，因为ex_grammar是由m_grammar_without_recursion得到的
	this->erase_left_factor();//然后消除左因子
}
void LL1::set_ex_grammar() {
	for (auto iIter = m_grammar_without_recursion.begin(); iIter != m_grammar_without_recursion.end(); iIter++) {
		vector<string> new_production;
		new_production.push_back(*(*iIter).begin());	//先入非终结符
		new_production.push_back("->");					//再如箭头
		for (auto jIter = (*iIter).begin() + 2; jIter != (*iIter).end(); jIter++) {
			if (*jIter != "|") {
				new_production.push_back((*jIter));
			}
			else {
				m_ex_grammar.push_back(new_production);
				new_production.clear();
				new_production.push_back(*(*iIter).begin());	//先入非终结符
				new_production.push_back("->");
			}
		}
		m_ex_grammar.push_back(new_production);			//因为end迭代器无法在循环内判断，所以入后面跟end迭代器的表达式

	}
}
void LL1::erase_left_reverse() {
	m_grammar_without_recursion = m_grammar;
	int init_num = m_non_terminal.size();
	for (int i = 0; i < init_num; i++) {
		for (int j = 0; j <= i-1; j++) {
			int the_row = 0;				//要替换的那行是迭代器序号

			//找到因为新插入行而位置变化的非终结符所对应的产生式的行数
			for (auto colIter = m_grammar_without_recursion.begin(); colIter != m_grammar_without_recursion.end(); colIter++) {
				if (*(*colIter).begin() == m_non_terminal[i]) the_row = colIter - m_grammar_without_recursion.begin();
			}
			int order = 0;					//A所出现的迭代器位置

			//
			for (auto iIter = (*(m_grammar_without_recursion.begin() + the_row)).begin(); iIter != (*(m_grammar_without_recursion.begin() + the_row)).end(); iIter++) {
				if ((*iIter != m_non_terminal[j])) continue;//如果不是第j个替换的终结符的话，则此项过
				else {
					int order = 0;
					int length = 0;
					/*
					A -> B a | A a | c
					B -> B b | A b | d
					如果B->Ba|Ab|c的话，也就是A的左侧为->或者|的话，才是递归左循环，才需要替换其中的A，
					*/
					if ((*(iIter - 1) == "->" || (*(iIter - 1) == "|"))) {

						/*找出替换的非终结符最开始的语法的行数，如果语法变化了，该非终结符消除了左递归，其他产生式种包含此非终结符的要做替换，否则不用替换，比如
						S -> a | ^ | ( T )
						T -> T , S | S
								*/
						int old_grmmar_row = 0;		//在最开始文法中的行号
						for (auto grammar_iter = m_grammar.begin(); grammar_iter != m_grammar.end(); grammar_iter++) {
							if (*(*grammar_iter).begin() == m_non_terminal[j]) {
								old_grmmar_row = grammar_iter - m_grammar.begin();
							}
						}

						int new_exgrmmar_row = 0;
						for (auto grammar_iter = m_grammar_without_recursion.begin(); grammar_iter != m_grammar_without_recursion.end(); grammar_iter++) {
							if (*(*grammar_iter).begin() == m_non_terminal[j]) {
								new_exgrmmar_row = grammar_iter - m_grammar_without_recursion.begin();
							}
						}
						if (*(m_grammar.begin() + old_grmmar_row) == *(m_grammar_without_recursion.begin() + new_exgrmmar_row)) {
							continue;
						}
						while (iIter != (*(m_grammar_without_recursion.begin() + the_row)).end() && (*iIter) != "|") {//顺序不能变，必须先判断不是结尾再读取迭代器
							length++;
							iIter++;
						}
					}
					/*
					expr -> expr addop term | term
					factor -> ( expr ) | number
					否则就虽然有expr但也不用代替,直接下一个非终结符
					*/
					else {
						continue;
					}
					vector<string> rest_string;
					rest_string.insert(rest_string.begin(), iIter - length + 1, iIter);
					vector<string> replace_string_of_Aj;
					replace_string_of_Aj.insert(replace_string_of_Aj.begin(), m_grammar_without_recursion[j].begin() + 2, m_grammar_without_recursion[j].end());
					replace_string_of_Aj.insert(replace_string_of_Aj.end(), rest_string.begin(), rest_string.end());
					for (auto iter = replace_string_of_Aj.begin(); iter != replace_string_of_Aj.end(); iter++) {
						if ((*iter) == "|") {
							iter = replace_string_of_Aj.insert(iter, rest_string.begin(), rest_string.end());//插入后必须对iter重新赋值，因为改变了容器对象，迭代器要用新的
							iter++;
						}
					}
					
					auto the_row_iter = m_grammar_without_recursion.begin() + the_row;//所要替换的非终结符在文法中的对应行的迭代器
					int iIterNum = iIter - (*(the_row_iter)).begin()-length;
					(*(the_row_iter)).erase((*(the_row_iter)).begin()+iIterNum, (*(the_row_iter)).begin() + iIterNum+length);
					iIter = (*(the_row_iter)).insert((*(the_row_iter)).begin()+iIterNum, replace_string_of_Aj.begin(), replace_string_of_Aj.end());
					iIter++;

				}
			}

		}

		int target_row = 0;

		for (auto colIter = m_grammar_without_recursion.begin(); colIter != m_grammar_without_recursion.end(); colIter++) {
			if (*(*colIter).begin() == m_non_terminal[i]) target_row = colIter - m_grammar_without_recursion.begin();
		}
		vector<vector<string>> result = erase_direct_left_reverse(*(m_grammar_without_recursion.begin()+target_row));
		m_grammar_without_recursion.erase(m_grammar_without_recursion.begin() + target_row);
		m_grammar_without_recursion.insert(m_grammar_without_recursion.begin() + target_row, result.begin(), result.end());
	}
}
vector<vector<string>> LL1::erase_production_left_factor(vector<string> p) {
	vector<int> alpha;
	vector<int> belta;						//存储非递归项下标
	vector<vector<string>> right_production;//存储产生式右侧
	vector<string> right_production_item;	//产生式右侧的项，不包含“|”

	for (auto iIter = p.begin() + 2; iIter != p.end(); iIter++) {
		if ((*iIter) != "|") {
			right_production_item.push_back(*iIter);
		}
		else if (right_production_item.size() != 0) {
			right_production.push_back(right_production_item);
			right_production_item.clear();
		}
	}
	right_production.push_back(right_production_item);//最后一个因为end（）跳出了，所以再push_back一下

	sort(right_production.begin(), right_production.end());//先对产生式子项排序
	vector<string> prefix = CommonVectorString(right_production);//求出最长公共子串
	int prefix_length = prefix.size();

	for (auto iIter = right_production.begin(); iIter != right_production.end(); iIter++) {
		vector<string> tempPrefix((*iIter).begin(), (*iIter).begin() + prefix_length);
		if (prefix_length > 0 && tempPrefix == prefix) {
			alpha.push_back(iIter - right_production.begin());
		}
		else {
			belta.push_back(iIter - right_production.begin());	//非左因子项的指针下标
		}
	}

	if (alpha.size() == 0) {
		//没有左因子

		vector <vector<string>> temp_result;
		temp_result.push_back(p);
		return temp_result;
	}
	else {
		string extend_name = ((*p.begin()) + to_string(extend_char++));
		this->m_non_terminal.push_back(extend_name);//对非终结符也要进行修正
		vector<string> first_production;

		first_production.push_back(*p.begin());
		first_production.push_back("->");
		first_production.insert(first_production.end(), prefix.begin(), prefix.end());
		first_production.push_back(extend_name);
		for (auto iter = belta.begin(); iter != belta.end(); iter++) {
			if (iter != belta.begin()) first_production.push_back("|");
			first_production.insert(first_production.end(), (*(right_production.begin() + (*iter))).begin(), (*(right_production.begin() + (*iter))).end());
		}

		vector<string> second_production;
		second_production.push_back(extend_name);
		second_production.push_back("->");
		for (auto iter = alpha.begin(); iter != alpha.end(); iter++) {
			if (iter != alpha.begin()) second_production.push_back("|");
			if ((*(right_production.begin() + (*iter))).begin() + prefix_length == (*(right_production.begin() + (*iter))).end()) {
				/*当某一项只是最大前缀子串的时候，也就是例如
				varlist -> id , varlist | id的时候，要给varlist0补一个空varlist0 -> , varlist | #
				*/
				second_production.push_back(space);
			}
			else {
				second_production.insert(second_production.end(), (*(right_production.begin() + (*iter))).begin() + prefix_length, (*(right_production.begin() + (*iter))).end());
			}
		}
		vector<vector<string>> temp_result;
		temp_result.push_back(first_production);
		temp_result.push_back(second_production);
		return temp_result;
	}
}
vector<string> LL1::CommonVectorString(vector<vector<string>> right_prodution) {
	int max_length = 0;						//二维字符数组right_production的最长子前缀
	vector<string> prefix;
	for (auto iIter = right_prodution.begin(); iIter != right_prodution.end(); iIter++) {
		for (auto jIter = iIter + 1; jIter != right_prodution.end(); jIter++) {
			vector<string>::iterator firstIter;		//前面一行的迭代器
			vector<string>::iterator secondIter;	//后面对比行的迭代器
			vector<string> tempPrefix;				//存储新的前缀字符串数组
			for (firstIter = (*iIter).begin(), secondIter = (*jIter).begin(); firstIter != (*iIter).end() && secondIter != (*jIter).end(); firstIter++, secondIter++) {
				if (*firstIter == *secondIter) {
					tempPrefix.push_back(*firstIter);
				}
				else {
					break;
				}
			}
			if (max_length < tempPrefix.size()) {
				max_length = tempPrefix.size();
				prefix = tempPrefix;
			}
		}
	}
	return prefix;
}
void LL1::erase_left_factor() {
	int if_change = 1;
	while (if_change) {
		if_change = 0;
		vector<string> temp_non_terminal = m_non_terminal;
		for (auto iter = temp_non_terminal.begin(); iter != temp_non_terminal.end(); iter++) {
			int row = 0;					//这个非终结符在没有左递归文法中的行数
			for (auto grammarIter = m_grammar_without_recursion.begin(); grammarIter != m_grammar_without_recursion.end(); grammarIter++) {
				if (*iter == *(*grammarIter).begin()) {
					row = grammarIter - m_grammar_without_recursion.begin();
				}
			}
			vector<string> prodution = *(m_grammar_without_recursion.begin() +row);
			vector<vector<string>> result = erase_production_left_factor(prodution);
			if (result.size() == 2) if_change = 1;//如果返回了两个产生式，则说明改变了

			m_grammar_without_recursion.erase(m_grammar_without_recursion.begin() + row);
			m_grammar_without_recursion.insert(m_grammar_without_recursion.begin() + row, result.begin(), result.end());
		}
	}
}
void LL1::set_parse_row_and_col() {
	//m_T和m_N为parse_table的列名和行名，分别为终结符+$和非终结符的集合，存储为map<string,int>,int为列号和行号
	for (auto iter = m_non_terminal.begin(); iter != m_non_terminal.end(); iter++) {
		m_N[*iter] = iter - m_non_terminal.begin();
	}
	for (auto iter = m_terminal.begin(); iter != m_terminal.end(); iter++) {
		m_T[*iter] = iter - m_terminal.begin();
	}
	m_T["$"] = m_terminal.size();
}
void LL1::set_parse_table() {
	
	m_parse_table.resize(m_N.size(), vector<int>(m_T.size() ,-1));//初始化parse_table大小，后面用下标来访问
	for (auto nonTerIter = m_non_terminal.begin(); nonTerIter != m_non_terminal.end(); nonTerIter++) {
	 		int i = m_N[*nonTerIter];
		for (auto proIter = m_ex_grammar.begin(); proIter != m_ex_grammar.end(); proIter++) {

			if (*((*proIter).begin()) == (*nonTerIter)) {
				vector<string> production_right((*proIter).begin() + 2, (*proIter).end());
				set<string >firstSet_of_production_right = this->get_first(production_right);
				for (auto terIter = firstSet_of_production_right.begin(); terIter != firstSet_of_production_right.end(); terIter++) {
					int follow_set = 0;				//是否将产生式左侧非终结符得follow集合中的元素列下面加入产生式序号，用集合元素中有无空决定
					if (*terIter == space) {
						follow_set = 1;
					}
					else {
						if (m_parse_table[i][m_T[*terIter]] == -1) {
							m_parse_table[i][m_T[*terIter]] = proIter - m_ex_grammar.begin();
						}
						else {
							m_whether_parse = 0;//表示一个单元格里面写入了两项，不能用于分析
							int write_num = proIter - m_ex_grammar.begin();
							int num = to_string(m_parse_table[i][m_T[*terIter]]).size() + 1;
							m_parse_table[i][m_T[*terIter]] = pow(10, num)*write_num + m_parse_table[i][m_T[*terIter]];
						}
					}

					if (follow_set) {
						for (auto followItemIter = m_follow[*(proIter->begin())].begin(); followItemIter != m_follow[*(proIter->begin())].end(); followItemIter++) {
							if (m_parse_table[i][m_T[*followItemIter]] == -1) {
								m_parse_table[i][m_T[*followItemIter]] = proIter - m_ex_grammar.begin();
							}
							else {
								m_whether_parse = 0;//表示一个单元格里面写入了两项，不能用于分析
								int write_num = proIter - m_ex_grammar.begin();
								int num = to_string(m_parse_table[i][m_T[*followItemIter]]).size() + 1;
								m_parse_table[i][m_T[*followItemIter]] = pow(10, num) * write_num + m_parse_table[i][m_T[*followItemIter]];
							}
						}
					}
				}
			}
		}
	}
}

bool LL1::parse_string(vector<string> input) {
	if (m_whether_parse == 0) return false;
	
	int INPUT_WIDTH = 10;
	string output_string = "";
	vector<string> parse_stack;					//本来应该用栈结构，但是考虑到输出，所以用vector
	vector<string> input_stack = input;

	for (auto iter = input.begin(); iter != input.end(); iter++) {
		INPUT_WIDTH += (*iter).size();
	}

	parse_stack.push_back(m_ex_grammar[0][0]);	//先入开始符号
	parse_stack.push_back("$");			

	input_stack.push_back("$");					//形成输入栈

	std::cout << setw(PARSE_WIDTH) << "Parse stack";
	std::cout << setw(INPUT_WIDTH) << "Input stack";
	std::cout << setw(ACTION_WIDTH) << "Action" << std::endl;

	while (input_stack.size() != 0 || parse_stack.size() != 0) {
		
		//输出栈的内容
		output_string = "";
		for (auto iter = parse_stack.begin(); iter != parse_stack.end(); iter++) {
			output_string += (*iter);
		}
		std::cout << setw(PARSE_WIDTH) << output_string;

		output_string = "";
		for (auto iter = input_stack.begin(); iter != input_stack.end(); iter++) {
			output_string += (*iter);
		}
		std::cout << setw(INPUT_WIDTH) << output_string;

		string topParse = *parse_stack.begin();
		string topInput = *input_stack.begin();
		if (topParse == space) {
			//如果分析栈顶不是非终结符也不是终结符的话，也就是空的话，直接弹出
			parse_stack.erase(parse_stack.begin());
			std::cout << setw(ACTION_WIDTH) << "macth" << std::endl;
		}
		else if (find(m_non_terminal.begin(), m_non_terminal.end(), topParse) != m_non_terminal.end()) {//如果是非终结符的话

			if (find(m_non_terminal.begin(), m_non_terminal.end(), topInput) != m_non_terminal.end()) {
				//如果此时输入栈顶也是非终结符的话，无法分析，返回
				this->m_whether_parse = 0;
				return false;
			}
			int action_num = m_parse_table[m_N[topParse]][m_T[topInput]];
			if (0 <= action_num || action_num <= m_ex_grammar.size()) {
				//当不为-1并且其分析表填的内容<=扩展文法后的产生式的数量时，则替换
				std::cout << setw(ACTION_WIDTH) << action_num << std::endl;
				vector<string> production_right(m_ex_grammar[action_num].begin() + 2, m_ex_grammar[action_num].end());
				parse_stack.erase(parse_stack.begin());
				parse_stack.insert(parse_stack.begin(), production_right.begin(), production_right.end());
			}
			else {//否则无法分析
				this->m_whether_parse = 0;
				return false;
			}
		}
		else if (topParse == topInput) {//此时是终结符对应终结符,或者$对应$
			if (topParse == "$") {
				std::cout << setw(ACTION_WIDTH) << "accpet" << endl;
			}
			else {
				std::cout << setw(ACTION_WIDTH) << "match" << endl;
			}
			parse_stack.erase(parse_stack.begin());
			input_stack.erase(input_stack.begin());
		}
		else {								//此时是其他情况
			this->m_whether_parse = 0;
			return false;
		}
		
	}

	this->m_whether_parse = 1;
	return true;
}
void LL1::print_grammar_without_recursion() {
	std::cout << endl;
	std::cout << "Grammar without left recursion and left factor is:" << std::endl;
	for (auto iter = m_grammar_without_recursion.begin(); iter != m_grammar_without_recursion.end(); iter++) {
		for (auto jIter = (*iter).begin(); jIter != (*iter).end(); jIter++) {
			std::cout << (*jIter) << " ";
		}
		std::cout << std::endl;
	}
}

void LL1::print_parse_table() {
	std::cout << std::endl;
	std::cout << "ParseTable is:" << std::endl;
	int length = 6;//控制显示的列宽度，为终结符和非终结符的最短项的长度
	for (auto iter = m_terminal.begin(); iter != m_terminal.end(); iter++) {
		length = (*iter).size() > length ? (*iter).size() : length;
	}
	for (auto iter = m_non_terminal.begin(); iter != m_non_terminal.end(); iter++) {
		length = (*iter).size() > length ? (*iter).size() : length;
	}

	//第一行表头
	std::cout << setw(length) << "M[N,T]";
	for (auto iter = m_terminal.begin(); iter != m_terminal.end(); iter++) {
		std::cout << setw(length) << (*iter);
	}
	std::cout << setw(length) << "$" << endl;

	for (auto iIter = m_parse_table.begin(); iIter != m_parse_table.end(); iIter++) {
		int i = iIter - m_parse_table.begin();
		std::cout << setw(length) << m_non_terminal[i];
		for (auto jIter = (*iIter).begin(); jIter != (*iIter).end(); jIter++) {
			int j = jIter - (*iIter).begin();
			if (m_parse_table[i][j] != -1) {
				std::cout << setw(length) << m_parse_table[i][j];
			}
			else {
				std::cout << setw(length) << " ";
			}

		}
		std::cout << std::endl;
	}
	if (m_whether_parse == 0) {
		std::cout << "This grammar can't parse string! I used 0 to separate them in table." << endl;
	}

}

#pragma once
#include "Parse.h"
#include "DFA.h"
#define PARSE_WIDTH 20	//定义分析栈的宽度
#define ACTION_WIDTH 15	//定义动作的宽度，输入串宽度由输出串决定
enum Action { Shift = 1, Reduce, Push, Conflict, Accpet, Error };
map<int, string> Action_map = { {Shift,"S"},{Reduce,"R"},{Push,"P"},{Conflict,"C"},{Accpet,"Acc"},{Error,"E"} };

struct Parse_Action {
	Action act;
	int num;
	Parse_Action(Action a = Error, int n = -1) {
		act = a;
		num = n;
	}
};
class LR :public Parse {
protected:
	map<string, int> m_col;
	vector<vector<string>>m_grammar_of_extension;	//进行S‘->S阔光
	vector<DFA_Items> m_DFA;						//DFA
	vector<vector<Parse_Action>> m_parse_table;		

	void set_grammar_of_extension();					//进行文法拓广,并且加入新的开始符号
	void set_ex_grammar();							//
	virtual vector<vector<string>> do_extence(vector<string> start);
	virtual DFA_Items get_valid_items(DFA_Item item);//由一个DFA_Item返回它的有效项目集
	virtual void set_DFA();									//不知道在里面能不能调用虚方法
	virtual void set_parse_table() {};
	void set_parse_col();
public:
	LR(vector<vector<string>> grammar) :Parse(grammar) {
		this->set_nonTerminal_and_terminal();
		this->set_grammar_of_extension();
		this->set_ex_grammar();
		this->set_first();
		this->set_follow();
		this->set_parse_col();						//设置分析表的表头，行就不用设置了，因为其行号就对应状态
		this->print_terminal_and_nonTerminal();
		this->print_grammar_of_extension();
		this->print_ex_grammar();
		this->print_first();
		this->print_fllow();
	}
	bool parse_string(vector<string> input);
	void print_grammar_of_extension();
	void print_DFA();
	void print_parse_table();

};

void LR::set_grammar_of_extension() {
	m_grammar_of_extension = m_grammar;
	string old_start = this->m_non_terminal[0];
	string new_start = old_start + to_string(extend_char++);
	vector<string> start_production;
	start_production.push_back(new_start);
	start_production.push_back("->");
	start_production.push_back(old_start);
	m_grammar_of_extension.insert(m_grammar_of_extension.begin(), start_production);
	m_non_terminal.insert(m_non_terminal.begin(), new_start);

}
void LR::set_ex_grammar() {
	for (auto iIter = m_grammar_of_extension.begin(); iIter != m_grammar_of_extension.end(); iIter++) {
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
vector<vector<string>> LR::do_extence(vector<string> item) {
	auto iter = find(item.begin(), item.end(), POINT);
	vector<vector<string>> result;
	result.push_back(item);
	if ((iter + 1) == item.end()) {//如果点是最后一个的话，扩展就只有它自己

		return result;
	}
	string after_point = (*(iter + 1));
	//如果点不是最后一个的话， 点之后的字符串是非终结符的话，找出这个非终结符的所有产生式，并且对每一个加入点作扩展
	if (find(m_non_terminal.begin(), m_non_terminal.end(), after_point) != m_non_terminal.end()) {
		vector<int> productionOrder;
		for (auto iter = m_ex_grammar.begin(); iter != m_ex_grammar.end(); iter++) {
			if (*((*iter).begin()) == after_point) {
				productionOrder.push_back(iter - m_ex_grammar.begin());
			}
		}
		for (auto iter = productionOrder.begin(); iter != productionOrder.end(); iter++) {
			vector<string> item = *(m_ex_grammar.begin() + (*iter));
			item.insert(item.begin() + 2, POINT);
			vector<vector<string>> item_result;
			if ((*(item.begin() + 3)) == *(item.begin())) {//如果新生成的点后面还是自己的话，就不做拓展了，直接插入即可
				item_result.push_back(item);
			}
			else {
				item_result = do_extence(item);
			}
			result.insert(result.end(), item_result.begin(), item_result.end());
		}
	}
	//如果点后面是空和终结符的话，扩展只有它自己
	return result;

}
DFA_Items LR::get_valid_items(DFA_Item dfa_item) {
	//由DFA_Item起始项构建DFA_Iterms
	//在这里面设置子项是否为规约项
	vector<string> item = dfa_item.item;
	int order = dfa_item.order;

	vector<vector<string>> extent_items = do_extence(item);//对DFA的item作扩展,不论是否能不能扩展，能扩展就扩展，不能扩展保持原样
	vector<DFA_Item> dfa_items;
	for (auto iter = extent_items.begin(); iter != extent_items.end(); iter++) {
		//形成DFA_item
		int production = 0;
		bool if_r = false;
		vector<string> temp = (*iter);//临时变量，用于删除掉点找production在ex_grammar的下标
		auto allocation = find(temp.begin(), temp.end(), POINT);
		temp.erase(allocation);
		for (auto proIter = m_ex_grammar.begin(); proIter != m_ex_grammar.end(); proIter++) {
			if ((*proIter) == temp) {
				production = proIter - m_ex_grammar.begin();
			}
		}
		if (find((*iter).begin(), (*iter).end(), POINT) == ((*iter).end() - 1)) {//如果点在最后一个位置，就是规约项
			if_r = true;
		}
		else if (*(find((*iter).begin(), (*iter).end(), POINT)+1) == space){//不是最后一个位置，那点后面肯定还有字符，这个字符如果是空的话，也是规约项,必须是else if
			if_r = true;
		}
		DFA_Item new_dfa_item(order, production, (*iter),Line (space, -1) ,if_r);
		dfa_items.push_back(new_dfa_item);
	}
	return DFA_Items(order, dfa_items);
}
void LR::set_DFA() {
	vector<string> temp_item = m_ex_grammar[0];
	temp_item.insert(temp_item.begin() + 2, POINT);
	DFA_Item start_item(STATUS_ORDER++, 0, temp_item, Line (space,-1));
	DFA_Items start_status = get_valid_items(start_item);
	queue<DFA_Items> queue;
	queue.push(start_status);
	m_DFA.push_back(start_status);						//入队列的时候记录此DFA_items。保持当前产生的新状态可以立马在DFA中看到
	while (!queue.empty()) {
		DFA_Items now_status = queue.front();
		queue.pop();
		for (int i = 0; i < now_status.items.size(); i++) {	//遍历DFA_items中的item
			if (now_status.items[i].if_reduce == true) {
				//如果是规约项的话，则此项后面不加新的状态
				continue;
			}
			//先画出线
			auto pointIter = find(now_status.items[i].item.begin(), now_status.items[i].item.end(), POINT);
			now_status.items[i].line.transform = (*(pointIter + 1));//直线上面的字符(串)为点后面的哪个字符(串)

			//再形成新的DFA状态
			DFA_Item next_status_start_item = now_status.items[i].move_point();
			DFA_Items next_status = get_valid_items(next_status_start_item);
			
			int if_merge = 0;				//是否合并过状态(有相同的状态或者两个status由一个相同的transform)
			auto allocation = find(m_DFA.begin(), m_DFA.end(), next_status);//这里LR0和LR1不同，LR1为find_if
			if (allocation != m_DFA.end()) {
				next_status.change_order((*allocation).order);//如果新生成的next_status已经有了，则回退序号
				now_status.items[i].line.next = next_status.order;
				if_merge = 1;
				//queue.push(next_status);也不用入队再进行分析
			}
			else {
				for (int j = 0; j < i; j++) {
					if (now_status.items[j].line.transform == now_status.items[i].line.transform) {
						next_status.change_order(now_status.items[j].line.next);
						now_status.items[i].line.next = next_status.order;
						//进行m_DFA中的物理合并
						for (auto dfaIter = m_DFA.begin(); dfaIter != m_DFA.end(); dfaIter++) {
							if ((*dfaIter).order == next_status.order) {
								//m_DFA中的进行物理合并
								for (auto tempIter = next_status.items.begin(); tempIter != next_status.items.end(); tempIter++) {
									if (find((*dfaIter).items.begin(), (*dfaIter).items.end(), *tempIter) == (*dfaIter).items.end()) {
										(*dfaIter).items.push_back((*tempIter));
									}
								}
								//对queue中的进行替换,queue没有迭代器，所以只能将一个个弹出来，相等的序号用新的替换再入队，不等的直接入队，一共进行queue.size()次，相当于遍历 
								for (int i = 0; i < queue.size(); i++) {
									DFA_Items temp = queue.front();
									queue.pop();
									if (temp.order == next_status.order) {
										temp = (*dfaIter);
									}
									queue.push(temp);
								}
							}
						}
						if_merge = 1;
						break;
					}
				}
			}

			if (!if_merge) {			//如果没有合并过状态
				now_status.items[i].line.next = next_status.order;
				queue.push(next_status);
				m_DFA.push_back(next_status);
			}
			
			for (auto iter = m_DFA.begin(); iter != m_DFA.end(); iter++) {
				if ((*iter).order == now_status.order) {
					for (auto tempIter = (*iter).items.begin(); tempIter != (*iter).items.end(); tempIter++) {
						if ((*tempIter).item == now_status.items[i].item) {
							(*iter).items[i].line = now_status.items[i].line;//对已经放入DFA中的进行更新，因为now_status是入队列时放在m_DFA中，而出队列后对此status还有line的变化
						}
					}
					break;
				}
			}
		}
	}

}
void LR::set_parse_col() {
	vector<string> col;
	col.insert(col.end(), m_terminal.begin(), m_terminal.end());
	col.insert(col.end(), "$");
	col.insert(col.end(), m_non_terminal.begin() + 1, m_non_terminal.end());//开始符号不用加入，所以迭代器+1
	for (auto iter = col.begin(); iter != col.end(); iter++) {
		m_col[*iter] = iter - col.begin();
	}
}
bool LR::parse_string(vector<string> input) {
	if (m_whether_parse == 0) return false;

	int INPUT_WIDTH = 10;
	string output_string = "";
	vector<string> parse_stack;					//本来应该用栈结构，但是考虑到输出，所以用vector
	vector<string> input_stack = input;
	input_stack.push_back("$");
	for (auto iter = input.begin(); iter != input.end(); iter++) {
		INPUT_WIDTH += (*iter).size();
	}

	parse_stack.insert(parse_stack.begin(), "$");
	parse_stack.insert(parse_stack.begin(), "0");

	std::cout << setw(PARSE_WIDTH) << "Parse stack";
	std::cout << std::right << setw(INPUT_WIDTH) << "Input stack" << std::left;
	std::cout << std::right << setw(ACTION_WIDTH) << "Action" << std::endl << std::left;


	while (input_stack.size() != 0 || parse_stack.size() != 0) {

		//输出栈的内容
		output_string = "";
		for (auto iter = parse_stack.rbegin(); iter != parse_stack.rend(); iter++) {
			output_string += (*iter);
		}
		std::cout << setw(PARSE_WIDTH) << output_string;

		output_string = "";
		for (auto iter = input_stack.begin(); iter != input_stack.end(); iter++) {
			output_string += (*iter);
		}
		std::cout << std::right << setw(INPUT_WIDTH) << output_string << std::left;

		int topParse = atoi((*parse_stack.begin()).c_str());//字符串转化为int
		string topInput = (*input_stack.begin());
		Parse_Action action = m_parse_table[topParse][m_col[topInput]];
		if (action.act == Error) {
			m_whether_parse = 0;
			std::cout << std::right << setw(ACTION_WIDTH) << Action_map[action.act] << endl << std::left;
			return false;
		}
		else if (action.act == Conflict) {
			m_whether_parse = 0;
			std::cout << std::right << setw(ACTION_WIDTH) << Action_map[action.act] << endl << std::left;
			return false;
		}
		else if (action.act == Shift) {
			parse_stack.insert(parse_stack.begin(), topInput);
			input_stack.erase(input_stack.begin());
			parse_stack.insert(parse_stack.begin(), to_string(action.num));
			string temp = Action_map[action.act] + to_string(action.num);
			std::cout << std::right << setw(ACTION_WIDTH) << temp << endl << std::left;
		}
		else if (action.act == Reduce) {
			if (*(m_ex_grammar[action.num].begin()+2) == space) {
				//如果规约项为空的话，不擦除栈顶
			}
			else {
				parse_stack.erase(parse_stack.begin(), parse_stack.begin() + 2 * (m_ex_grammar[action.num].size() - 2));
			}

			int topInt = atoi((*parse_stack.begin()).c_str());
			parse_stack.insert(parse_stack.begin(), *m_ex_grammar[action.num].begin());
			string topString = *parse_stack.begin();
			Parse_Action tempAction = m_parse_table[topInt][m_col[topString]];
			if (tempAction.act == Error) { //如果得到的新动作是错误动作，报错退出
				m_whether_parse = 0;
				std::cout << std::right << setw(ACTION_WIDTH) << Action_map[action.act] << endl << std::left;
				return false;
			}
			parse_stack.insert(parse_stack.begin(), to_string(tempAction.num));
			string temp = Action_map[action.act] + to_string(action.num);
			std::cout << std::right << setw(ACTION_WIDTH) << temp << endl << std::left;
		}
		else if (action.act == Accpet) {
			std::cout << std::right << setw(ACTION_WIDTH) << Action_map[action.act] << endl << std::left;
			return true;
		}
		else {
			m_whether_parse = 0;
			std::cout << std::right << setw(ACTION_WIDTH) << Action_map[action.act] << endl << std::left;
			return false;
		}
	}

}
void LR::print_grammar_of_extension() {
	std::cout << endl;
	std::cout << "Grammar of extension is:" << std::endl;
	for (auto iter = m_grammar_of_extension.begin(); iter != m_grammar_of_extension.end(); iter++) {
		for (auto jIter = (*iter).begin(); jIter != (*iter).end(); jIter++) {
			std::cout << (*jIter) << " ";
		}
		std::cout << std::endl;
	}
}
void LR::print_DFA() {
	int DFA_WIDTH = 10;
	
	for (auto iIter = m_ex_grammar.begin(); iIter != m_ex_grammar.end(); iIter++) {
		int temp_DFA_WIDTH = 0;
		for (auto jIter = (*iIter).begin(); jIter != (*iIter).end(); jIter++) {
			temp_DFA_WIDTH += (*jIter).size();
		}
		temp_DFA_WIDTH += 2*(*iIter).size();
		if (temp_DFA_WIDTH > DFA_WIDTH) {
			DFA_WIDTH = temp_DFA_WIDTH;
		}
	}
	std::cout << endl;
	std::cout << "DFA:" << endl;
	for (int i = 0; i < STATUS_ORDER; i++) {
		cout << "Status" << i << endl;
		for (auto iIter = m_DFA.begin(); iIter != m_DFA.end(); iIter++) {
			DFA_Items dfa_items = (*iIter);
			if (dfa_items.order == i) {
				
				for (auto jIter = dfa_items.items.begin(); jIter != dfa_items.items.end(); jIter++) {
					string temp = "";
					for (auto kIter = (*jIter).item.begin(); kIter != (*jIter).item.end(); kIter++) {
						temp+= (*kIter);
						if (kIter-(*jIter).item.begin() >= 1)
						temp += " ";
					}
					std::cout << setw(7) << " " << std::left << setw(DFA_WIDTH) << temp;
					if ((*jIter).line.next == -1) {
						cout << "reduce item" << endl;
					}
					else {
						cout << "_____" << (*jIter).line.transform << "_____>" << (*jIter).line.next << endl;
					}
				}
			}
			
		}
	}
}

void LR::print_parse_table() {
	std::cout << std::endl;
	std::cout << "ParseTable is:" << std::endl;
	int length = 6;//控制显示的列宽度

	//第一行表头
	std::cout << setw(length) << "M[S,T]";
	for (auto iter = m_terminal.begin(); iter != m_terminal.end(); iter++) {
		std::cout << setw(length) << (*iter);
	}
	std::cout << setw(length) << "$";

	for (auto iter = m_non_terminal.begin(); iter != m_non_terminal.end(); iter++) {
		if (iter == m_non_terminal.begin()) {}
		else {
			std::cout << setw(length) << (*iter);
		}
	}
	std::cout << endl;

	for (auto iIter = m_parse_table.begin(); iIter != m_parse_table.end(); iIter++) {
		int i = iIter - m_parse_table.begin();
		std::cout << setw(length) << i;
		for (auto jIter = (*iIter).begin(); jIter != (*iIter).end(); jIter++) {
			int j = jIter - (*iIter).begin();
			if (m_parse_table[i][j].act == Error) {
				std::cout << setw(length) << " ";
			}
			else if (m_parse_table[i][j].act == Push) {
				std::cout << setw(length) << m_parse_table[i][j].num;
			}
			else if (m_parse_table[i][j].act == Accpet) {
				std::cout << setw(length) << Action_map[Accpet];
			}
			else {
				string temp = Action_map[m_parse_table[i][j].act] + to_string(m_parse_table[i][j].num);
				std::cout << setw(length) << temp;
			}

		}
		std::cout << std::endl;
	}
	if (m_whether_parse == 0) {
		std::cout << "This grammar can't parse string! I used Charactor 'C' to mark allocation!" << endl;
	}
}

#pragma once
#include "LR.h"

class LR1 :public LR {
protected:
	set<string> get_first(vector<string> gamma);	//重写Parse的get_first，有一点点变化
	void merge_flag_of_items(vector<vector<string>>&);	//合并同一个DFA里面的除标志字符外都相等的项
	vector<vector<string>> do_extence(vector<string> start);
	DFA_Items get_valid_items(DFA_Item dfa_item);
	virtual void set_DFA();
	void set_parse_table();
public:
	LR1(vector<vector<string>>grammar) :LR(grammar) {
		this->set_DFA();
		this->set_parse_table();
	}
	


};
set<string> LR1::get_first(vector<string> gamma) {
	//这里的gamma是有形似与C ! c d或者 a C ! c d的串，而假设C的first为c d的话，我们要得出对应的c d与 a
	/*
	为什么要重写此方法，这里的标志串存储时，c/d存储为c d，而如果原先的求first的话，就只求成c了，但是还有d
	*/
	set<string> result;
	int space_num = 0;		//记录空符号个数
	auto separationIter = find(gamma.begin(), gamma.end(), SEPARATION);//分割符之前的用原先的方法，之后的有点点不同
	for (auto iter = gamma.begin(); iter != gamma.end(); iter++) {
		if (separationIter - iter > 0) {
			if (find(m_first[*iter].begin(), m_first[*iter].end(), space) != m_first[*iter].end()) {//如果有空,肯定是非终结符或者空
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
		else if (separationIter - iter == 0) {
			//不做处理
		}
		else {
			if (find(m_first[*iter].begin(), m_first[*iter].end(), space) != m_first[*iter].end()) {//如果有空,肯定是非终结符或者空
				result.insert(m_first[*iter].begin(), m_first[*iter].end());
				result.erase(space);
				space_num++;
			}
			else {//是终结符的话加入但是不返回,也就是可以加入后面的终结符，期到了c d的first为 c d
				result.insert(m_first[*iter].begin(), m_first[*iter].end());
				//return result;这就是不同之处，之后非终结符全部加入，
			}

			if (space_num == gamma.size() -1) {//表明全部都有空，-1是因为要减去分隔符!
				result.insert(space);
			}
		}
		
	}

	return result;
}
/*
防止这种情况出现:
L -> . a R ! =
L -> . b ! =
L -> . a R ! $
L -> . b ! $
*/
void LR1:: merge_flag_of_items(vector<vector<string>>& result) {
	vector<int> duplicate_order;			//DFA_item的item中重复的序号
	for (auto iIter = result.begin(); iIter != result.end() - 1; iIter++) {
		vector<string> a = (*iIter);
		for (auto jIter = (iIter + 1); jIter != result.end(); jIter++) {
			vector<string> b = *jIter;
			a.erase(find(a.begin(), a.end(), SEPARATION), a.end());
			b.erase(find(b.begin(), b.end(), SEPARATION), b.end());
			if (a == b) {			//如果除过分隔符以后相等的话，将后面重复的标识符加到前面的后面并记录下标,重复的不加
				auto sepaIter = find((*jIter).begin(), (*jIter).end(), SEPARATION);
				duplicate_order.push_back(jIter - result.begin());
				for (auto alloIter = sepaIter + 1; alloIter != (*jIter).end(); alloIter++) {
					if (find((*iIter).begin(), (*iIter).end(), (*alloIter)) == (*iIter).end()) {
						(*iIter).push_back((*alloIter));
					}
				}
			}
		}
	}
	for (auto iIter = duplicate_order.rbegin(); iIter != duplicate_order.rend(); iIter++) {//从大到小删除
		result.erase(result.begin() + (*iIter));//对重复的进行剔除
	}
	for (auto iIter = result.begin(); iIter != result.end(); iIter++) {
		auto sepaIter = find((*iIter).begin(), (*iIter).end(), SEPARATION);
		sort(sepaIter + 1, (*iIter).end());
	}
}
vector<vector<string>> LR1::do_extence(vector<string> item) {//传递过来的是带分隔符！相关字符的item
	auto iter = find(item.begin(), item.end(), POINT);
	auto separationIter = find(item.begin(), item.end(), SEPARATION);
	vector<vector<string>> result;
	result.push_back(item);
	if ((iter + 1) == separationIter) {//如果点是最后一个(也就是分隔符前一个的话）的话，扩展就只有它自己
	}
	else {
		string after_point = (*(iter + 1));
		//如果点不是最后一个的话， 点之后的字符串是非终结符的话，找出这个非终结符的所有产生式，并且对每一个加入点作扩展
		if (find(m_non_terminal.begin(), m_non_terminal.end(), after_point) != m_non_terminal.end()) {
			vector<string> needFirstBunch(iter + 2, item.end());//得到从点下下一个字符串的first集合
			set<string> bunchFirst = this->get_first(needFirstBunch);//这里重写了get_first方法，与原先的Parse里面的有一点点不同，不同是串的物理存储导致的
			vector<string> bunchFirstVector(bunchFirst.begin(), bunchFirst.end());
			vector<int> productionOrder;
			for (auto iter = m_ex_grammar.begin(); iter != m_ex_grammar.end(); iter++) {
				if (*((*iter).begin()) == after_point) {
					productionOrder.push_back(iter - m_ex_grammar.begin());
				}
			}
			for (auto iter = productionOrder.begin(); iter != productionOrder.end(); iter++) {
				vector<string> item = *(m_ex_grammar.begin() + (*iter));
				item.insert(item.begin() + 2, POINT);

				item.insert(item.end(), SEPARATION);//再插入分割符号！
				item.insert(item.end(), bunchFirstVector.begin(), bunchFirstVector.end());//再在末尾插入first集合
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
	}
	//如果点后面是空和终结符的话，扩展只有它自己
	
	return result;

}
DFA_Items LR1::get_valid_items(DFA_Item dfa_item) {
	//由DFA_Item起始项构建DFA_Iterms
	//在这里面设置子项是否为规约项
	vector<string> item = dfa_item.item;
	int order = dfa_item.order;

	vector<vector<string>> extent_items = do_extence(item);//对DFA的item作扩展,不论是否能不能扩展，能扩展就扩展，不能扩展保持原样
	merge_flag_of_items(extent_items);
	vector<DFA_Item> dfa_items;
	for (auto iter = extent_items.begin(); iter != extent_items.end(); iter++) {
		//形成DFA_item
		int production = 0;
		bool if_r = false;
		vector<string> temp = (*iter);//临时变量，用于删除掉点和分隔符及后面标志串找production在ex_grammar的下标
		auto allocation = find(temp.begin(), temp.end(), POINT);
		temp.erase(allocation);
		auto tempSeparationAll = find(temp.begin(), temp.end(), SEPARATION);
		temp.erase(tempSeparationAll, temp.end());
		for (auto proIter = m_ex_grammar.begin(); proIter != m_ex_grammar.end(); proIter++) {
			if ((*proIter) == temp) {
				production = proIter - m_ex_grammar.begin();
			}
		}
		auto separationAll = find((*iter).begin(), (*iter).end(), SEPARATION);
		if (find((*iter).begin(), (*iter).end(), POINT) == separationAll-1) {//如果点在最后一个位置，就是规约项
			if_r = true;
		}
		else if (*(find((*iter).begin(), (*iter).end(), POINT) + 1) == space) {//不是最后一个位置，那点后面肯定还有字符，这个字符如果是空的话，也是规约项,必须是else if
			if_r = true;
		}
		DFA_Item new_dfa_item(order, production, (*iter), Line(space, -1), if_r);
		dfa_items.push_back(new_dfa_item);
	}
	return DFA_Items(order, dfa_items);
}
void LR1::set_DFA() {
	vector<string> temp_item = m_ex_grammar[0];
	temp_item.insert(temp_item.begin() + 2, POINT);
	temp_item.insert(temp_item.end(), SEPARATION);
	temp_item.insert(temp_item.end(), "$");
	DFA_Item start_item(STATUS_ORDER++, 0, temp_item, Line(space, -1));
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
				next_status.change_order((*allocation).order);//如果新生成的next_status已经有了，则回退序号,而且也不需要入m_DFA
				now_status.items[i].line.next = next_status.order;
				if_merge = 1;
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
					break;	//已经进行了物理合并，只可能知道一个状态对应的DFA，所以找到后直接break;
				}
			}
			
		}
	}
}
void LR1::set_parse_table() {
	m_parse_table.resize(STATUS_ORDER, vector<Parse_Action>(m_col.size()));
	for (int i = 0; i < STATUS_ORDER; i++) {
		if (i == 1) {
			Parse_Action action(Accpet, 0);
			m_parse_table[i][m_col["$"]] = action;
			continue;
		}
		for (auto iIter = m_DFA.begin(); iIter != m_DFA.end(); iIter++) {
			if ((*iIter).order == i) {
				for (auto jIter = (*iIter).items.begin(); jIter != (*iIter).items.end(); jIter++) {
					string transform = (*jIter).line.transform;
					int next = (*jIter).line.next;
					int j = m_col[transform];

					if ((*jIter).if_reduce) {
						auto separationIter = find((*jIter).item.begin(), (*jIter).item.end(), SEPARATION);
						vector<string> flagBunch(separationIter + 1, (*jIter).item.end());
						for (auto xIter = flagBunch.begin(); xIter != flagBunch.end(); xIter++) {
							int x = m_col[*xIter];
							//只填到flagBunch里集合中，而对分析表的冲突判断则相同
							if (m_parse_table[i][x].act != Error) {//如果已经填了
								if (m_parse_table[i][j].act == Reduce && m_parse_table[i][j].num != (*jIter).production) {//但是规约到同一项
									m_parse_table[i][x] = Parse_Action(Reduce, (*jIter).production);
								}
								else {
									m_parse_table[i][x] = Parse_Action(Conflict, (*jIter).production);
									m_whether_parse = 0;
								}

							}
							else {
								m_parse_table[i][x] = Parse_Action(Reduce, (*jIter).production);
							}
						}


					}
					else {
						if (m_parse_table[i][j].act != Error) {	 //如果已经填写而且不是跳转到同一个状态的话
							if (find(m_terminal.begin(), m_terminal.end(), transform) != m_terminal.end() || transform == "$") {
								if (m_parse_table[i][j].act == Shift && m_parse_table[i][j].num == (*jIter).line.next) {
									m_parse_table[i][j] = Parse_Action(Shift, (*jIter).line.next);
								}
								continue;	//避免跳跃到同一状态但是动作不一样的
							}
							else {
								if (m_parse_table[i][j].act == Push && m_parse_table[i][j].num == (*jIter).line.next) {			//列为非终结符的时候
									m_parse_table[i][j] = Parse_Action(Push, (*jIter).line.next);
									continue;
								}
							}
							m_parse_table[i][j] = Parse_Action(Conflict, (*jIter).line.next);
							m_whether_parse = 0;
						}
						else {
							if (find(m_terminal.begin(), m_terminal.end(), transform) != m_terminal.end() || transform == "$") {
								m_parse_table[i][j] = Parse_Action(Shift, (*jIter).line.next);
							}
							else {			//列为非终结符的时候
								m_parse_table[i][j] = Parse_Action(Push, (*jIter).line.next);
							}
						}
					}

				}
			}
		}
	}
}
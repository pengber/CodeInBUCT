#pragma once
#include "LR1.h"
class LALR1 :public LR1 {
protected:
	void set_DFA();
	void add(int status, vector<string> a);//把status替换新的flag标志穿
public:
	LALR1(vector<vector<string>> grammar) :LR1(grammar) {
		STATUS_ORDER = 0;
		this->m_DFA.clear();
		this->m_parse_table.clear();
		this->set_DFA();
		this->set_parse_table();
		
	}
};
void LALR1::add(int status, vector<string> a) {
	for (auto dfaIter = m_DFA.begin(); dfaIter != m_DFA.end(); dfaIter++) {
		if ((*dfaIter).order == status) {
			for (auto itemIter = (*dfaIter).items.begin(); itemIter != (*dfaIter).items.end(); itemIter++) {
				auto sepaIter = find((*itemIter).item.begin(), (*itemIter).item.end(), SEPARATION);
				(*itemIter).item.erase(sepaIter + 1, (*itemIter).item.end());
				(*itemIter).item.insert((*itemIter).item.end(), a.begin(), a.end());
				if ((*itemIter).line.next != -1 && (*itemIter).line.next != status) {
					//如果有下个状态并且不是自己的话就再加上标志字符，-1的话会出现下标错误，自己的话会无限循环
					add((*itemIter).line.next, a);
				}
			}
			break;
		}
	}
}
void LALR1::set_DFA() {
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

			auto allocation = find_if(m_DFA.begin(), m_DFA.end(), DFA_Items(next_status));//!!!find_if,这里要用if


			if (allocation != m_DFA.end()) {
				next_status.change_order((*allocation).order);//如果新生成的next_status已经有了，则回退序号,而且也不需要入m_DFA
				//将现在状态！后面的字符提取出来，然后扫描旧状态的！后面的字符，如果没有的话就插在后面
				vector<DFA_Item>::iterator iIter = (*allocation).items.begin();
				vector<DFA_Item>::iterator jIter = next_status.items.begin();
				for (; iIter != (*allocation).items.end(), jIter != next_status.items.end(); iIter++, jIter++) {
					vector<string> a ((*iIter).item.begin(), (*iIter).item.end());
					vector<string> b((*jIter).item.begin(), (*jIter).item.end());
					auto iSepaIter = find(a.begin(), a.end(), SEPARATION);
					a.erase(a.begin(), iSepaIter+1);
					auto jSepaIter = find(b.begin(), b.end(), SEPARATION);
					b.erase(b.begin(), jSepaIter+1);
					for (auto bIter = b.begin(); bIter != b.end(); bIter++) {
						if (find(a.begin(), a.end(), (*bIter)) == a.end()) {
							a.push_back((*bIter));
						}
					}
					auto alloSeparation = find((*iIter).item.begin(), (*iIter).item.end(), SEPARATION);
					(*iIter).item.erase(alloSeparation+1, (*iIter).item.end());
					(*iIter).item.insert((*iIter).item.end(), a.begin(), a.end());
					if ((*iIter).line.next != -1 && (*iIter).line.next != (*iIter).order) add((*iIter).line.next, a);
				}
				now_status.items[i].line.next = next_status.order;
				if_merge = 1;
				//queue.push(next_status);应该也不用入队再进行分析
			}
			else {
				for (int j = 0; j < i; j++) {
					if (now_status.items[j].line.transform == now_status.items[i].line.transform) {//如果现在分析的子项和前面的子项的转移字符一样的话，则将此子项的状态和找到子项的状态进行“概念”合并，物理不进行合并
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
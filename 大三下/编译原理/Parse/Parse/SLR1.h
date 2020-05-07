#pragma once
#include "LR.h"

class SLR1 :public LR {
protected:
	//DFA_items get_valid_items();同理下
	//void set_parse_table();没有必要写，直接用父类的此虚函数的内容就行，父类的虚函数也可以处理，只不过是子类有的时候就用子类的，没有的时候就用父类的
	void set_parse_table();
public:
	SLR1(vector<vector<string>>grammar) :LR(grammar) {
		this->set_DFA();
		this->set_parse_table();
	}
	


};
void SLR1::set_parse_table() {
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
						vector<string> temp_production = m_ex_grammar[(*jIter).production];
						set<string> temp_follow = m_follow[*temp_production.begin()];
						for (auto xIter = temp_follow.begin(); xIter != temp_follow.end(); xIter++) {
							int x = m_col[*xIter];
							//只填到follow集合中，而对分析表的冲突判断则相同
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


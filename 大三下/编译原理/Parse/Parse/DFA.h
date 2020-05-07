#pragma once
#define POINT "."
#define SEPARATION "!"		//分割LR1和LALR1中的产生式与产生式后面的填写标志符号
#include <vector>
#include <string>
using namespace std;

int STATUS_ORDER = 0;								//现在的状态order数量,可以用这个变量说明内部类，静态变量等区别

struct Line {
	string transform;
	int next;
	Line() {
		next = -1;
	};
	Line(string t, int n = -1) {
		transform = t;
		next = n;
	}
};
struct DFA_Item {
	int order;				//自己属于第几个状态
	int production;			//自己的产生式的ex_grammar下标,填写分析表的时候好找到规约项下标
	vector<string> item;
	Line line;				//line.next = -1表示后面没有状态
	bool if_reduce;			//是否是规约项，默认为假
	DFA_Item(int o, int p, vector<string> i, Line l, bool if_r = false) {
		order = o;
		production = p;
		item = i;
		//item.insert(item.begin() + 2, POINT);加点不是在dfa_item初始化的时候加，而是扩展do_extence的时候加在dfa_item.item里面
		line = l;
		if_reduce = if_r;
	}
	bool operator==(const DFA_Item& dfa_item) const {//C++对健壮性很严格，必须加const
		return item == dfa_item.item;		//这是为LR0和SLR1的set_DFA中的find函数准备的
	}
	bool operator()(DFA_Item& dfa_item) {	//这是为LR1和LALR1的合并所准备的
		vector<string> a = item;
		vector<string> b = dfa_item.item;
		a.erase(find(a.begin(), a.end(), SEPARATION), a.end());
		b.erase(find(b.begin(), b.end(), SEPARATION), b.end());
		if (a == b) return true;			//如果dfa_item的item分隔符前面的都相等的话，返回真
		else return false;
	}
	DFA_Item move_point() {

		auto point_allocation = find(item.begin(), item.end(), POINT);
		string transform = (*(point_allocation + 1));		//在这里不做point是否是最后一个迭代器，在set_DFA中控制，是规约项的不能进行获取下一个状态，也就是下一个状态的起始状态不能move_point;
		this->line.transform = transform;
		this->line.next = STATUS_ORDER++;

		vector<string> new_item = this->item;
		auto new_point_allocation = find(new_item.begin(), new_item.end(), POINT);
		(*new_point_allocation) = (*(new_point_allocation + 1));
		(*(new_point_allocation + 1)) = POINT;

		bool if_r = false;
		if (find(new_item.begin(), new_item.end(), POINT) == (new_item.end() - 1)) {
			if_r = true;
		}
		DFA_Item temp(this->line.next, this->production, new_item, Line(space, -1), if_r);
		return temp;
	}
};

struct DFA_Items {
	int order;
	vector<DFA_Item> items;
	DFA_Items() {
		order = -1;
	}
	DFA_Items(int o, vector<DFA_Item> i) {
		order = o;
		items = i;
	}
	bool operator==(const DFA_Items& status) const {
		if (items == status.items) return true;
		else return false;
	}
	bool operator()(DFA_Items status) {//这里有点问题不知道怎么是哟个DFA_item的find_if的条件
		bool if_equal = true;
		vector<DFA_Item>::iterator iIter = this->items.begin();
		vector<DFA_Item>::iterator jIter = status.items.begin();
		for (; iIter != this->items.end(), jIter != status.items.end(); iIter++, jIter++) {
			if (!(*iIter)(*jIter)) {
				if_equal = false;
				break;
			}
		}
		return if_equal;
	}
	DFA_Items& operator=(DFA_Items& b) {
		this->order = b.order;
		this->items = b.items;
		return *this;
	}
	void change_order(int num) {
		this->order = num;
		for (auto iter = this->items.begin(); iter != items.end(); iter++) {
			(*iter).order = num;
		}
		STATUS_ORDER--;
	};	//用参数改变自身状态序号和自己的item的序号，并且将全局变量STATUS_ORDER-1,所以这个必须是新生成的Status才能使用，用以状态合并（相同状态或者同一个字符移进产生的结果）
};

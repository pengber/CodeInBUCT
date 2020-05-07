//
//  main.cpp
//  compiling3
//
//  Created by 徐奕 on 2018/11/6.
//  Copyright © 2018 Reacubeth. All rights reserved.
//
#include <iostream>
#include <vector>
#include <set>
#include <cstdio>
#include <algorithm>
using namespace std;
struct Part {
	string src;
	string edge;
	string dst;
};
void input(vector<Part>& NFA, int num) {
	for (int i = 0; i < num; i++) {
		Part temp;
		//scanf("%s,%s,%s",&temp.src,&temp.edge,&temp.dst);
		cin >> temp.src >> temp.edge >> temp.dst;
		NFA.push_back(temp);
	}
}
void outputNFA(vector<Part> NFA) {
	for (int i = 0; i < NFA.size(); i++) {
		cout << NFA[i].src << " " << NFA[i].edge << " " << NFA[i].dst << endl;
	}
}
bool check(string str, char x) {
	for (int i = 0; i < str.length(); i++) {
		if (str[i] == x)
			return true;
	}
	return false;
}
string closure(string setp, vector<Part> NFA) {
	for (int i = 0; i < setp.length(); i++) {
		for (int j = 0; j < NFA.size(); j++) {
			if (setp[i] == NFA[j].src[0] && NFA[j].edge[0] == '&') {
				if (!check(setp, NFA[j].dst[0])) {
					setp += NFA[j].dst[0];
				}
			}
		}
	}
	return setp;
}
string move(string t, char a, vector<Part> NFA) {
	string temp = "";
	for (int i = 0; i < t.length(); i++) {
		for (int j = 0; j < NFA.size(); j++) {
			if (t[i] == NFA[j].src[0] && NFA[j].edge[0] == a) {
				if (!check(temp, NFA[j].dst[0])) {
					temp += NFA[j].dst[0];
				}
			}
		}
	}
	return temp;
}
bool checkINrawDFA(vector<string> rawDFA, string u) {
	for (int i = 0; i < rawDFA.size(); i++) {
		if (rawDFA[i] == u)
			return true;
	}
	return false;
}
int checkFlag(vector<bool> t) {
	for (int i = 0; i < t.size(); i++) {
		if (t[i] == false)return i;
	}
	return -1;
}
int main(int argc, const char* argv[]) {
	vector<Part> NFA;
	int num;
	cout << "input: ";
	cin >> num;
	getchar();
	input(NFA, num);
	//outputNFA(NFA);
	char sigma[2] = { 'a','b' };//字母表
	string start = closure("0", NFA);//k起始符的闭包
	sort(start.begin(), start.end());
	vector<string> rawDFA;//存入子集
	rawDFA.push_back(start);
	vector<bool> rawDFAflag;//存入子集是否完成的标志
	rawDFAflag.push_back(false);
	cout << endl;
	while (checkFlag(rawDFAflag) != -1) {
		int m = checkFlag(rawDFAflag);
		rawDFAflag[m] = true;
		for (int i = 0; i < 2; i++) {
			string u = closure(move(rawDFA[m], sigma[i], NFA), NFA);
			sort(u.begin(), u.end());
			if (!checkINrawDFA(rawDFA, u)) {
				rawDFA.push_back(u);
				rawDFAflag.push_back(false);
			}
		}
	}
	cout << endl;
	for (int i = 0; i < rawDFA.size(); i++) {
		cout << rawDFA[i] << "   " << closure(move(rawDFA[i], 'a', NFA), NFA) << "   " << closure(move(rawDFA[i], 'b', NFA), NFA) << endl;
	}
	return 0;
}
/*
0 & 1
1 a 2
1 a 4
1 b 3
2 a 5
4 b 5
3 a 5
*/
/*
0 & 1
1 a 1
1 b 1
1 & 2
2 a 3
2 b 4
3 a 5
4 b 5
5 & 6
6 a 6
6 b 6
6 & 7
*/
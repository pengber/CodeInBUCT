#pragma once
#include "Parse.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "LR1.h"
using namespace std;
/*

ok: LR0分析不了，但是SLR1可以，LR1也可以分析
B -> b B | d D b
D -> a D | #
exit
b d b
exit

ok：SLR1可以分析，LR1也可以分析
S -> ( S ) S
S -> #
exit
( )
exit

ok：SLR1分析不了，但是LR1可以分析
S -> C C
C -> c C | d
exit
d c c d
exit

S -> L = L R | R
L -> a R | b
R -> L
exit
*/
void input(vector<vector<string>>& grammar) {
	string buf;
	string input;
	while (getline(cin, input) && input != "exit") {
		stringstream ss(input);
		vector<string> newRow;
		while (ss >> buf) {
			newRow.push_back(buf);
		}
		grammar.push_back(newRow);
	}
}
void output(vector < vector<string>>& grammar) {
	for (auto iter = grammar.begin(); iter != grammar.end(); iter++) {
		for (auto jIter = (*iter).begin(); jIter != (*iter).end(); jIter++) {
			cout << (*jIter) << " ";
		}
		cout << endl;
	}
}
int main() {
	vector<vector<string> > grammar;
	input(grammar);
	LR1 ll(grammar);

	vector<string> input_string;
	string str;
	while (cin >> str && str != "exit") {
		input_string.push_back(str);
	}
	if (ll.parse_string(input_string)) std::cout << "acc";
	else std::cout << "can't acc";

	//output(grammar);
	return 0;
}
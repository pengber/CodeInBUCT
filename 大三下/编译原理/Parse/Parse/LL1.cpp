#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include "LL1.h"
using namespace std;
/*
ok: 一般左递归检测
A -> B a | A a | c
B -> B b | A b | d
exit

ok: 左因子检测
A -> a b | a c
exit
a b
exit

ok: 
expr -> expr addop term | term
addop -> + | -
term -> term mulop factor | factor
mulop -> *
factor -> ( expr ) | number
exit
number * number
exit

ok: 不能分析，因为分析表中有两个规约选择
statement -> if-stmt | other
if-stmt -> if ( exp ) statement else-part
else-part -> else statement | #
exp -> 0 | 1
exit
if ( 1 ) other else other
exit

ok: 注意varlist -> id , varlist | id消除左因子
declaration -> type varlist
type -> int | float
varlist -> id , varlist | id
exit
int id , id , id
exit

ok: 
lexp -> atom | list
atom -> num | id
list -> ( lexp-seq )
lexp-seq -> lexp-seq lexp | lexp
exit
( ( id ) num )
exit

ok:
S -> a | ^ | ( T )
T -> T , S | S
exit
( a , ( ^ ) ) 
exit
*/
void input(vector<vector<string>>& grammar, vector<string>& input_string) {
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
	string str;
	while (cin >> str && str != "exit") {
		input_string.push_back(str);
	}
}
void input_by_file(vector<vector<string>>& grammar, string filename) {
	ifstream fcin;
	fcin.open(filename);
	string buf;
	string input;
	while (getline(fcin, input) && !fcin.eof()) {
		if (input != "exit") {
			stringstream ss(input);
			vector<string> newRow;
			while (ss >> buf) {
				newRow.push_back(buf);
			}
			grammar.push_back(newRow);
		}
		else {
			continue;
		}
	}
	fcin.close();
}
void input_by_file(vector<string>& input_string, string filename) {
	ifstream fcin;
	fcin.open(filename);
	string str;
	while (fcin >> str && str != "exit") {
		input_string.push_back(str);
	}
	fcin.close();
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

	vector<string> input_string;
	//input(grammar,input_string);
	input_by_file(grammar, "input_grammar.txt");
	input_by_file(input_string, "input_bunch.txt");
	LL1 ll(grammar);
	ll.print_grammar();
	ll.print_grammar_without_recursion();
	ll.print_ex_grammar();
	ll.print_first();
	ll.print_fllow();
	ll.print_terminal_and_nonTerminal();
	ll.print_parse_table();

	if (ll.parse_string(input_string)) std::cout << "acc";
	else std::cout << "can't acc";
	getchar();
	return 0;
}
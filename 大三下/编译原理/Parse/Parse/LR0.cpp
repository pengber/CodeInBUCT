#pragma once
#include "Parse.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "LR0.h"
using namespace std;
/*
no: 一般左递归检测不行
A -> B a | A a | c
B -> B b | A b | d
exit

ok: 左因子检测
A -> a b | a c
exit
a b
exit

ok: 不能分析，分析表有冲突
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

ok: LR0不用消除左因子，不能分析，第6个状态既有规约有有移进
declaration -> type varlist
type -> int | float
varlist -> id , varlist | id
exit
int id , id , id
exit

ok: 可以分析，并且串正确
lexp -> atom | list
atom -> num | id
list -> ( lexp-seq )
lexp-seq -> lexp-seq lexp | lexp
exit
( ( id ) num )
exit

ok: 可以分析，并且串正确
S -> a | ^ | ( T )
T -> T , S | S
exit
( a , ( ^ ) )
exit


----
ok: 可以分析，并且串正确
E -> ( L ) | a
L -> L , E | E
exit
( ( a ) , a )
exit

ok：LR0分析不了,SLR1可以
S -> ( S ) S
S -> #
exit
S -> ( )
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
	LR0 ll(grammar);

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
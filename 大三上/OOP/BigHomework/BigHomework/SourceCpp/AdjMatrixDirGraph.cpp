#include "AdjMatrixDirGraph.h"
#include <iostream>
using namespace std;
void write(char & ch);
void menu();
int main()
{
	int opeNum;
	int vexNum;
	char elems[1000];
	AdjMatrixDirGraph<char> graph;
	menu();
	while (cout << "请输入操作序号" && cin >> opeNum && opeNum != 0) {
		switch (opeNum)
		{
		case 1:
			cout << "请输入顶点个数" << endl;
			cin >> vexNum;
			cout << "请输入顶点元素" << endl;
			for (int i = 0; i < vexNum; i++) {
				cin >> elems[i];
			}
			graph.setGraph(elems, vexNum);
			break;
		case 2:
			graph.display();
			break;
		case 3:
			cout << graph.getVertexCount() << endl;
			break;
		case 4:
			cout << graph.getEdgeCount() << endl;
			break;
		case 5:
			graph.DFSTraverse(0, write);
			break;
		case 6:
			graph.BFSTraverse(0, write);
			break;
		default:
			break;
		}
	}
	return 0;
}

void write(char & ch) {
	cout << ch << endl;
}
void menu() {
	cout << "0.退出";
	cout << "1.建立图" << endl;
	cout << "2.输出图的相关信息" << endl;
	cout << "3.输出顶点数目" << endl;
	cout << "4.输出边的数目 "<< endl;
	cout << "5.深度优先搜索" << endl;
	cout << "6.广度优先搜索" << endl;
	cout << "7.更多选择,请查阅源码" << endl;
	
}
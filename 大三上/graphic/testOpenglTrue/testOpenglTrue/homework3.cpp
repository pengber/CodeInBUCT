
#include <iostream>
#include <vector>
#include <queue>
#include <GL/glut.h>
#include <GL/GL.h>
#include <Windows.h>
#include <math.h>
#define EDGES 6
#define WINDOW_SIZE_X 400
#define WINDOW_SIZE_Y 600
using namespace std;


class MyPair {
public:
	int x_;
	int y_;
	MyPair() { x_ = 0; y_ = 0; }
	MyPair(int x, int y) {
		x_ = x;
		y_ = y;
	}
};
class Edge {
public:
	double x_;//用double而不是int，因为deltaX会有浮点数，咱们计算出真正的坐标，让drawPixl自己去转换int描绘最近的点
	float deltaX_;
	int ymax_;
	Edge() { x_ = 0; deltaX_ = 0; ymax_ = 0; }
	Edge(int x, float deltaX, int ymax) {
		x_ = x;
		deltaX_ = deltaX;
		ymax_ = ymax;
	}
	friend bool operator < (const Edge& a, const Edge& b) {
		if (a.x_ == b.x_) return a.ymax_ > b.ymax_;
		return a.x_ > b.x_;
	};
};

//返回顶点的下标
int findPair(int i, MyPair* polygon) {
	for (int j = 0; j < EDGES; j++) {
		if (polygon[j].y_ == i) return j;
	}
	return -1;
}
float getDeltaX(MyPair& a, MyPair& b) {
	return 1.0 * (a.x_ - b.x_) / (a.y_ - b.y_);
}
MyPair rotate(const MyPair &a) {
	double ff = sqrt(2) / 2.0;
	double m[3][3] = {
		ff, -ff, -2+ff,
		ff, ff, -1-ff,
		0, 0, 1
	};
	double x, y;
	x = m[0][0] * a.x_ + m[0][1] * a.y_;
	y = m[1][0] * a.x_ + m[1][1] * a.y_;
	return MyPair(x, y);
}
void polygonFill() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_POINTS);

	MyPair* polygon = new MyPair[EDGES];
	queue<Edge>* NET = new queue<Edge>[WINDOW_SIZE_Y];
	priority_queue<Edge> AET;
	//六边形六个顶点
	polygon[0].x_ = 250;
	polygon[0].y_ = 50;
	polygon[1].x_ = 550;
	polygon[1].y_ = 150;
	polygon[2].x_ = 550;
	polygon[2].y_ = 400;
	polygon[3].x_ = 250;
	polygon[3].y_ = 440;
	polygon[4].x_ = 100;
	polygon[4].y_ = 350;
	polygon[5].x_ = 100;
	polygon[5].y_ = 100;
	
	for (int i = 0; i < EDGES; i++) {
		polygon[i].x_ += 200;

	}
	

	for (int i = 0; i < WINDOW_SIZE_Y; i++) {//新编表
		int index = findPair(i, polygon);
		if (index != -1) {//这条扫描线上有点
			if (polygon[(index - 1 + EDGES) % EDGES].y_ > polygon[index].y_) {//左边顶点比此顶点高
				Edge temp(polygon[index].x_, getDeltaX(polygon[index], polygon[(index - 1 + EDGES) % EDGES]), polygon[(index - 1 + EDGES) % EDGES].y_);
				NET[i].push(temp);
			}

			if (polygon[(index + 1 + EDGES) % EDGES].y_ > polygon[index].y_) {
				Edge temp(polygon[index].x_, getDeltaX(polygon[index], polygon[(index + 1 + EDGES) % EDGES]), polygon[(index + 1 + EDGES) % EDGES].y_);
				NET[i].push(temp);
			}
		}
	}

	for (int i = 0; i < WINDOW_SIZE_Y; i++) {//活性边表
		while (!NET[i].empty()) {//当新边表不为空的话
			Edge tempEdge;
			tempEdge = NET[i].front();
			NET[i].pop();
			AET.push(tempEdge);
		}
		int size = AET.size();
		Edge* edges = new Edge[size];	//因为优先队列不能遍历，所以自己新建一个数组，用于存储优先队列的值，再判断是否再压入优先队列（活性边表中）
		for (int k = 0; k < size - 1; k += 2) {//每次取一对
			edges[k] = AET.top();
			AET.pop();
			edges[k + 1] = AET.top();
			AET.pop();
			for (int j = edges[k].x_; j < edges[k + 1].x_; j++) {
				glVertex2i(j, i);
				MyPair tempPairA(j, i);
				MyPair tempPair = rotate(tempPairA);
				glVertex2i(tempPair.x_, tempPair.y_);
			}
		}
		for (int k = 0; k < size; k++) {
			if (edges[k].ymax_ == i + 1);//如果这个节点下一次就到头了，就不放入活性边表了，新编表会自动产生新的节点
			else {
				edges[k].x_ += edges[k].deltaX_;
				AET.push(edges[k]);
			}
		}
		delete[]edges;


	}
	glEnd();
	glFlush();
}
void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.4, 0.2);
	glPointSize(1);
	glBegin(GL_POINTS);
	polygonFill();
	glEnd();
	glFlush();
}

void init(int argc, char** argv)
{
	glutInit(&argc, argv);  //I初始化 GLUT.
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  //设置显示模式：单个缓存和使用RGB模型
	glutInitWindowPosition(50, 100);  //设置窗口的顶部和左边位置
	glutInitWindowSize(400, 300);  //设置窗口的高度和宽度
	glutCreateWindow("Scan Program");

	glClearColor(1.0, 1.0, 1.0, 0); //窗口背景颜色为白色
	glMatrixMode(GL_PROJECTION);
	//gluOrtho2D(0, 600, 0, 450);
	gluOrtho2D(-1000, 1000, -1000, 1000);
}

int main(int argc, char** argv) {
	init(argc, argv);
	glutDisplayFunc(myDisplay);        //图形的定义传递给我window.
	glutMainLoop();
	return 0;
}
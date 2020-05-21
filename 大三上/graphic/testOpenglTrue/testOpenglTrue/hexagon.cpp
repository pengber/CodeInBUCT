#include <GL/glut.h>
#include <GL/GL.h>
#include <vector>
#include <list>
using namespace std;

#define sqr(x) (x) * (x)
#define Height 400
void hexagon(void)
{
	GLfloat x1 =-200, y1 =400;
	GLfloat x2 = 200, y2 = 400;
	GLfloat x3 = 400, y3 = 0;
	GLfloat x4 = 200, y4 = -400;
	GLfloat x5 = -200, y5 = -400;
	GLfloat x6 = -400, y6 = 0;
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 1.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_POLYGON);

	glVertex2f(x1, y1); 
	glVertex2f(x2, y2);  
	glVertex2f(x3, y3);               
	glVertex2f(x4, y4); 
	glVertex2f(x5, y5);
	glVertex2f(x6, y6);
	glEnd();
	glFlush();
}
struct edge {
	GLfloat x;
	GLfloat deltx;
	GLfloat ymax;
};
struct myPair {
	GLfloat x;
	GLfloat y;
};
edge compare(myPair x, pair b) {

}
void fillHexagon() {
	vector<list<edge>> net(100);
	for (int i = 0; i < Height; i++) {

	}
}

//glut各函数讲解https://www.jianshu.com/p/86f8ce123de1
int main(int argc, char** argv) {
	glutInit(&argc, argv);//初始化glut

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(200, 100);
	glutCreateWindow("Ellipse:");//创建窗口
	glClearColor(1.0, 1.0, 0.0, 0.0);
	gluOrtho2D(-400, 400, -400, 400);
	glutDisplayFunc(hexagon);//渲染图形
	glutMainLoop();
	return 0;
}
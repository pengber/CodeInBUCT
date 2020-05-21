#include <GL/glut.h>
#include <GL/GL.h>

#define sqr(x) (x) * (x)
void k1(){// 0 < k < 1
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_POINTS);
	GLint x1 = 0, y1 = 0, x2 = 400, y2 = 200;
	GLint x = x1, y = y1;
	GLint dx = x2 - x1, dy = y2 - y1, dT = 2 * (dy - dx), dS = 2 * dy;
	GLint d = 2 * dy - dx;
	glVertex2i(x, y);
	while (x < x2) {
		x++;
		if (d < 0)
			d = d + dS;
		else { y++;
		d = d + dT;
		}
		glVertex2i(x, y);
	}
	glEnd();
	glFlush();
}
void midLine() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_POINTS);
	GLint x0 = 0, y0 = 0, x1 = 100, y1=300;
	GLint a, b, d1, d2, d, x, y;
	a = y0 - y1, b = x1 - x0, d = 2 * a - b;
	d1 = 2 * a; d2 = 2 * (a + b);
	x = x0;
	y = y0;
	glVertex2i(x, y);
	while (x < x1) {
		if (d < 0) {
			x++, y++, d += d2;
		}
		else {
			x++, d += d1;
		}
		glVertex2i(x, y);
	}
	glEnd();
	glFlush();
}

void CirclePoints(int x, int y) {
	glVertex2i(x, y);
	glVertex2i(y, x);
	glVertex2i(-x, y);
	glVertex2i(y,-x);
	glVertex2i(x, -y);
	glVertex2i(-y, x);
	glVertex2i(-x, -y);
	glVertex2i(-y, -x);
}
void EllipsePoints(int x, int y) {
	glVertex2i(x, y);
	glVertex2i(x, -y);
	glVertex2i(-x, y);
	glVertex2i(-x, -y);
}
void MidPointCircle() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_POINTS);
	GLint r = 200;
	GLint x, y;
	float d;
	x = 0;
	y = r;
	d = 1.25 - r;
	CirclePoints(x, y);
	while (x <= y) {
		if (d < 0) d += 2 * x + 3;
		else { d += 2 * (x - y) + 5; y--; }
		x++;
		CirclePoints(x, y);
	}
	glEnd();
	glFlush();
}
void MidPointEllipse() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_POINTS);
	GLint a =100, b =50;
	GLint x, y;
	GLfloat d1, d2;
	x = 0;
	y = b;
	d1 = b * b + a * a *(-b + 0.25);
	glVertex2i(x, y);
	while (b * b * (x + 1) < a * a * (y - 0.5)) {
		if (d1 < 0) {
			d1 += b * b * (2 * x + 3);
			x++;
		}
		else {
			d1 += (b * b * (2 * x + 3) + a * a * (-2 * y + 2));
			x++;
			y--;
		}
		EllipsePoints(x, y);
	}
	d2 = sqr(b * (x + 0.5)) + sqr(a * (y - 1)) - sqr(a*b);
	while (y > 0) {
		if (d2 < 0) {
			d2 += b*b * (2 * x + 2) + a * a * (-2 * y + 3);
			x++;
			y--;
		}
		else {
			d2 += a*a * (-2 * y + 3);
			y--;
		}
		EllipsePoints(x, y);
	}
	glEnd();
	glFlush();
}
//glut各函数讲解https://www.jianshu.com/p/86f8ce123de1
void main(int argc, char** argv) {
	glutInit(&argc, argv);//初始化glut
	
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(200, 100);
	glutCreateWindow("Ellipse:");//创建窗口
	glClearColor(1.0, 1.0, 0.0, 0.0);
	gluOrtho2D(-400, 400, -400, 400);
	glutDisplayFunc(MidPointEllipse);//渲染图形
	glutMainLoop();

}
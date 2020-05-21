// ====== Computer Graphics Experiment #7 ======
// |              Bezier curve                 |
// =============================================
//
// Requirement:
// (1) Implement algorithm to draw Bezier curve.
// (2)Implement interactive method to specify
//     Bezier curve control points by mouse clicking.
// (3) Implement display callback function

#include <windows.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

// 2D point class
class CPoint2D
{
public:
	float x, y;
};

int n_cp; // Number of control points
int ic_cp; // Control point counter
int i_cp; // Index of control point being moved
CPoint2D* control_points; // Coordinates of control points

// Program window size
int pw_width, pw_height;

int running_state;
// 0 --- Setting up control points.
// 1 --- Normal state.
// 2 --- Moving control point.

void binomialCoeffs(int n, int* c)//求二项式系数
{
	int k, j;
	for (k = 0; k <= n; k++)
	{
		c[k] = 1;
		for (j = n; j >= k + 1; j--)
			c[k] *= j;
		for (j = n - k; j >= 2; j--)
			c[k] /= j;
	}
}

void computerBezPt(float u, CPoint2D* bezPt, int nctrl, CPoint2D* ctrlPts, int* c)
//比例系数 点坐标  控制点数  控制点坐标 二项式系数
{
	int k, n = nctrl - 1;//u的多项式次数比控制点少一个
	float bez;
	bezPt->x = bezPt->y = 0.0;
	for (k = 0; k < nctrl; k++)
	{
		bez = c[k] * pow(u, k) * pow(1 - u, n - k);
		bezPt->x += ctrlPts[k].x * bez;
		bezPt->y += ctrlPts[k].y * bez;
	}
}
// Draw Bezier curve
void Draw_Bezier(int nctrl, CPoint2D* cp, int m)
// nctrl  --- Number of control points
// cp --- Array of control points
// m  --- Number of subdivision
{
	int i;
	float u, x, y;
	CPoint2D bez;
	int *c = new int[nctrl];
	binomialCoeffs(nctrl - 1, c);
	glBegin(GL_LINE_STRIP);
	glVertex2f(cp[0].x, cp[0].y);

	for (i = 0; i < m; ++i)
	{
		u = (float)i / (float)m;
		computerBezPt(u, &bez, nctrl, cp, c);
		glVertex2f(bez.x, bez.y);
	}
	glVertex2f(cp[nctrl - 1].x, cp[nctrl - 1].y);
	glEnd();
}
//使得点可见
void plot(int x, int y)
{
	glBegin(GL_POLYGON);
	glVertex2f(x + 2, y);
	glVertex2f(x, y + 2);
	glVertex2f(x, y - 2);
	glVertex2f(x - 2, y);
	glEnd();
}
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);//清缓存，
	for (int i = 0; i < ic_cp; i++)
	{
		plot(control_points[i].x, control_points[i].y);//先使点可见
	}
	glLineStipple(1, 0x0f0f);
	glBegin(GL_LINE_STRIP);//画点与点之间的连线
	for (int i = 0; i < ic_cp; i++)
	{
		glVertex2f(control_points[i].x, control_points[i].y);
	}
	glEnd();
	glLineStipple(1, 0xffff);//画Bezier曲线
	if (ic_cp == n_cp)
		Draw_Bezier(n_cp, control_points, 1000);
	glutSwapBuffers();
}

// Mouse callback function
void mouse_func(int button, int state, int x, int y)
{
	float dis;

	if (button == GLUT_LEFT_BUTTON)
	{
		if ((state == GLUT_DOWN) & (running_state == 0) & (ic_cp < n_cp))
		{
			control_points[ic_cp].x = x;
			control_points[ic_cp].y = pw_height - y;
			ic_cp++;
			if (ic_cp == n_cp)
				running_state = 1;
			glutPostRedisplay();
		}
		else if ((state == GLUT_DOWN) & (running_state == 1))
		{
			for (int i = 0; i < n_cp; i++)
			{
				dis = fabs((x - control_points[i].x) * (x - control_points[i].x) + (pw_height - y - control_points[i].y) * (pw_height - y - control_points[i].y));
				if (dis < 10)//当全部点点击后再点击的时候计算此点和之前的点的距离，如果小于10个像素的话，则说明要拖动原来的点
				{
					i_cp = i;
					running_state = 2;
					break;
				}
			}
		}
		else if ((state == GLUT_DOWN) & (running_state == 2))
		{
			control_points[i_cp].x = x;
			control_points[i_cp].y = pw_height - y;
			glutPostRedisplay();
		}
		else if ((state == GLUT_UP) & (running_state == 2))
		{
			running_state = 1;
		}
	}
}
// Mouse motion callback function
void motion_func(int x, int y)
{
	//与上一个循环的第二个elseif搭配移动点
	if (running_state == 2)
	{
		control_points[i_cp].x = x;
		control_points[i_cp].y = pw_height - y;
		glutPostRedisplay();
	}
}
// Initialization function
void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_LINE_STIPPLE);

}

// Reshape callback function
void reshape(int w, int h)
{
	pw_width = w;
	pw_height = h;

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, w, 0.0, h);
}

// Keyboard callback function
void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 27:
		exit(0);
	}
}

// Main program entrance
int main(int argc, char* argv[])
{
	// Input number of control points
	printf("Number of control points = ");
	scanf("%d", &n_cp);
	if (n_cp < 2) return 1;
	control_points = new CPoint2D[n_cp];
	running_state = 0;
	ic_cp = 0;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Bezier Curve");
	init();
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse_func);
	glutMotionFunc(motion_func);
	glutDisplayFunc(display);
	glutMainLoop();

	delete[] control_points;
	return 0;
}


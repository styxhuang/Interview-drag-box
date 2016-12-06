//By Ming Huang
#include <GL/glut.h>
#include <stdlib.h>
#include<math.h>
#include <iostream>

struct rxn_coord
{
	float x, y;  // initializor
	rxn_coord() { x = 0.0; y = 0.0; } // constructor
	rxn_coord(float _x, float _y) : x(_x), y(_y) {};
};
class box
{
public:
	rxn_coord pts[4]; // box structure
	box(); // initialize constructor
	box* setValue(int x, int y);
	void draw(box *sqr); // draw square
	rxn_coord mouse(int x, int y); // get mouse coordintaes
	box* drag(box *sqr, rxn_coord *mouse); // change points of square
};

// square constructor
box::box()
{
	pts[0] = rxn_coord(0.0, 0.0);
	pts[1] = rxn_coord(0.2, 0.0);
	pts[2] = rxn_coord(0.2, 0.2);
	pts[3] = rxn_coord(0.0, 0.2);
};

// draw function
void box::draw(box *sqr)
{
	// draw square fill
	int i;
	glColor3f(1.0, 0.2, 0.2);
	glBegin(GL_QUADS);
	for (i = 0; i < 4; ++i)
	{
		glVertex2f(sqr->pts[i].x, sqr->pts[i].y);
	}
	glEnd();
	glColor3f(1.0, 0.2, 0.2);
	glBegin(GL_QUADS);
	glVertex2f(0.6, 0.2);
	glVertex2f(0.6, 0.4);
	glVertex2f(0.8, 0.4);
	glVertex2f(0.8, 0.2);
	glEnd();
	// draw square points
	i = 0;
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POINTS);
	for (i = 0; i < 4; ++i)
	{
		glVertex2f(sqr->pts[i].x, sqr->pts[i].y);
	}
	glEnd();
}

// mouse function
rxn_coord box::mouse(int x, int y)
{
	int windowWidth = 400, windowHeight = 400;
	return rxn_coord(float(x) / windowWidth, 1.0 - float(y) / windowHeight);
}

// drag function
box* box::drag(box *sqr, rxn_coord *mouse)
{
	sqr->pts[0].x = mouse->x - 0.1;
	sqr->pts[0].y = mouse->y - 0.1;

	sqr->pts[1].x = mouse->x + 0.1;
	sqr->pts[1].y = mouse->y - 0.1;

	sqr->pts[3].x = mouse->x - 0.1;
	sqr->pts[3].y = mouse->y + 0.1;

	sqr->pts[2].x = mouse->x + 0.1;
	sqr->pts[2].y = mouse->y + 0.1;
	return sqr;
}

// GLOBAL

// create square object
box* sqr = new box;


// display at start
void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	sqr->draw(sqr);
	glFlush();
}

// drag function
void drag(int x, int y)
{
	// int x and y of mouse converts to screen coordinates
	// returns the point as mousePt
	rxn_coord mousePt = sqr->mouse(x, y);
	//create pointer to window point coordinates
	rxn_coord* mouse = &mousePt;
	// if the mouse is within the square
	printf("mouse=%f\n", mouse->x);
	if (mouse->x > sqr->pts[0].x && mouse->y > sqr->pts[0].y)
	{
		if (mouse->x < sqr->pts[2].x && mouse->y < sqr->pts[2].y)
		{
			// then drag by chaning square coordinates relative to mouse
			sqr->drag(sqr, mouse);
			if (mouse->x > 0.5 && mouse->x <0.9)
			{
				if (mouse->y > 0.1 &&mouse->y < 0.5)
				{
					sqr->setValue(0.5, 0.5);
					printf("Intention!\n");
				}
			}	
			glutPostRedisplay();
		}
	}
}
box* box::setValue(int x, int y)
{
	sqr->pts[0].x = x;
	sqr->pts[0].y = y;

	sqr->pts[1].x = x+0.2;
	sqr->pts[1].y = y;

	sqr->pts[2].x = x+0.2;
	sqr->pts[2].y = y+0.2;

	sqr->pts[3].x = x;
	sqr->pts[3].y = y+0.2;
	return sqr;
}

void Initialize() {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}

int main(int iArgc, char** cppArgv) {

	glutInit(&iArgc, cppArgv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("Move Box");
	glutMotionFunc(drag);
	Initialize();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
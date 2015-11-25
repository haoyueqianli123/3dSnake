/**
*Author :Tharindra Galahena
*Project:snake game openGL and c++
*Date   :19/02/2012
*/

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <GL/gl.h>
#include <GL/glut.h>


using namespace std;

typedef struct sq{
	int x;
	int y;
	int z;
	int mx;
	int my;
	int mz;
	struct sq *next;
} sq;

sq *snake;

int mx;
int my;
int mz;
int change_view_z = 0;

int fx = -6;
int fy = -6;
int fz = 0;
int sc = 0;
bool p = false;
bool color = true;


void add(int x, int y, int z){
	sq *tmp = (sq *)malloc(sizeof(sq));
	tmp -> x = x;
	tmp -> y = y;
	tmp -> z = z;
	tmp -> mx = 1;
	tmp -> my = 0;
	tmp -> mz = 0;
	tmp -> next = snake;
	snake = tmp;
}
void start(){
	snake = NULL;
	add(0, 0, 0);
	add(1, 0, 0);
	add(2, 0, 0);
	add(3, 0, 0);
	add(4, 0, 0);
	mx = 1;
	my = 0;
	mz = 0;
}
void set_f(){
	bool f = true;
	while(f){
		srand(time(NULL));
		fx = (rand() % 14) - 7;	 
		srand(time(NULL));
		fy = (rand() % 14) - 7;
		sq *p = snake;
		while(p != NULL){
			if(p -> x == fx && p -> y == fy && p -> z == fz){
				f = true;
				break;		
			}	
			f = false;
			p = p -> next;
		}	
	}
}

bool tail(){
	sq *p = snake;
	while(p -> next != NULL){
		if(p -> next -> x == snake -> x + mx && p -> next -> y == snake -> y + my
			&& p -> next -> z == snake -> z + mz)
			return true;	
		p = p -> next;
	}
	return false;
}
void rev(){
	sq *snake2 = NULL;
	sq *p = snake;
	while(p != NULL){
		sq *tmp = (sq *)malloc(sizeof(sq));
		tmp -> x = p -> x;
		tmp -> y = p -> y;
		tmp -> z = p -> z;
		tmp -> mx = -1 * p -> mx;
		tmp -> my = -1 * p -> my;
		tmp -> mz = -1 * p -> mz;
		tmp -> next = snake2;
		snake2 = tmp;
		sq *x = p -> next;
		free(p);
		p = x;	
	}
	snake = snake2;
	mx = snake -> mx;
	my = snake -> my;
	mz = snake -> mz;
}

void move(){
	sq *p = snake;
	int x = p -> x;
	int y = p -> y;
	int z = p -> z;
	int tmx = p -> mx;
	int tmy = p -> my;
	int tmz = p -> mz;
	while(p -> next != NULL){
		sq *q = p -> next;
		int tmp = q -> x;
		q -> x = x;
		x = tmp;

		tmp = q -> y;
		q -> y = y;
		y = tmp;

		tmp = q -> z;
		q -> z = z;
		z = tmp;

		tmp = q -> mx;
		q -> mx = tmx;
		tmx = tmp;

		tmp = q -> my;
		q -> my = tmy;
		tmy = tmp;

		tmp = q -> mz;
		q -> mz = tmz;
		tmz = tmp;

		p = p -> next;
	}
	snake -> mx = mx;
	snake -> my = my;
	snake -> mz = mz;
	snake -> x += mx;
	snake -> y += my;
	snake -> z += mz;
	if (snake -> y >= 7){
		snake -> y = -7;
	}
	if (snake -> y <= -8){
		snake -> y = 6;
	}

}



void drawmap(){
		glColor3f(0.5, 0.0, 100.0);
		// draw back face
		// glVertex3f(7, -7, -7);
		// glVertex3f(-7, -7,-7);
		// glVertex3f(-7, -7,7);
		// glVertex3f(7, -7, 7);
		for (int x = -7; x <= 7; x++) {
			glBegin(GL_LINE_LOOP);
			glVertex3f(x, -7, -7);
			glVertex3f(x, 7, -7);
			glEnd();
		}
		for (int x = -7; x <= 7; x++) {
			glBegin(GL_LINE_LOOP);
			glVertex3f(-7, x, -7);
			glVertex3f(7, x, -7);
			glEnd();
		}

	// 	// draw front face
	// 	glVertex3f(7, 7, -7);
	// 	glVertex3f(-7, 7, -7);
	// 	glVertex3f(-7, 7, 7);
	// 	glVertex3f(7, 7, 7);
		for (int x = -7; x <= 7; x++) {
			glBegin(GL_LINE_LOOP);
			glVertex3f(x, -7, 7);
			glVertex3f(x, 7, 7);
			glEnd();
		}
		for (int x = -7; x <= 7; x++) {
			glBegin(GL_LINE_LOOP);
			glVertex3f(-7, x, 7);
			glVertex3f(7, x, 7);
			glEnd();
		}

	// 	// draw left face
	// 	glVertex3f(-7, -7, -7);
	// 	glVertex3f(-7, 7, -7);
	// 	glVertex3f(-7, 7, 7);
	// 	glVertex3f(-7, -7, 7);
		for (int x = -7; x <= 7; x++) {
			glBegin(GL_LINE_LOOP);
			glVertex3f(-7, x, -7);
			glVertex3f(-7, x, 7);
			glEnd();
		}
		for (int x = -7; x <= 7; x++) {
			glBegin(GL_LINE_LOOP);
			glVertex3f(-7, -7, x);
			glVertex3f(-7, 7, x);
			glEnd();
		}

	// 	// draw right face
	// 	glVertex3f(7, -7, -7);
	// 	glVertex3f(7, 7, -7);
	// 	glVertex3f(7, 7, 7);
	// 	glVertex3f(7, -7, 7);
		for (int x = -7; x <= 7; x++) {
			glBegin(GL_LINE_LOOP);
			glVertex3f(7, x, -7);
			glVertex3f(7, x, 7);
			glEnd();
		}
		for (int x = -7; x <= 7; x++) {
			glBegin(GL_LINE_LOOP);
			glVertex3f(7, -7, x);
			glVertex3f(7, 7, x);
			glEnd();
		}

	// 	// draw top
	// 	glVertex3f(7, 7, -7);
	// 	glVertex3f(-7, 7, -7);
	// 	glVertex3f(-7, -7, -7);
	// 	glVertex3f(7, -7, -7);

	// 	// draw bottom
	// 	glVertex3f(7, 7, 7);
	// 	glVertex3f(-7, 7, 7);
	// 	glVertex3f(-7, -7, 7);
	// 	glVertex3f(7, -7, 7);

	// glEnd();

}




void par(float x1, float x2, float y1, float y2, float z1, float z2){
	glColor3f(1.0, 1.0, 1.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glBegin(GL_QUADS);
		// draw front face
		glVertex3f(x1, y2, z2);
		glVertex3f(x2, y2, z2);
		glVertex3f(x2, y2, z1);
		glVertex3f(x1, y2, z1);

		// draw back face
		glVertex3f(x1, y1, z2);
		glVertex3f(x2, y1, z2);
		glVertex3f(x2, y1, z1);
		glVertex3f(x1, y1, z1);

		// draw left face
		glVertex3f(x2, y2, z2);
		glVertex3f(x2, y1, z2);
		glVertex3f(x2, y1, z1);
		glVertex3f(x2, y2, z1);

		// draw right face
		glVertex3f(x1, y2, z2);
		glVertex3f(x1, y1, z2);
		glVertex3f(x1, y1, z1);
		glVertex3f(x1, y2, z1);

		// draw top
		glVertex3f(x1, y1, z2);
		glVertex3f(x2, y1, z2);
		glVertex3f(x2, y2, z2);
		glVertex3f(x1, y2, z2);

		// draw bottom
		glVertex3f(x1, y1, z1);
		glVertex3f(x2, y1, z1);
		glVertex3f(x2, y2, z1);
		glVertex3f(x1, y2, z1);

	glEnd();
	
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity ();
	glTranslatef(0.0, 0.0, -40.0);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glPushMatrix();

		glTranslatef(-0.3, 1.0, 0.0);
		glRotatef(-35.0, 1.0, 0.0, 0.0);

	int i;
	sq *p = snake;
	if (color) {
		glColor3f(0.5, 0.0, 100.0);	
	} else {
		glColor3f(1.0, 1.0, 1.0);
	}
	par(-8.7,  9.2,  9.0,  9.2, 0.0, 0.5);
	par(-8.7,  9.2, -8.5, -8.7, 0.0, 0.5);
	par(-8.5, -8.7, -8.7,  9.2, 0.0, 0.5);
	par( 9.2,  9.0, -8.7,  9.2, 0.0, 0.5);

		drawmap();
		glPushMatrix();
		


	while(p != NULL){
		par((p -> x),(p -> x) + 1,(p -> y),(p -> y) + 1, 7, 7.0);
		p = p -> next;	
	}
	par(fx, fx + 1 , fy , fy + 1, 7, 7.0);
	glutSwapBuffers();
	glPopMatrix();
	glPopMatrix();
}

void myIdleFunc(int a) {
	if(!p){
		if(tail()) start();
		else if(sc >= 30) {
			cout << "\n" << endl;
			cout << "you win!" << endl;	
			cout << "\n" << endl;
			exit(0);
		}else{
			if(snake -> x + mx == fx && snake -> y + my == fy){
				add(fx, fy, fz);	
				sc++;
				glColor3f(0.0, 0.0, 0.0);
				set_f();
			}
		}
		move();
		glutPostRedisplay();
	}
	glutTimerFunc(400, myIdleFunc, 0);
}
void keyboard(unsigned char key, int x, int y)
{
	if(key == 27) {		
		exit(0);	
	}else if((char)key == 'a'){
		if(!p){
			if(mx == 1) rev();
			else{
				mx = -1;
				my =  0;
				mz =  0;
			}	
		}
	}else if((char)key == 'd'){
		if(!p){
			if(mx == -1) rev();
			else{
				mx =  1;
				my =  0;
				mz =  0;
			}
		}
	}else if((char)key == 'w'){
		if(!p){
			if(my == -1) rev();
			else{
				mx =  0;
				my =  1;
				mz =  0;
			}
		}	
	}else if((char)key == 's'){
		if(!p){		
			if(my == 1) rev();
			else{
				mx =  0;
				my = -1;
				mz =  0;
			}
		}

	}else if((char)key == 'p'){
		if(p) p = false;
		else p = true;	
	}else if((char)key == 'z'){ //change color. and yes, I am that boring
		if (color) color = false;
		else color = true;
	}

}

void init()
{
	glClearColor(0.7f, 0.7f, 0.9f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);	
	glLoadIdentity ();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

	GLfloat acolor[] = {1.4, 1.4, 1.4, 1.0};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, acolor);

}
void Reshape(int w, int h)
{
    	glViewport(0, 0, w, h);
    	glMatrixMode(GL_PROJECTION); 
		glLoadIdentity();
		gluPerspective(45.0, (float)w/(float)h, 0.1, 200.0);
	
}
int main(int argc, char** argv)
{

	if(argc < 2){
		cout << "\n usage :\n\n ./snake 800x600\n" << endl;		
		return 0;
	}
	string s(argv[1]);
	s += string(":16@60");

	start();

	glutInit(&argc,argv);
	glutInitDisplayMode ( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutGameModeString(s.c_str());
	
	glutEnterGameMode();
	init();
	glutTimerFunc(400, myIdleFunc, 0);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc( keyboard );
	glutDisplayFunc(display);
	glPushMatrix();
		glColor3f(0.0, 0.0, 0.0);
		set_f();
	glPopMatrix();
	
	
	glutMainLoop();
	return 0;
}

#include <GL/glut.h>
#include <GL/freeglut.h>
#include <stdlib.h>
#include <windows.h>
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

int speed = 0;
int start = 0;
int size = 0;
int randx = 12;
int randy = 9;
int tile = 25;
int width = 600;
int height = 600;
int direction = 0;							// 0 = up
											// 1 = down
											// 2 = left
											// 3 = right
int easy_x = 250;
int easy_y = 300;
int easy_width = 100;
int easy_height = 50;

int medium_x = 250;
int medium_y = 200;
int medium_width = 100;
int medium_height = 50;

vector<int> xr;
vector<int> yr;
vector<int> xl;
vector<int> yl;

void draw(int x, int y, int width, int height, float r, float g, float b){
	glColor3f(r,g,b);

	glBegin(GL_QUADS);
	glVertex2f(x, y);
	glVertex2f(x + width, y);
	glVertex2f(x + width, y + height);
	glVertex2f(x, y+height);
	glEnd();
}

void menu(int button, int state, int x, int y){
	cout<<"x: "<<x<<endl;
	cout<<"y: "<<y<<endl;
	cout<<state<<endl;
	if((easy_x < x && easy_x + easy_width > x) && (easy_y > y && easy_y - easy_height < y)) {
	speed = 75;
	start = 1;
	}
	else if((medium_x < x && medium_x + medium_width > x) && (400 > y && 350 < y)){
	speed = 50;
	start = 1;
	cout<<"medium"<<endl;
	}

}

void spawnDot() {
	glColor3f(1,0,0);

	glBegin(GL_QUADS);
	glVertex2f(randx * tile, randy * tile);
	glVertex2f(randx * tile + 25, randy * tile);
	glVertex2f(randx * tile + 25, randy * tile + 25);
	glVertex2f(randx * tile, randy * tile + 25);
	glEnd();

}

void drawSegment(int i){
	glBegin(GL_QUADS);
	glVertex2f(0+xr[i], 0+yr[i]);
	glVertex2f(tile+xr[i], 0+yr[i]);
	glVertex2f(tile+xr[i], tile+yr[i]);
	glVertex2f(0+xr[i], tile+yr[i]);
	glEnd();
}

void drawLast(int i){
	glBegin(GL_QUADS);
	glVertex2f(0+xl[i], 0+yl[i]);
	glVertex2f(tile+xl[i], 0+yl[i]);
	glVertex2f(tile+xr[i], tile+yl[i]);
	glVertex2f(0+xl[i], tile+yl[i]);
	glEnd();
}


void specialkey(int key, int x, int y){
	printf("%d \n", key);

	switch(key){
		case GLUT_KEY_UP:
			direction = 0;
			break;
		case GLUT_KEY_DOWN:
			direction = 1;
			break;
		case GLUT_KEY_LEFT:
			direction = 2;
			break;
		case GLUT_KEY_RIGHT:
			direction = 3;
			break;
	}
}

void display(){
	
	if(xr[0] == randx * tile && yr[0] == randy * tile) {
		randx = rand()%24;				// collect
		randy = rand()%24;
		xr.push_back(xr[size]-25);
		yr.push_back(yr[size]);
		xl.push_back(xr[size]);
		yl.push_back(yr[size]);
		printf("IT WORKS!!! \n");
		size++;
		cout<<size<<endl;
	}

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.08,0.45,0.61);
	
	for(int j = 0;j <= size;j++){
		xl[j] = xr[j];
		yl[j] = yr[j];

	if(j!=0){	
		xr[j] = xl[j-1];
		yr[j] = yl[j-1];

	}
		drawSegment(j);

	} 

	spawnDot();
if(start == 0) {
	draw(easy_x, easy_y, easy_width, easy_height, 0.07, 0.61, 0.22);
	draw(medium_x, medium_y, medium_width, medium_height, 1, 0.31 ,0.07);
}
	glFlush();
	glutPostRedisplay();
	glutSwapBuffers();

	Sleep(speed);

	
if(start == 1){
	switch(direction){
		case 0:
			yr[0] += tile;
			glutPostRedisplay();
			break;
		case 1:
			yr[0] -= tile;
			glutPostRedisplay();
			break;
		case 2:
			xr[0] -= tile;
			glutPostRedisplay();
			break;
		case 3:
			xr[0] += tile;
			glutPostRedisplay();
			break;
	}
}
	if(yr[0]+tile > height || yr[0] < 0 || xr[0]+tile > width || xr[0] < 0){
			cout<<"Your score was: "<<size<<endl;
			exit(1);
	}
	for(int i = 2; i<=size; i++){
		if(xr[0] == xr[i] && yr[0] == yr[i]){
			cout<<"Your score was: "<<size<<endl;
			exit(1);
		}
	}

}

int main(int argc, char** argv){
	srand(time(NULL));
	
	xr.push_back(300);
	yr.push_back(200);
	xl.push_back(300);
	yl.push_back(200);

	printf("use array keys \n");
	printf("Blue - easy \n");
	printf("Red - hard \n");

	glutInit(& argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(width, height);
	glutCreateWindow("event handling");
	
	glutDisplayFunc(display);

	glClearColor(0.070, 0.88, 0.56, 0);
	gluOrtho2D(0.0,width,0.0,height);
	glutSpecialFunc(specialkey);
	glutMouseFunc(menu);
	glutMainLoop();

	return 0;
}

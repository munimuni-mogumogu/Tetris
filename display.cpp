#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <GL/freeglut.h>
#include "display.h"

int angle = 80;			//視野角
int angle_of_top = 1.0;

double azimuth = 0.0;
double elevation = 0.0;
ViewPoint viewpoint = {VIEW_DISTANCE, 0.0, 0.0};	//視点
MousePoint mousepoint;	//マウスの位置

void cube() {
	glPushMatrix();
	glColor3d(1.0, 0.0, 0.0);
	glutSolidCube(BLOCK_SIZE);
	glPopMatrix();
}

void Create_Block(bool block[MINO_WIDTH][MINO_HEIGHT]) {
	for(int i = 0; i < MINO_WIDTH; i++) {
		for(int j = 0; j < MINO_HEIGHT; j++){
			glPushMatrix();
			glTranslated(i * BLOCK_SIZE, j * BLOCK_SIZE, 0.0);
			if(block[i][j]) cube();
			glPopMatrix();
		}
	}
}

void Create_Board(bool block[TETRIS_WIDTH][TETRIS_HEIGHT]) {
	for(int i = 0; i < TETRIS_WIDTH; i++) {
		for(int j = 0; j < TETRIS_HEIGHT; j++){
			glPushMatrix();
			glTranslated(i * BLOCK_SIZE, j * BLOCK_SIZE, 0.0);
			if(block[i][j]) cube();
			glPopMatrix();
		}
	}
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(viewpoint.x, viewpoint.y, viewpoint.z,
			0.0, 0.0, 0.0,
			0.0, angle_of_top, 0.0);
	glPushMatrix();

	//描画！！
	bool check[3][3] = {{1.0, 0.0, 0.0},{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}};
	Create_Block(check);


	glPopMatrix();
	glutSwapBuffers();
}

void reshape(int w, int h) {
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(angle, WINDOW_WIDTH / WINDOW_HEIGHT, 0.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void mouse(int b, int s, int x, int y) {
	switch(b) {
	case GLUT_LEFT_BUTTON:
		mousepoint.x = x;
		mousepoint.y = y;
		break;
	case GLUT_RIGHT_BUTTON:
		break;
	}
}

void keyboard(unsigned char k, int x, int y) {
	switch(k) {
	case 'z':
		break;
	default:
		break;
	}
}

void specialkeyboard(int k, int x, int y) {
	switch(k) {
	case GLUT_KEY_UP:
		break;
	default:
		break;
	}
}

void motion(int x, int y) {
	azimuth += (double)(x - mousepoint.x) / WINDOW_WIDTH * M_PI * 2;
	elevation += (double)(y - mousepoint.y) / WINDOW_HEIGHT * M_PI * 2;
	if(elevation > M_PI / 3 ) elevation = M_PI / 3;
	else if(elevation < -M_PI / 3) elevation = -M_PI / 3;

	viewpoint.x = -VIEW_DISTANCE * cos(elevation) * cos(azimuth);
	viewpoint.y = VIEW_DISTANCE * sin(elevation);
	viewpoint.z = VIEW_DISTANCE * cos(elevation) * sin(azimuth);
	std::cout << viewpoint.x << ", " << viewpoint.y << ", " << viewpoint.z << std::endl;
	mousepoint.x = x;
	mousepoint.y = y;
}

void initgl() {
	// 背景色
	glClearColor(1.0, 1.0, 1.0, 0.0);
	// デプスバッファ有効
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);

	/*
	//光源の設定
	GLfloat lpos0[4] = { 10.0, 10.0, 10.0, 1.0 };
	GLfloat lcol0[4] = { 1.0, 1.0, 1.0, 1.0 };
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, lpos0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lcol0);
	*/

	glEnable(GL_CULL_FACE);
	
}

void timer(int value) {
	glutPostRedisplay();
	glutTimerFunc(16, timer, 0);
}

void funcgroup() {
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialkeyboard);
	glutTimerFunc(16, timer, 0);
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("TETRIS");
	funcgroup();
	initgl();
	glutMainLoop();

	return 0;
}
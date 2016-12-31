#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <GL/freeglut.h>
#include "display.h"
#include "draw_str.h"
#include "tetris.h"

int angle = 80;			//視野角
GLfloat angle_of_top = 1.0;

int view_distance = 300;

double azimuth = 0.0;
double elevation = 0.0;
Point2 mousepoint = {0, 0};					//マウスの位置
Point3 viewpoint = {0, 0, view_distance};	//視点
Point3 center = {(BOARD_WIDTH + MENU_SIZE) / 2 * BLOCK_SIZE, BOARD_HEIGHT / 2 * BLOCK_SIZE, 0};	//全体の中心

Tetrimino tetrimino;
Board board;

void cube(GLdouble Red, GLdouble Green, GLdouble Blue) {
	glPushMatrix();
	glColor3d(Red, Green, Blue);
	glutSolidCube(BLOCK_SIZE);
	glPopMatrix();
}

void Create_Block(bool block[MINO_WIDTH][MINO_HEIGHT]) {
	for(int i = 0; i < MINO_WIDTH; i++) {
		for(int j = 0; j < MINO_HEIGHT; j++){
			glPushMatrix();
			glTranslated(i * BLOCK_SIZE, j * BLOCK_SIZE, 0.0);
			if(block[i][j]) cube(1.0, 0.0, 0.0);
			glPopMatrix();
		}
	}
}

void Create_Board(bool block[BOARD_WIDTH][BOARD_HEIGHT]) {
	for(int i = 0; i < BOARD_WIDTH; i++) {
		for(int j = 0; j < BOARD_HEIGHT; j++){
			glPushMatrix();
			glTranslated(i * BLOCK_SIZE, j * BLOCK_SIZE, 0.0);
			if(block[i][j]) cube(0.0, 0.0, 0.0);
			glPopMatrix();
		}
	}
}

void Get_Mino(bool ret_block[MINO_WIDTH][MINO_HEIGHT], bool* block) {
	for (int i = 0; i < MINO_WIDTH; i++) {
		for (int j = 0; j < MINO_HEIGHT; j++) {
			ret_block[i][j] = block[i * BOARD_HEIGHT + j];
		}
	}
}

void Get_Board(bool ret_board[BOARD_WIDTH][BOARD_HEIGHT], bool* board) {
	for (int i = 0; i < BOARD_WIDTH; i++) {
		for (int j = 0; j < BOARD_HEIGHT; j++) {
			ret_board[i][j] = board[i * BOARD_HEIGHT + j];
		}
	}
}

void draw_information(int score, int line) {
	glPushMatrix();
	draw_str score_name("score");
	glTranslated((BOARD_WIDTH + 1) * BLOCK_SIZE, (BOARD_HEIGHT - 2) * BLOCK_SIZE, 0);
	glScaled(2, 2, 0);
	score_name.draw_block();
	glPopMatrix();
	
	glPushMatrix();
	char char_score = static_cast<char>(score);
	draw_str draw_score(char_score);
	glTranslated((BOARD_WIDTH + 1) * BLOCK_SIZE, (BOARD_HEIGHT - 4) * BLOCK_SIZE, 0);
	//draw_score.draw_block();
	glPopMatrix();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(viewpoint.x + center.x, viewpoint.y + center.y, viewpoint.z + center.z,
			center.x, center.y, center.z,
			0.0, angle_of_top, 0.0);
	glPushMatrix();
	
	bool draw_board[BOARD_WIDTH][BOARD_HEIGHT];
	board.init();
	Get_Board(draw_board, board.getBoard());
	Create_Board(draw_board);

	draw_information(10, 10);

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
	
	viewpoint.x = -view_distance * cos(elevation) * sin(azimuth);
	viewpoint.y = view_distance * sin(elevation);
	viewpoint.z = view_distance * cos(elevation) * cos(azimuth);
	//std::cout << viewpoint.x << ", " << viewpoint.y << ", " << viewpoint.z << std::endl;
	mousepoint.x = x;
	mousepoint.y = y;
}

void MouseWheel(int wheel_number, int direction, int x, int y)
{
	view_distance -= direction * 2;
	glutPostRedisplay();
}

void init() {
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
	glutTimerFunc(value, timer, 16);
}

void funcgroup() {
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialkeyboard);
	glutMotionFunc(motion);
	glutMouseWheelFunc(MouseWheel);
	glutTimerFunc(16, timer, 0);
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("TETRIS");
	funcgroup();
	init();
	glutMainLoop();

	return 0;
}
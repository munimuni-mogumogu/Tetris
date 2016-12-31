#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <GL/freeglut.h>
#include <time.h>
#include "display.h"
#include "draw_str.h"
#include "tetris.h"

int angle = 80;			//����p
GLfloat angle_of_top = 1.0;

int view_distance = 300;

double azimuth = 0.0;
double elevation = 0.0;
bool view_check = true;
bool reset_check = true;
Point2 mousepoint = {0, 0};					//�}�E�X�̈ʒu
Point3 viewpoint = {0, 0, view_distance};	//���_
Point3 center = {(BOARD_WIDTH + MENU_SIZE) / 2 * BLOCK_SIZE, BOARD_HEIGHT / 2 * BLOCK_SIZE, 0};	//�S�̂̒��S
clock_t start = clock();
Tetrimino tetrimino;
Tetrimino nextmino;
Board board;

void View_reset() {
	reset_check = false;
	view_distance = 300;
	azimuth = 0.0;
	elevation = 0.0;
	mousepoint.x = 0; mousepoint.y = 0;
	viewpoint.x = 0; viewpoint.y = 0; viewpoint.z = view_distance;
	center.x = (BOARD_WIDTH + MENU_SIZE) / 2 * BLOCK_SIZE; center.y = BOARD_HEIGHT / 2 * BLOCK_SIZE; center.z = 0;
}

void Tetris_reset() {
	start = clock();
	board.init();
}

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

void Tetris_Main() {
	if(clock() - start > 1000) {
		start = clock();
		tetrimino.translate(0, -1, &board);
	}
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(viewpoint.x + center.x, viewpoint.y + center.y, viewpoint.z + center.z,
		center.x, center.y, center.z,
		0.0, angle_of_top, 0.0);
	glPushMatrix();

	Tetris_Main();
	Create_Board(board.getBoard().board);
	draw_information(10, 10);
	glPushMatrix();
	glTranslated(tetrimino.getX() * BLOCK_SIZE, tetrimino.getY() * BLOCK_SIZE, 0);
	Create_Block(tetrimino.getMino().mino);
	glPopMatrix();

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
		mousepoint.x = x;
		mousepoint.y = y;
		if(view_check) view_check = false;
		else view_check = true;
		break;
	}
}

void keyboard(unsigned char k, int x, int y) {
	switch(k) {
	case 'r':
		Tetris_reset();
		View_reset();
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
	if(view_check) {
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
	} else {
		center.x += x - mousepoint.x;
		center.y += y - mousepoint.y;
		mousepoint.x = x;
		mousepoint.y = y;
	}
}

void MouseWheel(int wheel_number, int direction, int x, int y)
{
	view_distance -= direction * 2;
	std::cout << view_distance << std::endl;
	glutPostRedisplay();
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

void init() {
	// �w�i�F
	glClearColor(1.0, 1.0, 1.0, 0.0);
	// �f�v�X�o�b�t�@�L��
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);

	/*
	//�����̐ݒ�
	GLfloat lpos0[4] = { 10.0, 10.0, 10.0, 1.0 };
	GLfloat lcol0[4] = { 1.0, 1.0, 1.0, 1.0 };
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, lpos0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lcol0);
	*/

	glEnable(GL_CULL_FACE);
}

void tetris_init() {
	board.init();
	tetrimino.create();
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("TETRIS");
	funcgroup();
	init();
	tetris_init();
	glutMainLoop();

	return 0;
}
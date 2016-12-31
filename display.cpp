#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <GL/freeglut.h>
#include <time.h>
#include "display.h"
#include "draw_str.h"
#include "tetris.h"

int angle = 80;			//視野角
int menu = 0;
GLfloat angle_of_top = 1.0;
int view_distance = 200;
double azimuth = 0.0;
double elevation = 0.0;
bool view_check = true;
bool reset_check = true;
Point2 mousepoint = {0, 0};					//マウスの位置
Point3 viewpoint = {0, 0, view_distance};	//視点
Point3 center = {(BOARD_WIDTH + MENU_SIZE) / 2 * BLOCK_SIZE, BOARD_HEIGHT / 2 * BLOCK_SIZE, 0};	//全体の中心
clock_t start = clock();
TmpPoint mino_pos;
TmpPoint holdmino_pos;
Tetrimino tetrimino;
Tetrimino nextmino;
bool hold_check = true;
Tetrimino holdmino;
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

void tetris_init() {
	board.init();
	tetrimino.create();
	mino_pos.x = BOARD_WIDTH / 2;
	mino_pos.y = BOARD_HEIGHT - 2;
	holdmino_pos.x = BOARD_WIDTH + 2;
	holdmino_pos.y = 7;
	tetrimino.setPoint(mino_pos);
	holdmino.setPoint(holdmino_pos);
	nextmino.create();
	start = clock();
}

void cube(GLdouble Red, GLdouble Green, GLdouble Blue) {
	glPushMatrix();
	glColor3d(Red, Green, Blue);
	glutSolidCube(BLOCK_SIZE);
	glPopMatrix();
}

void Create_Block(bool block[MINO_HEIGHT][MINO_WIDTH]) {
	for(int i = 0; i < MINO_HEIGHT; i++) {
		for(int j = 0; j < MINO_WIDTH; j++){
			glPushMatrix();
			glTranslated(j * BLOCK_SIZE, i * BLOCK_SIZE, 0.0);
			if(block[i][j]) cube(1.0, 0.0, 0.0);
			glPopMatrix();
		}
	}
}

void Create_Board(bool block[BOARD_HEIGHT][BOARD_WIDTH]) {
	for(int i = 0; i < BOARD_HEIGHT; i++) {
		for(int j = 0; j < BOARD_WIDTH; j++){
			glPushMatrix();
			glTranslated(j * BLOCK_SIZE, i * BLOCK_SIZE, 0.0);
			if(block[i][j]) {
				glColor4d(0, 0, 0, 0.4);
				glutSolidCube(BLOCK_SIZE);
			}
			glPopMatrix();
		}
	}
}

void Title() {
	glPushMatrix();
	draw_str Title_str("tetris");
	glTranslated(0,  BOARD_HEIGHT / 2 * BLOCK_SIZE, 0);
	glScaled(6, 6, 6);
	Title_str.draw_block();
	glPopMatrix();
	
	glPushMatrix();
	draw_str Start_str("please push enter");
	glTranslated(BLOCK_SIZE, (BOARD_HEIGHT / 2 - 4) * BLOCK_SIZE, 0);
	glScaled(2, 2, 2);
	Start_str.draw_block();
	glPopMatrix();
}

void draw_information(int score, int line) {
	glPushMatrix();
	draw_str score_str("score");
	glTranslated((BOARD_WIDTH + 1) * BLOCK_SIZE, (BOARD_HEIGHT - 2) * BLOCK_SIZE, 0);
	glScaled(2, 2, 0);
	score_str.draw_block();
	glPopMatrix();

	glPushMatrix();
	draw_str draw_score(score);
	glTranslated((BOARD_WIDTH + 1) * BLOCK_SIZE, (BOARD_HEIGHT - 4) * BLOCK_SIZE, 0);
	glScaled(2, 2, 0);
	draw_score.draw_block();
	glPopMatrix();

	glPushMatrix();
	draw_str line_str("line");
	glTranslated((BOARD_WIDTH + 1) * BLOCK_SIZE, (BOARD_HEIGHT - 6) * BLOCK_SIZE, 0);
	glScaled(2, 2, 0);
	line_str.draw_block();
	glPopMatrix();

	glPushMatrix();
	draw_str draw_line(line);
	glTranslated((BOARD_WIDTH + 1) * BLOCK_SIZE, (BOARD_HEIGHT - 8) * BLOCK_SIZE, 0);
	glScaled(2, 2, 0);
	draw_line.draw_block();
	glPopMatrix();

	glPushMatrix();
	draw_str hold_str("hold");
	glTranslated((BOARD_WIDTH + 1) * BLOCK_SIZE, (BOARD_HEIGHT - 11) * BLOCK_SIZE, 0);
	glScaled(2, 2, 0);
	hold_str.draw_block();
	glPopMatrix();

	glPushMatrix();
	glTranslated(holdmino.getX() * BLOCK_SIZE, holdmino.getY() * BLOCK_SIZE, 0);
	Create_Block(holdmino.getMino().mino);
	glPopMatrix();

	glPushMatrix();
	draw_str next_str("next");
	glTranslated((BOARD_WIDTH + 1) * BLOCK_SIZE, 4 * BLOCK_SIZE, 0);
	glScaled(2, 2, 0);
	next_str.draw_block();
	glPopMatrix();

	glPushMatrix();
	glTranslated(nextmino.getX() * BLOCK_SIZE, nextmino.getY() * BLOCK_SIZE, 0);
	Create_Block(nextmino.getMino().mino);
	glPopMatrix();
}

void Next_Mino_set() {
	tetrimino.setMino(nextmino.getMino());
	nextmino.create();
	tetrimino.setPoint(mino_pos);
}


void Mino_hold() {
	hold_check = false;
	TmpMino temp = holdmino.getMino();
	if(temp.mino[1][1] == false) {
		holdmino.setMino(tetrimino.getMino());
		Next_Mino_set();
	} else {
		holdmino.setMino(tetrimino.getMino());
		tetrimino.setMino(temp);
		tetrimino.setPoint(mino_pos);
	}
}

void Tetris_Main() {
	glPushMatrix();

	glPushMatrix();
	glTranslated(tetrimino.getX() * BLOCK_SIZE, tetrimino.getY() * BLOCK_SIZE, 0);
	Create_Block(tetrimino.getMino().mino);
	glPopMatrix();

	glPopMatrix();
	if(clock() - start > 1000) {
		start = clock();
		if(tetrimino.translate(0, -1, &board)) {
			hold_check = true;
			Next_Mino_set();
		}
	}
	Create_Board(board.getBoard().board);
	draw_information(6250, 120);
	if(board.boardCheck()) exit(0);
	glPopMatrix();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(viewpoint.x + center.x, viewpoint.y + center.y, viewpoint.z + center.z,
		center.x, center.y, center.z,
		0.0, angle_of_top, 0.0);

	if(menu == 0) Title();
	else if(menu == 1) Tetris_Main();

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
	case GLUT_KEY_ENTER:
		menu = 1;
		tetris_init();
		break;
	case 'v':
		View_reset();
		break;
	case 'r':
		menu = 0;
		break;
	case 'z':
		tetrimino.rotate(1);
		break;
	case 'x':
		tetrimino.rotate(0);
		break;
	case 'a':
		if(hold_check) Mino_hold();
		break;
	default:
		break;
	}
}

void specialkeyboard(int k, int x, int y) {
	switch(k) {
	case GLUT_KEY_RIGHT:
		tetrimino.translate(1, 0, &board);
		break;
	case GLUT_KEY_LEFT:
		tetrimino.translate(-1, 0, &board);
		break;
	case GLUT_KEY_DOWN:
		if(tetrimino.translate(0, -1, &board)) {
			hold_check = true;
			Next_Mino_set();
		}
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
		center.x -= x - mousepoint.x;
		center.y += y - mousepoint.y;
		std::cout << center.x << ", " << center.y << ", " << center.z << std::endl;
		mousepoint.x = x;
		mousepoint.y = y;
	}
}

void MouseWheel(int wheel_number, int direction, int x, int y)
{
	view_distance -= direction * 2;
	//std::cout << view_distance << std::endl;
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
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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
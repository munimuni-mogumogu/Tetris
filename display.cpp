#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <GL/freeglut.h>
#include <time.h>
#include <fstream>
#include "display.h"
#include "draw_str.h"
#include "tetris.h"

int angle = 80;			//����p
int mode = 0;			//gamemode
GLfloat angle_of_top = 1.0;	//��ʂ̏�̐ݒ�(1 : �オy�̐�, -1 : ����y�̐�)
int view_distance = 200;	//���_���璆�_�̋���
double azimuth = 0.0;		//���ʊp
double elevation = 0.0;		//�p
bool view_check = true;		//���_�ړ��̏������p�ϐ�
bool reset_check = true;	//�e�g���X�̃��Z�b�g�p�ϐ�
Point2 mousepoint = {0, 0};		//�}�E�X�̈ʒu
Point3 viewpoint = {0, 0, view_distance};	//���_
Point3 center = {(BOARD_WIDTH + MENU_SIZE) / 2 * BLOCK_SIZE, BOARD_HEIGHT / 2 * BLOCK_SIZE, 0};	//�S�̂̒��S
clock_t start = clock();	//���Ԍo�߂̊Ǘ��p
TmpPoint mino_pos;			//�e�g���~�m�̈ʒu
Tetrimino tetrimino;		//�e�g���~�m
Tetrimino nextmino;			//���̃e�g���~�m
bool hold_check = true;		//�z�[���h�������p�ϐ�
TmpPoint holdmino_pos;		//�z�[���h�̈ʒu
Tetrimino holdmino;			//�z�[���h�̃e�g���~�m
TmpPoint forecastmino_pos;	//���n�_�\�z�ʒu
Tetrimino forecastmino;		//���n�_�̃e�g���~�m
Board board;				//�{�[�h
int rank_pos = -1;			//�����L���O�̏���
Point2 ranking[10];			//�����L���O�i�[�p�̕ϐ�
int title_pos = 0;			//�^�C�g���̈ʒu
Score score;				//�X�R�A
double speed = 1000;		//�������x(ms)

//���_�̃��Z�b�g
void View_reset() {
	reset_check = false;
	view_distance = 200;
	azimuth = 0.0;
	elevation = 0.0;
	mousepoint.x = 0; mousepoint.y = 0;
	viewpoint.x = 0; viewpoint.y = 0; viewpoint.z = view_distance;
	center.x = (BOARD_WIDTH + MENU_SIZE) / 2 * BLOCK_SIZE; center.y = BOARD_HEIGHT / 2 * BLOCK_SIZE; center.z = 0;
}

//�����L���O���e�L�X�g�t�@�C������ǂݏo���A�X�R�A�Ə��������C������ۑ�����
//�z��փX�R�A�̍~�����i�[����
void setRanking(int score, int line) {
	rank_pos = -1;
	std::ifstream fin("ranking.txt");
	if(fin.fail()) {
		std::cerr << "Error : Cannot open file" << std::endl;
	}
	for(int i = 0; i < 10; i++)
		fin >> ranking[i].x >> ranking[i].y;
	fin.close();

	Point2 temp1 = {score, line};
	Point2 temp2;
	for(int i = 0; i < 10; i++) {
		if(ranking[i].x < temp1.x) {
			if(rank_pos == -1) rank_pos = i;
			temp2.x = ranking[i].x; temp2.y = ranking[i].y;
			ranking[i].x = temp1.x; ranking[i].y = temp1.y;
			temp1.x = temp2.x; temp1.y = temp2.y;
		}else if(ranking[i].x == temp1.x) {
			if(ranking[i].y < temp1.y) {
				if(rank_pos == -1) rank_pos = i;
				temp2.x = ranking[i].x; temp2.y = ranking[i].y;
				ranking[i].x = temp1.x; ranking[i].y = temp1.y;
				temp1.x = temp2.x; temp1.y = temp2.y;
			}
		}
	}

	std::ofstream fout("ranking.txt");
	if(fout.fail()) {
		std::cerr << "Error : Cannot open file" << std::endl;
	}
	for(int i = 0; i < 10; i++) {
		fout << ranking[i].x << " " << ranking[i].y << std::endl;
	}
	fout.close();
}

//�e�g���X�̏��������s�Ȃ�
void tetris_init() {
	board.init();
	tetrimino.create();
	holdmino = Tetrimino();
	mino_pos.x = BOARD_WIDTH / 2;
	mino_pos.y = BOARD_HEIGHT - 2;
	holdmino_pos.x = BOARD_WIDTH + 2;
	holdmino_pos.y = 7;
	tetrimino.setPoint(mino_pos);
	holdmino.setPoint(holdmino_pos);
	nextmino.create();
	start = clock();
	rank_pos = -1;
	setRanking(0, 0);
	title_pos = 0;
	score.clear();
}

//RGB�̐F�̎l�p�`��`��
void cube(GLdouble Red = 0, GLdouble Green = 0, GLdouble Blue = 0, GLdouble shadow = 1) {
	glPushMatrix();
	glColor4d(Red, Green, Blue, shadow);
	glutSolidCube(BLOCK_SIZE);
	glPopMatrix();
}

//3�~3�̔z��̃u���b�N��`��
void Create_Block(bool block[MINO_HEIGHT][MINO_WIDTH], GLdouble Red = 0, GLdouble Green = 0, GLdouble Blue = 0, GLdouble shadow = 1) {
	for(int i = 0; i < MINO_HEIGHT; i++) {
		for(int j = 0; j < MINO_WIDTH; j++){
			glPushMatrix();
			glTranslated(j * BLOCK_SIZE, i * BLOCK_SIZE, 0.0);
			if(block[i][j]) cube(Red, Green, Blue, shadow);
			glPopMatrix();
		}
	}
}

//22�~11�̔z��̃u���b�N��`��
void Create_Board(bool block[BOARD_HEIGHT][BOARD_WIDTH]) {
	for(int i = 0; i < BOARD_HEIGHT; i++) {
		for(int j = 0; j < BOARD_WIDTH; j++){
			glPushMatrix();
			glTranslated(j * BLOCK_SIZE, i * BLOCK_SIZE, 0.0);
			if(block[i][j]) {
				if(i == 0 || j == 0 || j == BOARD_WIDTH - 1) {
					glColor4d(board.getBoard().red[i][j], board.getBoard().green[i][j], board.getBoard().blue[i][j], 0.4);
				} else {
					glColor3d(board.getBoard().red[i][j], board.getBoard().green[i][j], board.getBoard().blue[i][j]);
				}
				glutSolidCube(BLOCK_SIZE);
			}
			glPopMatrix();
		}
	}
}

//�^�C�g���̕`��
void Title() {

	glPushMatrix();
	glTranslated((BOARD_WIDTH / 6 - 1) * BLOCK_SIZE, (BOARD_HEIGHT / 2 - 3 - (title_pos * 2)) * BLOCK_SIZE - 6, 0);
	glColor3d(1, 0, 0);
	glutSolidSphere(5, 5, 5);
	glPopMatrix();
	glPushMatrix();

	draw_str Title_str("tetris");
	glTranslated(0,  BOARD_HEIGHT / 2 * BLOCK_SIZE, 0);
	glScaled(6, 6, 6);
	Title_str.draw_block();
	glPopMatrix();

	glPushMatrix();
	draw_str Start_str("start tetris");
	glTranslated(BOARD_WIDTH / 6 * BLOCK_SIZE, (BOARD_HEIGHT / 2 - 4) * BLOCK_SIZE, 0);
	glScaled(2, 2, 2);
	Start_str.draw_block();
	glPopMatrix();

	glPushMatrix();
	draw_str ranking_str("ranking");
	glTranslated(BOARD_WIDTH / 6 * BLOCK_SIZE, (BOARD_HEIGHT / 2 - 6) * BLOCK_SIZE, 0);
	glScaled(2, 2, 2);
	ranking_str.draw_block();
	glPopMatrix();
}

//�e�g���X���̏��̕`��
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
	Create_Block(holdmino.getMino().mino, holdmino.getR(), holdmino.getG(), holdmino.getB());
	glPopMatrix();

	glPushMatrix();
	draw_str next_str("next");
	glTranslated((BOARD_WIDTH + 1) * BLOCK_SIZE, 4 * BLOCK_SIZE, 0);
	glScaled(2, 2, 0);
	next_str.draw_block();
	glPopMatrix();

	glPushMatrix();
	glTranslated(nextmino.getX() * BLOCK_SIZE, nextmino.getY() * BLOCK_SIZE, 0);
	Create_Block(nextmino.getMino().mino, nextmino.getR(), nextmino.getG(), nextmino.getB());
	glPopMatrix();
}

//���̃e�g���~�m�̐ݒ�
void Next_Mino_set() {
	tetrimino.setMino(nextmino.getMino());
	tetrimino.setColor(nextmino.getR(), nextmino.getG(),nextmino.getB());
	nextmino.create();
	tetrimino.setPoint(mino_pos);
}

//�z�[���h�~�m�̐ݒ�
void Mino_hold() {
	hold_check = false;
	TmpMino temp = holdmino.getMino();
	int color[3] = { holdmino.getR(), holdmino.getG(), holdmino.getB() };
	if(temp.mino[1][1] == false) {
		holdmino.setMino(tetrimino.getMino());
		holdmino.setColor(tetrimino.getR(), tetrimino.getG(), tetrimino.getB());
		Next_Mino_set();
	} else {
		holdmino.setMino(tetrimino.getMino());
		holdmino.setColor(tetrimino.getR(), tetrimino.getG(), tetrimino.getB());
		tetrimino.setMino(temp);
		tetrimino.setColor(color[0], color[1], color[2]);
		tetrimino.setPoint(mino_pos);
	}
}

//�e�g���X�̃��C�����[�v
void Tetris_Main() {
	glPushMatrix();

	glPushMatrix();
	glTranslated(tetrimino.getX() * BLOCK_SIZE, tetrimino.getY() * BLOCK_SIZE, 0);
	Create_Block(tetrimino.getMino().mino, tetrimino.getR(), tetrimino.getG(), tetrimino.getB());
	glPopMatrix();

	forecastmino.setMino(tetrimino.getMino());
	forecastmino_pos = tetrimino.getXY();
	forecastmino.setPoint(forecastmino_pos);
	while(!forecastmino.translate(0, -1, true, &board));

	glPushMatrix();
	glTranslated(forecastmino.getX() * BLOCK_SIZE, forecastmino.getY() * BLOCK_SIZE, 0);
	Create_Block(forecastmino.getMino().mino, 1.0, 0, 0, 0.4);
	glPopMatrix();

	glPopMatrix();

	speed = 1000 * pow(0.9, score.getLine() / 1);

	if(clock() - start > speed) {
		start = clock();
		if(tetrimino.translate(0, -1, false, &board)) {
			hold_check = true;
			Next_Mino_set();
		}
	}

	draw_information(score.getScore(), score.getLine());
	Create_Board(board.getBoard().board);
	if(board.boardCheck(score)) {
		mode = 2;
	}
	glPopMatrix();
}

//�Q�[���I�[�o�[�̏���
void drawGameOver() {
	Create_Board(board.getBoard().board);
	draw_information(score.getScore(), score.getLine());

	draw_str gameover_str("gameover", 1, 0, 0);
	glPushMatrix();
	glTranslated((BOARD_WIDTH + MENU_SIZE - 18) / 2 * BLOCK_SIZE, BOARD_HEIGHT / 2 * BLOCK_SIZE, 30);
	glScaled(4, 4, 4);
	gameover_str.draw_block();
	glPopMatrix();

	draw_str end_str("please push enter", 1, 0, 0);
	glPushMatrix();
	glTranslated((BOARD_WIDTH + MENU_SIZE - 19) / 2 * BLOCK_SIZE, (BOARD_HEIGHT - 4) / 2 * BLOCK_SIZE, 30);
	glScaled(2, 2, 2);
	end_str.draw_block();
	glPopMatrix();
}

//�����L���O�̕`��
void drawRanking() {
	draw_str rank("rank");
	draw_str score("score");
	draw_str line("line");
	draw_str name("name");
	glPushMatrix();
	glTranslated((BOARD_WIDTH - 16) * BLOCK_SIZE, (BOARD_HEIGHT + 2) * BLOCK_SIZE, 0);
	glScaled(1.5, 1.5, 1.5);
	rank.draw_block();
	glTranslated(4 * BLOCK_SIZE , 0, 0);
	score.draw_block();
	glTranslated(6 * BLOCK_SIZE , 0, 0);
	line.draw_block();
	glTranslated(4 * BLOCK_SIZE, 0, 0);
	name.draw_block();
	glPopMatrix();

	draw_str ranking_str[10][3];
	for(int i = 0; i < 10; i++) {
		Point3 color = {0, 0, 0};
		if(rank_pos == i) color.x = 1;
		glPushMatrix();
		glTranslated((BOARD_WIDTH - 16) * BLOCK_SIZE, (BOARD_HEIGHT - i * 2) * BLOCK_SIZE, 0);
		glScaled(1.5, 1.5, 1.5);
		ranking_str[i][0].set_str(i + 1, color.x, color.y, color.z);
		ranking_str[i][0].draw_block();

		glTranslated(4 * BLOCK_SIZE, 0, 0);
		ranking_str[i][1].set_str(ranking[i].x, color.x, color.y, color.z);
		ranking_str[i][1].draw_block();

		glTranslated(6 * BLOCK_SIZE, 0, 0);
		ranking_str[i][2].set_str(ranking[i].y, color.x, color.y, color.z);
		ranking_str[i][2].draw_block();
		glPopMatrix();
	}

	glPushMatrix();
	glTranslated(-BLOCK_SIZE, 0, 0);
	draw_str please("please push r key", 1, 0, 0);
	glScaled(2.0, 2.0, 2.0);
	please.draw_block();
	glPopMatrix();
}

//�`��̃��C���֐�
void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(viewpoint.x + center.x, viewpoint.y + center.y, viewpoint.z + center.z,
		center.x, center.y, center.z,
		0.0, angle_of_top, 0.0);

	if(mode == 0) Title();
	else if(mode == 1) Tetris_Main();
	else if(mode == 2) drawGameOver();
	else if(mode == 3) drawRanking();

	glutSwapBuffers();
}

//MatrixMode�̐ݒ�
void reshape(int w, int h) {
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(angle, WINDOW_WIDTH / WINDOW_HEIGHT, 0.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

//�}�E�X�̃N���b�N����
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

//�L�[�{�[�h����
void keyboard(unsigned char k, int x, int y) {
	switch(k) {
	case GLUT_KEY_ENTER:
		if(mode == 0){
			if(title_pos == 0) {
				mode = 1;
				tetris_init();
			} else if(title_pos == 1) {
				mode = 3;
			}
		} else if(mode == 2) {
			setRanking(score.getScore(), score.getLine());
			mode = 3;
		}
		break;
	case 'v':
		View_reset();
		break;
	case 'r':
		tetris_init();
		mode = 0;
		break;
	case 'z':
		if(mode == 1) tetrimino.rotate(1, &board);
		break;
	case 'x':
		if(mode == 1) tetrimino.rotate(0, &board);
		break;
	case 'a':
		if(mode == 1) {
			if(hold_check) Mino_hold();
		}
		break;
	default:
		break;
	}
}

//���L�[�Ȃǂ̓���L�[�{�[�h�̏���
void specialkeyboard(int k, int x, int y) {
	switch(k) {
	case GLUT_KEY_RIGHT:
		if(mode == 1) tetrimino.translate(1, 0, false, &board);
		break;
	case GLUT_KEY_LEFT:
		if(mode == 1) tetrimino.translate(-1, 0, false, &board);
		break;
	case GLUT_KEY_DOWN:
		if(mode == 0) {
			if(title_pos < 1)title_pos++;
		} else if(mode == 1) {
			if(tetrimino.translate(0, -1, false, &board)) {
				hold_check = true;
				Next_Mino_set();
			}
		}
		break;
	case GLUT_KEY_UP:
		if(mode == 0) {
			if(title_pos > 0)title_pos--;
		} else if(mode == 1) {
			while(!tetrimino.translate(0, -1, false, &board));
			hold_check = true;
			Next_Mino_set();
		}
		break;
	default:
		break;
	}
}

//�h���b�O����̏���
void motion(int x, int y) {
	//std::cout << elevation << ", " << azimuth << std::endl;
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
		int dx = (x - mousepoint.x) / 2;
		int dy = (y - mousepoint.y) / 2;
		center.x -= dx * cos(azimuth) - dy * sin(elevation) * sin(azimuth);
		center.y += dy * cos(elevation);
		center.z += -dx * sin(azimuth) - dy * sin(elevation) * cos(azimuth);
		//std::cout << center.x << ", " << center.y << ", " << center.z << std::endl;
		mousepoint.x = x;
		mousepoint.y = y;
	}
}

//�}�E�X�z�C�[���̏���
void MouseWheel(int wheel_number, int direction, int x, int y)
{
	view_distance -= direction * 2;
	viewpoint.x = -view_distance * cos(elevation) * sin(azimuth);
	viewpoint.y = view_distance * sin(elevation);
	viewpoint.z = view_distance * cos(elevation) * cos(azimuth);
	//std::cout << view_distance << std::endl;
}

//�ĕ`��֐��̌Ăяo��
void timer(int value) {
	glutPostRedisplay();
	glutTimerFunc(value, timer, 16);
}

//�R�[���o�b�N�֐��̂܂Ƃ�
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

//OpenGL�̏����ݒ�
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
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

//���C���֐�
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
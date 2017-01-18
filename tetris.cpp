#include "tetris.h"

int Tetris::angle;			//����p
int Tetris::mode;			//�Q�[�����[�h
GLfloat Tetris::angle_of_top;	//��ʂ̏�̐ݒ�(1 : �オy�̐�, -1 : ����y�̐�)
int Tetris::view_distance;	//���_���璆�_�̋���
double Tetris::azimuth;		//���ʊp
double Tetris::elevation;		//�p
bool Tetris::view_check;		//���_�ړ��̏������p�ϐ�
bool Tetris::reset_check;	//�e�g���X�̃��Z�b�g�p�ϐ�
Point2 Tetris::mousepoint;		//�}�E�X�̈ʒu
Point3 Tetris::viewpoint;	//���_
Point3 Tetris::center;	//�S�̂̒��S
clock_t Tetris::start;	//���Ԍo�߂̊Ǘ��p
TmpPoint Tetris::mino_pos;			//�e�g���~�m�̈ʒu
Tetrimino Tetris::tetrimino;		//�e�g���~�m
Tetrimino Tetris::nextmino;			//���̃e�g���~�m
bool Tetris::hold_check;		//�z�[���h�������p�ϐ�
TmpPoint Tetris::holdmino_pos;		//�z�[���h�̈ʒu
Tetrimino Tetris::holdmino;			//�z�[���h�̃e�g���~�m
TmpPoint Tetris::forecastmino_pos;	//���n�_�\�z�ʒu
Tetrimino Tetris::forecastmino;		//���n�_�̃e�g���~�m
Board Tetris::board;				//�{�[�h
int Tetris::rank_pos;			//�����L���O�̏���
char Tetris::rank_name[10][6];
Point2 Tetris::ranking[10];			//�����L���O�i�[�p�̕ϐ�
int Tetris::title_pos;			//�^�C�g���̈ʒu
Score Tetris::score;				//�X�R�A
double Tetris::speed;		//�������x(ms)
bool Tetris::light_check;	//���C�g�̃I���I�t

Tetris::Tetris() {
	angle = 90;
	mode = 0;
	angle_of_top = 1.0;
	view_distance = 200;
	azimuth = 0.0;
	elevation = 0.0;
	view_check = true;
	reset_check = true;
	mousepoint.x = 0; mousepoint.y = 0;
	viewpoint.x = 0; viewpoint.y = 0; viewpoint.z = view_distance;
	center.x = (BOARD_WIDTH + MENU_SIZE) / 2 * BLOCK_SIZE; center.y = BOARD_HEIGHT / 2 * BLOCK_SIZE; center.z = 0;
	start = clock();
	hold_check = true;
	rank_pos = -1;
	title_pos = 0;
	speed = 1000;
	light_check = false;
}

void Tetris::View_Reset() {
	reset_check = false;
	view_distance = 200;
	azimuth = 0.0;
	elevation = 0.0;
	mousepoint.x = 0; mousepoint.y = 0;
	viewpoint.x = 0; viewpoint.y = 0; viewpoint.z = view_distance;
	center.x = (BOARD_WIDTH + MENU_SIZE) / 2 * BLOCK_SIZE; center.y = BOARD_HEIGHT / 2 * BLOCK_SIZE; center.z = 0;
}

void Tetris::Tetris_Init() {
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
	title_pos = 0;
	score.clear();
}

void Tetris::Gl_Init() {
	// �w�i�F
	glClearColor(1.0, 1.0, 1.0, 0.0);
	// �f�v�X�o�b�t�@�L��
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);

	//�����̐ݒ�
	GLfloat lpos0[4] = { 10.0, 10.0, 10.0, 1.0 };
	GLfloat lcol0[4] = { 1.0, 1.0, 1.0, 1.0 };
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, lpos0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lcol0);
	glDisable(GL_LIGHTING);

	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
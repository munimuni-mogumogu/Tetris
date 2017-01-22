#include "tetris.h"

bool Tetris::run;
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
Tetrimino Tetris::holdmino;			//�z�[���h�̃e�g���~�m
TmpPoint Tetris::forecastmino_pos;	//���n�_�\�z�ʒu
Tetrimino Tetris::forecastmino;		//���n�_�̃e�g���~�m
Board Tetris::board;				//�{�[�h
int Tetris::rank_pos;			//�����L���O�̏���
char Tetris::rank_name[10][6];
int Tetris::name_pos;
int Tetris::dialog_pos;
bool Tetris::dialog_check;
int Tetris::page;
Point2 Tetris::ranking[10];			//�����L���O�i�[�p�̕ϐ�
int Tetris::title_pos;			//�^�C�g���̈ʒu
Score Tetris::score;				//�X�R�A
double Tetris::speed;		//�������x(ms)
bool Tetris::light_check;	//���C�g�̃I���I�t

Board3D Tetris::board3d;
TmpPoint3D Tetris::mino_pos3d;
Tetrimino3D Tetris::tetrimino3d;
Tetrimino3D Tetris::nextmino3d;
Tetrimino3D Tetris::holdmino3d;
TmpPoint3D Tetris::forecastmino_pos3d;
Tetrimino3D Tetris::forecastmino3d;

Tetris::Tetris() {
	run = true;
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
	name_pos = 0;
	dialog_pos = 0;
	dialog_check = false;
	page = 0;
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
	TmpPoint holdmino_pos;
	holdmino_pos.x = BOARD_WIDTH + 2;
	holdmino_pos.y = 7;
	tetrimino.setPoint(mino_pos);
	holdmino.setPoint(holdmino_pos);
	nextmino.create();
	start = clock();
	rank_pos = -1;
	name_pos = 0;
	dialog_pos = 0;
	dialog_check = false;
	page = 0;
	title_pos = 0;
	score.clear();

	board3d.init();
	tetrimino3d.create();
	holdmino3d = Tetrimino3D();
	mino_pos3d.x =  BOARD_WIDTH / 2;
	mino_pos3d.y = BOARD_HEIGHT - 2;
	mino_pos3d.z = BOARD_DEPTH / 2;
	tetrimino3d.setPoint(mino_pos3d);
	TmpPoint3D holdmino_pos3d;
	holdmino_pos3d.x = BOARD_WIDTH + 2;
	holdmino_pos3d.y = 7;
	holdmino_pos3d.z = 0;
	holdmino3d.setPoint(holdmino_pos3d);
	nextmino3d.create();
}

void Tetris::Gl_Init() {
	// �w�i�F
	glClearColor(1.0, 1.0, 1.0, 0.0);
	// �f�v�X�o�b�t�@�L��
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);

	GLfloat ambient[] = { (GLfloat)0.135, (GLfloat)0.2225, (GLfloat)0.1575, (GLfloat)1.0 };
	GLfloat diffuse[] = { (GLfloat)0.54, (GLfloat)0.89, (GLfloat)0.63, (GLfloat)1.0 };
	GLfloat specular[] = { (GLfloat)0.316228, (GLfloat)0.316228, (GLfloat)0.316228, (GLfloat)1.0 };
	GLfloat shininess = (GLfloat)12.8;
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &shininess);

	//�����̐ݒ�
	GLfloat lightPosition[4] = { (BOARD_WIDTH + MENU_SIZE) * BLOCK_SIZE / 2, BOARD_HEIGHT / 2, -500, 1.0 }; //�����̈ʒu
	GLfloat lightDiffuse[3]  = { 1.0, 1.0, 1.0 }; //�g�U��
	GLfloat lightAmbient[3]  = { 0.25, 0.25, 0.25 }; //����
	GLfloat lightSpecular[3] = { 0.25, 0.25, 0.25 }; //���ʌ�
	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glLightfv(GL_LIGHT0, GL_DIFFUSE,  lightDiffuse);
	glLightfv(GL_LIGHT0, GL_AMBIENT,  lightAmbient);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
	glEnable(GL_LIGHT0);
	glDisable(GL_LIGHTING);

	glDisable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
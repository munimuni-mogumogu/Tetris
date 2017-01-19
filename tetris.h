#ifndef DISPLAY_H
#define DISPLAY_H

#define _USE_MATH_DEFINES
#include <cmath>
#include <GL/freeglut.h>
#include <time.h>
#include "tetris.h"
#include "draw_str.h"

#define BOARD_WIDTH 12
#define BOARD_HEIGHT 22
#define BOARD_DEPTH 12

#define MINO_WIDTH 3
#define MINO_HEIGHT 3
#define MINO_DEPTH 3

#define BLOCK_SIZE 10

#define MENU_SIZE 8

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600

#define GLUT_KEY_ENTER 0x000d

#define TITLE 0
#define TETRIS 1
#define GAMEOVER 2
#define RANKING 3
#define TETRIS3D 4

#define RANKNAME 6

/*** �萔��` ***/
/* �{�[�h�T�C�Y */
#define BOARD_WIDTH		12
#define BOARD_HEIGHT	22

/* �e�g���~�m�T�C�Y */
#define MINO_WIDTH		3
#define MINO_HEIGHT		3

/* �e���v���[�g�p�^�[���� */
#define TEMPLATE_PATTERN	7

#include "tetrimino.h"
#include "board.h"
#include "score.h"
#include "tmp_struct.h"
#include "tetrimino_template.h"

struct Point2 {
	double x;
	double y;
};

struct Point3 {
	double x;
	double y;
	double z;
};

class Tetris {
private:
	static bool run;			//�Q�[���I������
	static int angle;			//����p
	static int mode;			//�Q�[�����[�h
	static GLfloat angle_of_top;	//��ʂ̏�̐ݒ�(1 : �オy�̐�, -1 : ����y�̐�)
	static int view_distance;	//���_���璆�_�̋���
	static double azimuth;		//���ʊp
	static double elevation;		//�p
	static bool view_check;		//���_�ړ��̏������p�ϐ�
	static bool reset_check;	//�e�g���X�̃��Z�b�g�p�ϐ�
	static Point2 mousepoint;		//�}�E�X�̈ʒu
	static Point3 viewpoint;	//���_
	static Point3 center;	//�S�̂̒��S
	static clock_t start;	//���Ԍo�߂̊Ǘ��p
	static TmpPoint mino_pos;			//�e�g���~�m�̈ʒu
	static Tetrimino tetrimino;		//�e�g���~�m
	static Tetrimino nextmino;			//���̃e�g���~�m
	static bool hold_check;		//�z�[���h�������p�ϐ�
	static TmpPoint holdmino_pos;		//�z�[���h�̈ʒu
	static Tetrimino holdmino;			//�z�[���h�̃e�g���~�m
	static TmpPoint forecastmino_pos;	//���n�_�\�z�ʒu
	static Tetrimino forecastmino;		//���n�_�̃e�g���~�m
	static Board board;				//�{�[�h
	static int rank_pos;			//�����L���O�̏���
	static Point2 ranking[10];			//�����L���O�i�[�p�̕ϐ�
	static char rank_name[10][RANKNAME];	//���O
	static int name_pos;		//���͈ʒu
	static int title_pos;			//�^�C�g���̈ʒu
	static Score score;				//�X�R�A
	static double speed;		//�������x(ms)
	static bool light_check;	//���C�g�̃I���I�t
public:
	Tetris();		//�R���X�g���N�^
	static void View_Reset();	//���_�̃��Z�b�g
	static void Tetris_Init();	//�e�g���X�̏����ݒ�
	static void Gl_Init();		//OpenGL�̏����ݒ�
	static bool Run(int, char**);	//���s

	//�^�C�g���̊֐�
	static void Title();
	static void Title_Display();
	static void Title_Keyboard(unsigned char, int, int);
	static void Title_Specialkeyboard(int, int, int);
	
	//�e�g���X�̊֐�
	static void Tetris_Main();
	static void Create_Block(bool[MINO_HEIGHT][MINO_WIDTH], GLdouble, GLdouble, GLdouble, GLdouble);
	static void Create_Board(bool[BOARD_HEIGHT][BOARD_WIDTH]);
	static void Draw_Information(int, int);
	static void Next_Mino();
	static void Mino_Hold();
	static void Tetris_Display();
	static void Tetris_Keyboard(unsigned char, int, int);
	static void Tetris_Specialkeyboard(int, int, int);

	//�Q�[���I�[�o�[�̊֐�
	static void Gameover();
	static void Gameover_Display();
	static void Gameover_Keyboard(unsigned char, int, int);
	static void Gameover_Specialkeyboard(int, int, int);

	//�����L���O�̊֐�
	static void Ranking();
	static void Change_Name(char[], char[], int);
	static void Set_Get_Ranking();
	static void Save_Ranking_Name();
	static void Ranking_Display();
	static void Ranking_Keyboard(unsigned char, int, int);
	static void Ranking_Specialkeyboard(int, int, int);

	//3D�e�g���X�̊֐�
	static void Tetris3D();
	static void Create_Block3D(bool[MINO_DEPTH][MINO_HEIGHT][MINO_WIDTH], GLdouble, GLdouble, GLdouble, GLdouble);
	static void Create_Board3D(bool[BOARD_DEPTH][BOARD_HEIGHT][BOARD_WIDTH]);
	static void Tetris3D_Display();
	static void Tetris3D_Keyboard(unsigned char, int, int);
	static void Tetris3D_Specialkeyboard(int, int, int);
	
	//�S�̂ŋ��ʂ̃R�[���o�b�N�֐�
	static void Funcgroup();
	static void Reshape(int, int);
	static void Mouse(int, int, int, int);
	static void Motion(int, int);
	static void Mousewheel(int, int, int, int);
	static void Timer(int);
};

#endif

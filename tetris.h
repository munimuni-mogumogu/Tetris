#ifndef DISPLAY_H
#define DISPLAY_H

#define _USE_MATH_DEFINES
#include <cmath>
#include <GL/freeglut.h>
#include <time.h>
#include "draw_str.h"

#include "tetrimino.h"
#include "tetrimino3d.h"
#include "tmp_struct.h"
#include "board.h"
#include "board3d.h"
#include "score.h"
#include "tetrimino_template.h"
#include "tetris_def.h"
#include "draw_template.h"

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
	static Point2 mousepoint;		//�}�E�X�̈ʒu
	static Point3 viewpoint;	//���_
	static Point3 center;	//�S�̂̒��S
	static clock_t start;	//���Ԍo�߂̊Ǘ��p
	static Draw_Rect draw_rect;
	static TmpPoint mino_pos;			//�e�g���~�m�̈ʒu
	static Tetrimino tetrimino;		//�e�g���~�m
	static Tetrimino nextmino;			//���̃e�g���~�m
	static bool hold_check;		//�z�[���h�������p�ϐ�
	static Tetrimino holdmino;			//�z�[���h�̃e�g���~�m
	static TmpPoint forecastmino_pos;	//���n�_�\�z�ʒu
	static Tetrimino forecastmino;		//���n�_�̃e�g���~�m
	static Board board;				//�{�[�h
	static int rank_pos;			//�����L���O�̏���
	static Point2 ranking[10];			//�����L���O�i�[�p�̕ϐ�
	static char rank_name[10][RANKNAME];	//���O
	static int name_pos;		//���͈ʒu
	static bool dialog_check;	//�͂�/�������̓���
	static int dialog_pos;		//�͂�/�������̓��͈ʒu
	static int title_pos;			//�^�C�g���̈ʒu
	static int page;
	static Score score;				//�X�R�A
	static double speed;		//�������x(ms)
	static bool light_check;	//���C�g�̃I���I�t
	static bool screen_check;
	
	static Board3D board3d;
	static TmpPoint3D mino_pos3d;
	static Tetrimino3D tetrimino3d;
	static Tetrimino3D nextmino3d;
	static Tetrimino3D holdmino3d;
	static TmpPoint3D forecastmino_pos3d;
	static Tetrimino3D forecastmino3d;
	
public:
	Tetris();		//�R���X�g���N�^
	static bool Run(int, char**);	//���s

private:
	static void View_Reset();	//���_�̃��Z�b�g
	static void Tetris_Init();	//�e�g���X�̏����ݒ�
	static void Gl_Init();		//OpenGL�̏����ݒ�

	//�^�C�g���̊֐�
	static void Title();
	static void Title_Display();
	static void Title_Keyboard(unsigned char, int, int);
	static void Title_Specialkeyboard(int, int, int);
	
	//�e�g���X�̊֐�
	static void Tetris_Main();
	static void DrawCube(int = 0, GLdouble = 0, GLdouble = 0, GLdouble = 0, GLdouble = 1);
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
	static int charcheck();
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
	static void Draw_Information3D(int, int);
	static void Next_Mino3D();
	static void Mino_Hold3D();
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
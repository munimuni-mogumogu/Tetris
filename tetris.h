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

/*** 定数定義 ***/
/* ボードサイズ */
#define BOARD_WIDTH		12
#define BOARD_HEIGHT	22

/* テトリミノサイズ */
#define MINO_WIDTH		3
#define MINO_HEIGHT		3

/* テンプレートパターン数 */
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
	static bool run;			//ゲーム終了判定
	static int angle;			//視野角
	static int mode;			//ゲームモード
	static GLfloat angle_of_top;	//画面の上の設定(1 : 上がyの正, -1 : 下がyの正)
	static int view_distance;	//視点から中点の距離
	static double azimuth;		//方位角
	static double elevation;		//仰角
	static bool view_check;		//視点移動の初期化用変数
	static bool reset_check;	//テトリスのリセット用変数
	static Point2 mousepoint;		//マウスの位置
	static Point3 viewpoint;	//視点
	static Point3 center;	//全体の中心
	static clock_t start;	//時間経過の管理用
	static TmpPoint mino_pos;			//テトリミノの位置
	static Tetrimino tetrimino;		//テトリミノ
	static Tetrimino nextmino;			//次のテトリミノ
	static bool hold_check;		//ホールド初期化用変数
	static TmpPoint holdmino_pos;		//ホールドの位置
	static Tetrimino holdmino;			//ホールドのテトリミノ
	static TmpPoint forecastmino_pos;	//着地点予想位置
	static Tetrimino forecastmino;		//着地点のテトリミノ
	static Board board;				//ボード
	static int rank_pos;			//ランキングの順位
	static Point2 ranking[10];			//ランキング格納用の変数
	static char rank_name[10][RANKNAME];	//名前
	static int name_pos;		//入力位置
	static int title_pos;			//タイトルの位置
	static Score score;				//スコア
	static double speed;		//落下速度(ms)
	static bool light_check;	//ライトのオンオフ
public:
	Tetris();		//コンストラクタ
	static void View_Reset();	//視点のリセット
	static void Tetris_Init();	//テトリスの初期設定
	static void Gl_Init();		//OpenGLの初期設定
	static bool Run(int, char**);	//実行

	//タイトルの関数
	static void Title();
	static void Title_Display();
	static void Title_Keyboard(unsigned char, int, int);
	static void Title_Specialkeyboard(int, int, int);
	
	//テトリスの関数
	static void Tetris_Main();
	static void Create_Block(bool[MINO_HEIGHT][MINO_WIDTH], GLdouble, GLdouble, GLdouble, GLdouble);
	static void Create_Board(bool[BOARD_HEIGHT][BOARD_WIDTH]);
	static void Draw_Information(int, int);
	static void Next_Mino();
	static void Mino_Hold();
	static void Tetris_Display();
	static void Tetris_Keyboard(unsigned char, int, int);
	static void Tetris_Specialkeyboard(int, int, int);

	//ゲームオーバーの関数
	static void Gameover();
	static void Gameover_Display();
	static void Gameover_Keyboard(unsigned char, int, int);
	static void Gameover_Specialkeyboard(int, int, int);

	//ランキングの関数
	static void Ranking();
	static void Change_Name(char[], char[], int);
	static void Set_Get_Ranking();
	static void Save_Ranking_Name();
	static void Ranking_Display();
	static void Ranking_Keyboard(unsigned char, int, int);
	static void Ranking_Specialkeyboard(int, int, int);

	//3Dテトリスの関数
	static void Tetris3D();
	static void Create_Block3D(bool[MINO_DEPTH][MINO_HEIGHT][MINO_WIDTH], GLdouble, GLdouble, GLdouble, GLdouble);
	static void Create_Board3D(bool[BOARD_DEPTH][BOARD_HEIGHT][BOARD_WIDTH]);
	static void Tetris3D_Display();
	static void Tetris3D_Keyboard(unsigned char, int, int);
	static void Tetris3D_Specialkeyboard(int, int, int);
	
	//全体で共通のコールバック関数
	static void Funcgroup();
	static void Reshape(int, int);
	static void Mouse(int, int, int, int);
	static void Motion(int, int);
	static void Mousewheel(int, int, int, int);
	static void Timer(int);
};

#endif

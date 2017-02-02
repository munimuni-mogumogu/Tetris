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
	static bool run;			//ゲーム終了判定
	static int angle;			//視野角
	static int mode;			//ゲームモード
	static GLfloat angle_of_top;	//画面の上の設定(1 : 上がyの正, -1 : 下がyの正)
	static int view_distance;	//視点から中点の距離
	static double azimuth;		//方位角
	static double elevation;		//仰角
	static bool view_check;		//視点移動の初期化用変数
	static Point2 mousepoint;		//マウスの位置
	static Point3 viewpoint;	//視点
	static Point3 center;	//全体の中心
	static clock_t start;	//時間経過の管理用
	static Draw_Rect draw_rect;
	static TmpPoint mino_pos;			//テトリミノの位置
	static Tetrimino tetrimino;		//テトリミノ
	static Tetrimino nextmino;			//次のテトリミノ
	static bool hold_check;		//ホールド初期化用変数
	static Tetrimino holdmino;			//ホールドのテトリミノ
	static TmpPoint forecastmino_pos;	//着地点予想位置
	static Tetrimino forecastmino;		//着地点のテトリミノ
	static Board board;				//ボード
	static int rank_pos;			//ランキングの順位
	static Point2 ranking[10];			//ランキング格納用の変数
	static char rank_name[10][RANKNAME];	//名前
	static int name_pos;		//入力位置
	static bool dialog_check;	//はい/いいえの入力
	static int dialog_pos;		//はい/いいえの入力位置
	static int title_pos;			//タイトルの位置
	static int page;
	static Score score;				//スコア
	static double speed;		//落下速度(ms)
	static bool light_check;	//ライトのオンオフ
	static bool screen_check;
	
	static Board3D board3d;
	static TmpPoint3D mino_pos3d;
	static Tetrimino3D tetrimino3d;
	static Tetrimino3D nextmino3d;
	static Tetrimino3D holdmino3d;
	static TmpPoint3D forecastmino_pos3d;
	static Tetrimino3D forecastmino3d;
	
public:
	Tetris();		//コンストラクタ
	static bool Run(int, char**);	//実行

private:
	static void View_Reset();	//視点のリセット
	static void Tetris_Init();	//テトリスの初期設定
	static void Gl_Init();		//OpenGLの初期設定

	//タイトルの関数
	static void Title();
	static void Title_Display();
	static void Title_Keyboard(unsigned char, int, int);
	static void Title_Specialkeyboard(int, int, int);
	
	//テトリスの関数
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

	//ゲームオーバーの関数
	static void Gameover();
	static void Gameover_Display();
	static int charcheck();
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
	static void Draw_Information3D(int, int);
	static void Next_Mino3D();
	static void Mino_Hold3D();
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
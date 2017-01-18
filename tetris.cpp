#include "tetris.h"

int Tetris::angle;			//視野角
int Tetris::mode;			//ゲームモード
GLfloat Tetris::angle_of_top;	//画面の上の設定(1 : 上がyの正, -1 : 下がyの正)
int Tetris::view_distance;	//視点から中点の距離
double Tetris::azimuth;		//方位角
double Tetris::elevation;		//仰角
bool Tetris::view_check;		//視点移動の初期化用変数
bool Tetris::reset_check;	//テトリスのリセット用変数
Point2 Tetris::mousepoint;		//マウスの位置
Point3 Tetris::viewpoint;	//視点
Point3 Tetris::center;	//全体の中心
clock_t Tetris::start;	//時間経過の管理用
TmpPoint Tetris::mino_pos;			//テトリミノの位置
Tetrimino Tetris::tetrimino;		//テトリミノ
Tetrimino Tetris::nextmino;			//次のテトリミノ
bool Tetris::hold_check;		//ホールド初期化用変数
TmpPoint Tetris::holdmino_pos;		//ホールドの位置
Tetrimino Tetris::holdmino;			//ホールドのテトリミノ
TmpPoint Tetris::forecastmino_pos;	//着地点予想位置
Tetrimino Tetris::forecastmino;		//着地点のテトリミノ
Board Tetris::board;				//ボード
int Tetris::rank_pos;			//ランキングの順位
char Tetris::rank_name[10][6];
Point2 Tetris::ranking[10];			//ランキング格納用の変数
int Tetris::title_pos;			//タイトルの位置
Score Tetris::score;				//スコア
double Tetris::speed;		//落下速度(ms)
bool Tetris::light_check;	//ライトのオンオフ

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
	// 背景色
	glClearColor(1.0, 1.0, 1.0, 0.0);
	// デプスバッファ有効
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);

	//光源の設定
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
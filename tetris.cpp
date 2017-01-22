/**
*	@file	tetris.cpp
*	@brief	テトリスの初期化及び全体で使用する関数のまとめ
*	@author	三木 陽平
*	@date	2017/01/22
*/

#include "tetris.h"

//Tetris classの変数の初期化
bool Tetris::run;				//ゲーム終了判定用
int Tetris::angle;				//視野角
int Tetris::mode;				//ゲームモード
GLfloat Tetris::angle_of_top;	//画面の上の設定(1 : 上がyの正, -1 : 下がyの正)
int Tetris::view_distance;		//視点から中点の距離
double Tetris::azimuth;			//方位角
double Tetris::elevation;		//仰角
bool Tetris::view_check;		//視点移動の初期化用
Point2 Tetris::mousepoint;		//マウスの位置
Point3 Tetris::viewpoint;		//視点
Point3 Tetris::center;			//全体の中心
clock_t Tetris::start;			//時間経過の管理用
TmpPoint Tetris::mino_pos;		//テトリミノの位置
Tetrimino Tetris::tetrimino;	//テトリミノ
Tetrimino Tetris::nextmino;		//次のテトリミノ
bool Tetris::hold_check;		//ホールド初期化用
Tetrimino Tetris::holdmino;		//ホールドのテトリミノ
TmpPoint Tetris::forecastmino_pos;	//着地点予測位置
Tetrimino Tetris::forecastmino;	//着地点のテトリミノ
Board Tetris::board;			//ボード
int Tetris::rank_pos;			//ランキングの順位
char Tetris::rank_name[10][6];	//ランキングの名前用
int Tetris::name_pos;			//名前入力時の入力位置
int Tetris::dialog_pos;			//選択位置
bool Tetris::dialog_check;		//ダイアログが出ているかどうか
int Tetris::page;				//ランキングのページ
Point2 Tetris::ranking[10];		//ランキング格納用
int Tetris::title_pos;			//タイトルの位置
Score Tetris::score;			//スコア
double Tetris::speed;			//落下速度(ms)
bool Tetris::light_check;		//ライトのオンオフ

Board3D Tetris::board3d;		//3Dテトリスのボード
TmpPoint3D Tetris::mino_pos3d;	//3Dテトリスのミノの位置
Tetrimino3D Tetris::tetrimino3d;//3Dテトリスのミノ
Tetrimino3D Tetris::nextmino3d;	//次のミノ
Tetrimino3D Tetris::holdmino3d;	//ホールドミノ
TmpPoint3D Tetris::forecastmino_pos3d;	//着地点予測位置
Tetrimino3D Tetris::forecastmino3d;		//着地点予測用ミノ

/**
*	@brief		Tetrisのコンストラクタ
*	@return		なし
*/
Tetris::Tetris() {
	run = true;
	angle = 90;
	mode = 0;
	angle_of_top = 1.0;
	view_distance = 200;
	azimuth = 0.0;
	elevation = 0.0;
	view_check = true;
	mousepoint.x = 0; mousepoint.y = 0;
	viewpoint.x = 0; viewpoint.y = 0; viewpoint.z = view_distance;
	center.x = (BOARD_WIDTH + MENU_SIZE) / 2 * BLOCK_SIZE; center.y = BOARD_HEIGHT / 2 * BLOCK_SIZE; center.z = 0;
	start = clock();
	hold_check = true;
	rank_pos = -1;
	name_pos = 0;
	dialog_pos = 0;
	dialog_check = false;
	page = TETRIS;
	title_pos = 0;
	speed = 1000;
	light_check = false;
}

/**
*	@brief		視点位置リセット
*	@return		なし
*/
void Tetris::View_Reset() {
	view_distance = 200;
	azimuth = 0.0;
	elevation = 0.0;
	mousepoint.x = 0; mousepoint.y = 0;
	viewpoint.x = 0; viewpoint.y = 0; viewpoint.z = view_distance;
	center.x = (BOARD_WIDTH + MENU_SIZE) / 2 * BLOCK_SIZE; center.y = BOARD_HEIGHT / 2 * BLOCK_SIZE; center.z = 0;
}

/**
*	@brief		テトリスの初期化用
*	@return		なし
*/
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
	page = TETRIS;
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

/**
*	@brief		OpenGLの初期設定
*	@return		なし
*/
void Tetris::Gl_Init() {
	// 背景色
	glClearColor(1.0, 1.0, 1.0, 0.0);
	// デプスバッファ有効
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);

	//ライティングをonにした時の物体の質感(翡翠を参照)
	GLfloat ambient[] = { (GLfloat)0.135, (GLfloat)0.2225, (GLfloat)0.1575, (GLfloat)1.0 };
	GLfloat diffuse[] = { (GLfloat)0.54, (GLfloat)0.89, (GLfloat)0.63, (GLfloat)1.0 };
	GLfloat specular[] = { (GLfloat)0.316228, (GLfloat)0.316228, (GLfloat)0.316228, (GLfloat)1.0 };
	GLfloat shininess = (GLfloat)12.8;
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &shininess);

	//光源の設定
	GLfloat lightPosition[4] = { (BOARD_WIDTH + MENU_SIZE) * BLOCK_SIZE / 2, BOARD_HEIGHT / 2, -500, 1.0 }; //光源の位置
	GLfloat lightDiffuse[3]  = { 1.0, 1.0, 1.0 }; //拡散光
	GLfloat lightAmbient[3]  = { 0.25, 0.25, 0.25 }; //環境光
	GLfloat lightSpecular[3] = { 0.25, 0.25, 0.25 }; //鏡面光
	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glLightfv(GL_LIGHT0, GL_DIFFUSE,  lightDiffuse);
	glLightfv(GL_LIGHT0, GL_AMBIENT,  lightAmbient);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
	glEnable(GL_LIGHT0);
	glDisable(GL_LIGHTING);

	//両面表示指定
	glDisable(GL_CULL_FACE);

	//透過処理
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
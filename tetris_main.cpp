/**
*	@file	tetris_main.cpp
*	@brief	テトリスのmain関数(コールバック関数)
*	@author	三木 陽平
*	@date	2017/01/22
*/

#include "tetris.h"

/**
*	@brief		実行用関数
*	@param [in]	argc
*	@param [in]	**argv
*	@return		終了時にfalseを返す
*/
bool Tetris::Run(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("TETRIS");
	Gl_Init();
	Tetris_Init();
	Funcgroup();
	glutMainLoop();
	return run;
}

/**
*	@brief		OpenGLのコールバック関数のまとめ(全共通の物)
*	@return		なし
*/
void Tetris::Funcgroup() {
	glutReshapeFunc(Reshape);
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	glutMouseWheelFunc(Mousewheel);
	glutTimerFunc(16, Timer, 0);
}

/**
*	@brief		OpenGLのReshape関数
*				視点の必要な設定
*	@param [in]	w	Windowの横幅
*	@param [in]	h	Windowの縦幅
*	@return		なし
*/
void Tetris::Reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(angle, aspect, 0.1, 1000.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

/**
*	@brief		マウスのクリックの処理
*	@param [in]	b	ボタンクリック判定
*	@param [in]	s	ボタンの状態
*	@param [in]	x	x座標
*	@param [in]	y	y座標
*	@return		なし
*/
void Tetris::Mouse(int b, int s, int x, int y) {
	switch(b) {
	case GLUT_LEFT_BUTTON:
		mousepoint.x = x;
		mousepoint.y = y;
		break;
	case GLUT_RIGHT_BUTTON:
		mousepoint.x = x;
		mousepoint.y = y;
		//クリックされている間はtrue,離されるとfalse
		view_check = !view_check;
		break;
	}
}

/**
*	@brief		ドラッグ処理
*	@param [in]	x	x座標
*	@param [in]	y	y座標
*	@return		なし
*/
void Tetris::Motion(int x, int y) {
	//右ドラッグか左ドラッグかの判定
	if(view_check) {
		//左ドラッグの時
		//画面の端から端のドラッグを360°とする
		azimuth += (double)(x - mousepoint.x) / WINDOW_WIDTH * M_PI * 2;
		elevation += (double)(y - mousepoint.y) / WINDOW_HEIGHT * M_PI * 2;
		//上下の回転の限界(-90°～90°)
		if(elevation > M_PI / 2) elevation = M_PI / 2;
		else if(elevation < -M_PI / 2) elevation = -M_PI / 2;

		//視点の設定：view_distanceを半径とする球上の一点
		viewpoint.x = -view_distance * cos(elevation) * sin(azimuth);
		viewpoint.y = view_distance * sin(elevation);
		viewpoint.z = view_distance * cos(elevation) * cos(azimuth);
		//std::cout << viewpoint.x << ", " << viewpoint.y << ", " << viewpoint.z << std::endl;
		mousepoint.x = x;
		mousepoint.y = y;
	} else {
		//右ドラッグの時
		double dx = (x - mousepoint.x) / 2;
		double dy = (y - mousepoint.y) / 2;
		//視点の設定：注視点を平行移動することで視点も平行移動
		center.x -= dx * cos(azimuth) - dy * sin(elevation) * sin(azimuth);
		center.y += dy * cos(elevation);
		center.z += -dx * sin(azimuth) - dy * sin(elevation) * cos(azimuth);
		//std::cout << center.x << ", " << center.y << ", " << center.z << std::endl;
		mousepoint.x = x;
		mousepoint.y = y;
	}
}

/**
*	@brief		マウスホイールの処理
*	@param [in]	wheel_number	マウスホイールの番号
*	@param [in]	direction	どちらに回しているか(手前:-1, 奥:1)
*	@param [in]	x	x座標
*	@param [in]	y	y座標
*	@return		なし
*/
void Tetris::Mousewheel(int wheel_number, int direction, int x, int y)
{
	view_distance -= direction * 2;
	viewpoint.x = -view_distance * cos(elevation) * sin(azimuth);
	viewpoint.y = view_distance * sin(elevation);
	viewpoint.z = view_distance * cos(elevation) * cos(azimuth);
	//std::cout << wheel_number << " " << direction << " " << x << " " << y << std::endl;
}

/**
*	@brief		指定した時間ごとに呼び出される関数
*	@param [in]	value
*	@return		なし
*/
void Tetris::Timer(int value) {
	//ゲームのモードの切り替え
	switch(mode) {
	case TITLE:	//タイトル画面
		Title();
		break;
	case TETRIS:	//通常のテトリス
		Tetris_Main();
		break;
	case TETRIS3D:	//3Dのテトリス
		Tetris3D();
		break;
	case GAMEOVER:	//ゲームオーバー時
		Gameover();
		break;
	case RANKING:	//ランキングの描画
		Ranking();
		break;
	}
	//タイトルでEscキーを押された時にメインループ終了
	if(!run) glutLeaveMainLoop();
	glutPostRedisplay();
	glutTimerFunc(value, Timer, 16);
}
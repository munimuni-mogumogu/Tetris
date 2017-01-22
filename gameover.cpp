/**
*	@file	gameover.cpp
*	@brief	ゲームオーバーモード
*	@author	三木 陽平
*	@date	2017/01/22
*/

#include "tetris.h"

/**
*	@brief		ゲームオーバーモードのメイン関数
*	@return		なし
*/
void Tetris::Gameover() {
	glutDisplayFunc(Gameover_Display);
	glutKeyboardFunc(Gameover_Keyboard);
	glutSpecialFunc(Gameover_Specialkeyboard);
}

/**
*	@brief		ゲームオーバーモードの描画のメイン関数
*	@return		なし
*/
void Tetris::Gameover_Display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(viewpoint.x + center.x, viewpoint.y + center.y, viewpoint.z + center.z,
		center.x, center.y, center.z,
		0.0, angle_of_top, 0.0);

	//どのモードかを判定し,ボードを描画する
	if(page == TETRIS) Create_Board(board.getBoard().board);
	else if(page == TETRIS3D) Create_Board3D(board3d.getBoard().board);
	Draw_Information(score.getScore(), score.getLine());

	//ゲームオーバーの文字描画
	draw_str gameover_str("gameover", 1, 0, 0);
	glPushMatrix();
	glTranslated((BOARD_WIDTH + MENU_SIZE) / 2 * BLOCK_SIZE, BOARD_HEIGHT / 2 * BLOCK_SIZE, 30);
	glScaled(4, 4, 4);
	gameover_str.draw_block(CENTER);
	glPopMatrix();

	//please push enterの描画
	draw_str end_str("please push enter ", 1, 0, 0);
	glPushMatrix();
	glTranslated((BOARD_WIDTH + MENU_SIZE) / 2 * BLOCK_SIZE, (BOARD_HEIGHT - 4) / 2 * BLOCK_SIZE, 30);
	glScaled(2, 2, 2);
	end_str.draw_block(CENTER);
	glPopMatrix();

	glutSwapBuffers();
}

/**
*	@brief		ゲームオーバーのキー操作関数
*	@param [in]	k	キー
*	@param [in] x	マウスx座標
*	@param [in] y	マウスy座標
*	@return		なし
*/
void Tetris::Gameover_Keyboard(unsigned char k, int x, int y) {
	switch(k) {
	case GLUT_KEY_ENTER:	//Enterキー入力時
		//どのモードかの判定
		if(page == TETRIS) Set_Get_Ranking(RANKINGTXT);
		else if(page == TETRIS3D) Set_Get_Ranking(RANKING3DTXT);
		mode = RANKING;
		break;
	case 'v':	//視点のリセット
		View_Reset();
		break;
	case 'r':	//タイトルへ戻る
		Tetris_Init();
		mode = TITLE;
		break;
	case 'l':	//ライティングのon/offの切り替え
		light_check = !light_check;
		if(light_check) glEnable(GL_LIGHTING);
		else glDisable(GL_LIGHTING);
		break;
	default:
		break;
	}
}

/**
*	@brief		ゲームオーバーモードの特殊キー操作関数
*	@param [in]	k	キー
*	@param [in] x	マウスx座標
*	@param [in] y	マウスy座標
*	@return		なし
*/
void Tetris::Gameover_Specialkeyboard(int k, int x, int y) {
	switch(k) {
	case GLUT_KEY_UP:
	default:
		break;
	}
}
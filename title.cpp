/**
*	@file	title.cpp
*	@brief	タイトルモード
*	@author	三木 陽平
*	@date	2017/01/22
*/

#include "tetris.h"

/**
*	@brief		タイトルモードのメイン関数
*	@return		なし
*/
void Tetris::Title() {
	glutDisplayFunc(Title_Display);
	glutKeyboardFunc(Title_Keyboard);
	glutSpecialFunc(Title_Specialkeyboard);
}

/**
*	@brief		タイトルモードの描画関数
*	@return		なし
*/
void Tetris::Title_Display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(viewpoint.x + center.x, viewpoint.y + center.y, viewpoint.z + center.z,
		center.x, center.y, center.z,
		0.0, angle_of_top, 0.0);

	//選択コマンドの球
	glPushMatrix();
	glTranslated((BOARD_WIDTH + MENU_SIZE - 18) / 2 * BLOCK_SIZE, (BOARD_HEIGHT / 2 - 3 - (title_pos * 2)) * BLOCK_SIZE - 6, 0);
	glColor3d(1, 0, 0);
	glutSolidSphere(5, 5, 10);
	glPopMatrix();
	glPushMatrix();

	//タイトルの描画
	draw_str Title_str("tetris");
	glTranslated((BOARD_WIDTH + MENU_SIZE) / 2 * BLOCK_SIZE,  BOARD_HEIGHT / 2 * BLOCK_SIZE, 0);
	glScaled(6, 6, 6);
	Title_str.draw_block(CENTER);
	glPopMatrix();

	//通常テトリスの描画
	glPushMatrix();
	draw_str Start_str("start tetris");
	glTranslated((BOARD_WIDTH + MENU_SIZE) / 2 * BLOCK_SIZE, (BOARD_HEIGHT / 2 - 4) * BLOCK_SIZE, 0);
	glScaled(2, 2, 2);
	Start_str.draw_block(CENTER);
	glPopMatrix();
	
	//3Dテトリスの描画
	glPushMatrix();
	draw_str start3d("start 3D tetris");
	glTranslated((BOARD_WIDTH + MENU_SIZE) / 2 * BLOCK_SIZE, (BOARD_HEIGHT / 2 - 6) * BLOCK_SIZE, 0);
	glScaled(2, 2, 2);
	start3d.draw_block(CENTER);
	glPopMatrix();

	//ランキングの描画
	glPushMatrix();
	draw_str ranking_str("ranking");
	glTranslated((BOARD_WIDTH + MENU_SIZE) / 2 * BLOCK_SIZE, (BOARD_HEIGHT / 2 - 8) * BLOCK_SIZE, 0);
	glScaled(2, 2, 2);
	ranking_str.draw_block(CENTER);
	glPopMatrix();

	glutSwapBuffers();
}

/**
*	@brief		タイトルモードのキー操作関数
*	@param [in]	k	キー
*	@param [in] x	マウスx座標
*	@param [in] y	マウスy座標
*	@return		なし
*/
void Tetris::Title_Keyboard(unsigned char k, int x, int y) {
	switch(k) {
	case GLUT_KEY_ENTER:	//Enterキーの時
		//タイトルでどれが選択されているかの判定
		if(title_pos == 0) {
			//通常テトリスの時
			Tetris_Init();
			mode = TETRIS;
		} else if (title_pos == 1) {
			//3Dテトリスの時
			mode = TETRIS3D;
		} else if(title_pos == 2) {
			//ランキングの時
			Set_Get_Ranking(RANKINGTXT);
			mode = RANKING;
		}
		break;
	case '\033':	//テトリス全体の終了(Escキー)
		run = false;
		break;
	case 'v':	//視点のリセット
		View_Reset();
		break;
	case 'l':	//ライティングのon/off切り替え
		light_check = !light_check;
		if(light_check) glEnable(GL_LIGHTING);
		else glDisable(GL_LIGHTING);
		break;
	default:
		break;
	}
}

/**
*	@brief		タイトルモードの特殊キー操作関数
*	@param [in]	k	キー
*	@param [in] x	マウスx座標
*	@param [in] y	マウスy座標
*	@return		なし
*/
void Tetris::Title_Specialkeyboard(int k, int x, int y) {
	switch(k) {
	case GLUT_KEY_DOWN:	//タイトルの選択を下へ移動させる
		if(title_pos < 2)title_pos++;
		break;
	case GLUT_KEY_UP:	//タイトルの選択を上へ移動させる
		if(title_pos > 0)title_pos--;
		break;
	default:
		break;
	}
}
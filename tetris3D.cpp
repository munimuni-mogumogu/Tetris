/**
*	@file	tetris3D.cpp
*	@brief	3Dテトリスモード
*	@author	三木 陽平
*	@date	2017/01/22
*/

#include "tetris.h"

/**
*	@brief		3Dテトリスモードのメイン関数
*	@return		なし
*/
void Tetris::Tetris3D() {
	glutDisplayFunc(Tetris3D_Display);
	glutKeyboardFunc(Tetris3D_Keyboard);
	glutSpecialFunc(Tetris3D_Specialkeyboard);
}

/**
*	@brief		テトリミノ3Dの描画関数
*				透明度を利用する場合奥のものから描画することに注意
*	@param [in]	block[MINO_DEPTH][MINO_HEIGHT][MINO_WIDTH]	テトリミノ
*	@param [in]	Red		赤色(=0, 0 < Red < 1)
*	@param [in]	blue	青色(=0. 0 < Blue < 1)
*	@param [in]	Green	緑色(=0, 0 < Green < 1)
*	@param [in]	shadow	透明度(=1, 0 < shadow < 1)
*	@return		なし
*/
void Tetris::Create_Block3D(bool block[MINO_DEPTH][MINO_HEIGHT][MINO_WIDTH], GLdouble Red = 0, GLdouble Green = 0, GLdouble Blue = 0, GLdouble shadow = 1) {
	glPushMatrix();
	//透明度利用時はデプスバッファへの書き込みをしない
	if(shadow != 1) glDepthMask(GL_FALSE);
	for(int i = 0; i < MINO_DEPTH; i++) {
		for(int j = 0; j < MINO_HEIGHT; j++){
			for(int k = 0; k < MINO_WIDTH; k++) {
				glPushMatrix();
				glTranslated(k * BLOCK_SIZE, j * BLOCK_SIZE, -i * BLOCK_SIZE);
				if(block[i][j][k]) DrawCube(BLOCK_SIZE, Red, Green, Blue, shadow);
				glPopMatrix();
			}
		}
	}
	glDepthMask(GL_TRUE);
	glPopMatrix();
}

/**
*	@brief		ボードの描画関数
*				透明度を利用するため描画順に注意
*	@param [in]	board[BOARD_DEPTH][MINO_HEIGHT][MINO_WIDTH]	ボード
*	@return		なし
*/
void Tetris::Create_Board3D(bool block[BOARD_DEPTH][BOARD_HEIGHT][BOARD_WIDTH]) {
	for(int i = 1; i < BOARD_DEPTH - 1; i++) {
		for(int j = 1; j < BOARD_HEIGHT - 1; j++){
			for(int k = 1; k < BOARD_WIDTH - 1; k++) {
				glPushMatrix();
				glTranslated(k * BLOCK_SIZE, j * BLOCK_SIZE, -i * BLOCK_SIZE);
				if(block[i][j][k]) {
					DrawCube(BLOCK_SIZE, board3d.getBoard().red[i][j][k], board3d.getBoard().green[i][j][k], board3d.getBoard().blue[i][j][k]);
				}
				glPopMatrix();
			}
		}
	}
	//落下予測位置にテトリミノの描画(透明度60%)
	glPushMatrix();
	glTranslated(forecastmino3d.getX() * BLOCK_SIZE, forecastmino3d.getY() * BLOCK_SIZE, -forecastmino3d.getZ() * BLOCK_SIZE);
	Create_Block3D(forecastmino3d.getMino().mino, 0, 0, 0, 0.4);
	glPopMatrix();
	//3Dなのでボードは透過処理を行うためライティングの影響を受けない
	glDisable(GL_LIGHTING);
	for(int i = 0; i < BOARD_DEPTH; i++) {
		for(int j = 0; j < BOARD_HEIGHT; j++){
			for(int k = 0; k < BOARD_WIDTH; k++) {
				glPushMatrix();
				glTranslated(k * BLOCK_SIZE, j * BLOCK_SIZE, -i * BLOCK_SIZE);
				if(block[i][j][k]) {
					if(i == 0 || j == 0 || k == 0 || i == BOARD_DEPTH - 1 || k == BOARD_WIDTH - 1) {
						//柱は半透明に描画,箱は薄く描画
						if((i == 0 && j == 0) || (i == 0 && k == 0) || (i == 0 && k == BOARD_WIDTH - 1) || (i == BOARD_DEPTH - 1 && j == 0) || (i == BOARD_DEPTH - 1 && k == 0) || (i == BOARD_DEPTH - 1 && k == BOARD_WIDTH - 1) || (j == 0 && k == 0) || (j == 0 && k == BOARD_WIDTH - 1)) {
							//箱の時
							glDepthMask(GL_FALSE);
							DrawCube(BLOCK_SIZE, board3d.getBoard().red[i][j][k], board3d.getBoard().green[i][j][k], board3d.getBoard().blue[i][j][k], 0.4);
						} else {
							//柱の時
							glDepthMask(GL_FALSE);
							DrawCube(BLOCK_SIZE, board3d.getBoard().red[i][j][k], board3d.getBoard().green[i][j][k], board3d.getBoard().blue[i][j][k], 0.01);
						}
					}
				}
				glPopMatrix();
			}
		}
	}
	if(light_check) glEnable(GL_LIGHTING);
	glDepthMask(GL_TRUE);
}

/**
*	@brief		次のミノセット関数
*	@return		なし
*/
void Tetris::Next_Mino3D() {
	tetrimino3d.setMino(nextmino3d.getMino());
	tetrimino3d.setColor(nextmino3d.getR(), nextmino3d.getG(),nextmino3d.getB());
	nextmino3d.create();
	tetrimino3d.setPoint(mino_pos3d);
}

/**
*	@brief		ホールドミノセット関数
*	@return		なし
*/
void Tetris::Mino_Hold3D() {
	hold_check = false;
	TmpMino3D temp = holdmino3d.getMino();
	double color[3] = { holdmino3d.getR(), holdmino3d.getG(), holdmino3d.getB() };
	//ホールドされているミノが既にあるかの判定
	if(temp.mino[1][1][1] == false) {
		//ホールドミノがない
		holdmino3d.setMino(tetrimino3d.getMino());
		holdmino3d.setColor(tetrimino3d.getR(), tetrimino3d.getG(), tetrimino3d.getB());
		Next_Mino3D();
	} else {
		//ホールドミノがある
		holdmino3d.setMino(tetrimino3d.getMino());
		holdmino3d.setColor(tetrimino3d.getR(), tetrimino3d.getG(), tetrimino3d.getB());
		tetrimino3d.setMino(temp);
		tetrimino3d.setColor(color[0], color[1], color[2]);
		tetrimino3d.setPoint(mino_pos3d);
	}
}

/**
*	@brief		テトリス中の情報の描画
*	@param [in]	score	点数
*	@param [in]	line	ライン数
*	@return		なし
*/
void Tetris::Draw_Information3D(int score, int plane) {
	glPushMatrix();

	glTranslated(center.x, center.y, center.z);
	glRotated(azimuth/M_PI*180, 0, -1, 0);
	glRotated(-elevation/M_PI*180,info_pos.x,0,-info_pos.z);
	glTranslated(0, 0, view_distance - tmp_view_distance);
	
	//SCOREの文字の描画
	glPushMatrix();
	draw_str score_str("score");
	glTranslated(6 * BLOCK_SIZE, (BOARD_HEIGHT/2 - 2) * BLOCK_SIZE, 0);
	glScaled(2, 2, 0);
	score_str.draw_block();
	glPopMatrix();

	//点数の描画
	glPushMatrix();
	draw_str draw_score(score);
	glTranslated(6 * BLOCK_SIZE, (BOARD_HEIGHT/2 - 4) * BLOCK_SIZE, 0);
	glScaled(2, 2, 0);
	draw_score.draw_block();
	glPopMatrix();

	//PLANEの文字の描画
	glPushMatrix();
	draw_str plane_str("plane");
	glTranslated(6 * BLOCK_SIZE, (BOARD_HEIGHT/2 - 6) * BLOCK_SIZE, 0);
	glScaled(2, 2, 0);
	plane_str.draw_block();
	glPopMatrix();

	//消したPLANE数の描画
	glPushMatrix();
	draw_str draw_plane(plane);
	glTranslated(6 * BLOCK_SIZE, (BOARD_HEIGHT/2 - 8) * BLOCK_SIZE, 0);
	glScaled(2, 2, 0);
	draw_plane.draw_block();
	glPopMatrix();

	//HOLDの文字の描画
	glPushMatrix();
	draw_str hold_str("hold");
	glTranslated(6 * BLOCK_SIZE, (BOARD_HEIGHT/2 - 11) * BLOCK_SIZE, 0);
	glScaled(2, 2, 0);
	hold_str.draw_block();
	glPopMatrix();

	//ホールドミノの描画
	glPushMatrix();
	glTranslated(7 * BLOCK_SIZE, -4 * BLOCK_SIZE, 0);
	Create_Block3D(holdmino3d.getMino().mino, holdmino3d.getR(), holdmino3d.getG(), holdmino3d.getB());
	glPopMatrix();

	//NEXTの文字の描画
	glPushMatrix();
	draw_str next_str("next");
	glTranslated(6 * BLOCK_SIZE, -7 * BLOCK_SIZE, 0);
	glScaled(2, 2, 0);
	next_str.draw_block();
	glPopMatrix();

	//ネクストミノの描画
	glPushMatrix();
	glTranslated(7 * BLOCK_SIZE,-11 * BLOCK_SIZE, 0);
	Create_Block3D(nextmino3d.getMino().mino, nextmino3d.getR(), nextmino3d.getG(), nextmino3d.getB());
	glPopMatrix();
	glPopMatrix();
}

/**
*	@brief		通常テトリスモードの描画のメイン関数
*	@return		なし
*/
void Tetris::Tetris3D_Display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glEnable(GL_DEPTH_TEST);
	gluLookAt(viewpoint.x + center.x, viewpoint.y + center.y, viewpoint.z + center.z,
		center.x, center.y, center.z,
		0.0, angle_of_top, 0.0);
	glPushMatrix();

	//テトリミノの描画
	glPushMatrix();
	glTranslated(tetrimino3d.getX() * BLOCK_SIZE, tetrimino3d.getY() * BLOCK_SIZE, -tetrimino3d.getZ() * BLOCK_SIZE);
	Create_Block3D(tetrimino3d.getMino().mino, tetrimino3d.getR(), tetrimino3d.getG(), tetrimino3d.getB());
	glPopMatrix();

	//落下速度の指定(１プレーン消すごとに0.9倍, 初期1秒)
	speed = 1000 * pow(0.9, score.getLine() / 1);
	if(clock() - start > speed) {
		start = clock();
		//落下処理
		if(tetrimino3d.translate(0, -1, 0, false, &board3d)) {
			//下にミノが着いたとき
			hold_check = true;
			Next_Mino3D();
		}
	}

	//テトリス中の情報の描画
	glDepthMask(GL_FALSE);
	Draw_Information3D(score.getScore(), score.getLine());
	glDepthMask(GL_TRUE);

	//テトリミノの落下予測位置の計測
	forecastmino3d.setMino(tetrimino3d.getMino());
	forecastmino_pos3d = tetrimino3d.getXYZ();
	forecastmino3d.setPoint(forecastmino_pos3d);
	while(!forecastmino3d.translate(0, -1, 0, true, &board3d));

	//ボードの描画
	Create_Board3D(board3d.getBoard().board);
	//ゲームオーバーの判定
	if(board3d.boardCheck(score)) {
		page = TETRIS3D;
		mode = GAMEOVER;
	}
	glPopMatrix();
	glutSwapBuffers();
}

/**
*	@brief		テトリスモードのキー操作関数
*	@param [in]	k	キー
*	@param [in]	x	マウスx座標
*	@param [in]	y	マウスy座標
*	@return		なし
*/
void Tetris::Tetris3D_Keyboard(unsigned char k, int x, int y) {
	switch(k) {
	case 'z':	//回転(x左)
		tetrimino3d.rotate(1, 1, 0, 0, &board3d);
		break;
	case 'x':	//回転(x右)
		tetrimino3d.rotate(0, 1, 0, 0, &board3d);
		break;
	case 'a':	//回転(y左)
		tetrimino3d.rotate(1, 0, 1, 0, &board3d);
		break;
	case 's':	//回転(y右)
		tetrimino3d.rotate(0, 0, 1, 0, &board3d);
		break;
	case 'q':	//回転(z左)
		tetrimino3d.rotate(1, 0, 0, 1, &board3d);
		break;
	case 'w':	//回転(z右)
		tetrimino3d.rotate(0, 0, 0, 1, &board3d);
		break;
	case ' ':	//ホールド
		//2度連続でホールドしていないかの判定
		if(hold_check) Mino_Hold3D();
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
*	@brief		テトリスモードの特殊キー操作関数
*	@param [in]	k	キー
*	@param [in]	x	マウスx座標
*	@param [in]	y	マウスy座標
*	@return		なし
*/
void Tetris::Tetris3D_Specialkeyboard(int k, int x, int y) {
	switch(k) {
	case GLUT_KEY_RIGHT:	//移動(右)
		tetrimino3d.translate(1, 0, 0, false, &board3d);
		break;
	case GLUT_KEY_LEFT:		//移動(左)
		tetrimino3d.translate(-1, 0, 0, false, &board3d);
		break;
	case GLUT_KEY_DOWN:		//移動(下)
		tetrimino3d.translate(0, 0, -1, false, &board3d);
		break;
	case GLUT_KEY_UP:		//移動(上)
		tetrimino3d.translate(0, 0, 1, false, &board3d);
	case 112:		//移動(下)Shift左
		//着地判定
		if(tetrimino3d.translate(0, -1, 0, false, &board3d)) {
			hold_check = true;
			Next_Mino3D();
		}
		break;
	case 113:		//移動(着地)Shift右
		//着地するまで移動
		while(!tetrimino3d.translate(0, -1, 0, false, &board3d));
		hold_check = true;
		Next_Mino3D();
		break;
	default:
		break;
	}
}
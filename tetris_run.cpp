/**
*	@file	tetris_run.cpp
*	@brief	通常テトリスモード
*	@author	三木 陽平
*	@date	2017/01/22
*/

#include "tetris.h"

/**
*	@brief		通常テトリスモードのメイン関数
*	@return		なし
*/
void Tetris::Tetris_Main() {
	glutDisplayFunc(Tetris_Display);
	glutKeyboardFunc(Tetris_Keyboard);
	glutSpecialFunc(Tetris_Specialkeyboard);
}

/**
*	@brief		立方体の描画(線付き)
*	@param [in]	block[MINO_HEIGHT][MINO_WIDTH]	テトリミノ
*	@param [in]	Red		赤色(=0, 0 < Red < 1)
*	@param [in]	blue	青色(=0. 0 < Blue < 1)
*	@param [in]	Green	緑色(=0, 0 < Green < 1)
*	@param [in]	shadow	透明度(=1, 0 < shadow < 1)
*	@return		なし
*/
void Tetris::DrawCube(int size, GLdouble Red, GLdouble Green, GLdouble Blue, GLdouble shadow) {
	glPushMatrix();
	glScaled(size, size, size);
	glColor4d(Red, Green, Blue, shadow);
	glBegin(GL_QUADS);
	for (int j = 0; j < 6; ++j) {
		glNormal3dv(draw_rect.normal[j]); //法線ベクトルの指定
		for (int i = 0; i < 4; ++i) {
			glVertex3dv(draw_rect.vertex[draw_rect.face[j][i]]);
		}
	}
	glEnd();
	glColor4d(Red / 2, Green / 2, Blue / 2, shadow);
	glBegin(GL_LINE_LOOP);
	for(int i = 0; i < 4; i++)
		glVertex3d(draw_rect.vertex2[i][0], draw_rect.vertex2[i][1], draw_rect.vertex2[i][2]);
	glEnd();
	glBegin(GL_LINE_LOOP);
	for(int i = 4; i < 8; i++)
		glVertex3d(draw_rect.vertex2[i][0], draw_rect.vertex2[i][1], draw_rect.vertex2[i][2]);
	glEnd();
	for(int i = 0; i < 4; i++) {
		glBegin(GL_LINE_LOOP);
		glVertex3d(draw_rect.vertex2[i][0], draw_rect.vertex2[i][1], draw_rect.vertex2[i][2]);
		glVertex3d(draw_rect.vertex2[i + 4][0], draw_rect.vertex2[i + 4][1], draw_rect.vertex2[i + 4][2]);
		glEnd();
	}
	glPopMatrix();
}

/**
*	@brief		テトリミノの描画関数
*				透明度を利用する場合奥のものから描画することに注意
*	@param [in]	block[MINO_HEIGHT][MINO_WIDTH]	テトリミノ
*	@param [in]	Red		赤色(=0, 0 < Red < 1)
*	@param [in]	blue	青色(=0. 0 < Blue < 1)
*	@param [in]	Green	緑色(=0, 0 < Green < 1)
*	@param [in]	shadow	透明度(=1, 0 < shadow < 1)
*	@return		なし
*/
void Tetris::Create_Block(bool block[MINO_HEIGHT][MINO_WIDTH], GLdouble Red = 0, GLdouble Green = 0, GLdouble Blue = 0, GLdouble shadow = 1) {
	glPushMatrix();
	//透明度利用時はデプスバッファへの書き込みをしない
	if(shadow != 1) glDepthMask(GL_FALSE);
	for(int i = 0; i < MINO_HEIGHT; i++) {
		for(int j = 0; j < MINO_WIDTH; j++){
			glPushMatrix();
			glTranslated(j * BLOCK_SIZE, i * BLOCK_SIZE, 0.0);
			if(block[i][j]) DrawCube(BLOCK_SIZE, Red, Green, Blue, shadow);
			glPopMatrix();
		}
	}
	glDepthMask(GL_TRUE);
	glPopMatrix();
}

/**
*	@brief		ボードの描画関数
*				透明度を利用するため描画順に注意
*	@param [in]	board[MINO_HEIGHT][MINO_WIDTH]	ボード
*	@return		なし
*/
void Tetris::Create_Board(bool block[BOARD_HEIGHT][BOARD_WIDTH]) {
	for(int i = 0; i < BOARD_HEIGHT; i++) {
		for(int j = 0; j < BOARD_WIDTH; j++){
			glPushMatrix();
			glTranslated(j * BLOCK_SIZE, i * BLOCK_SIZE, 0.0);
			if(block[i][j]) {
				if(i == 0 || j == 0 || j == BOARD_WIDTH - 1) {
					//枠は半透明に描画
					glDepthMask(GL_FALSE);
					DrawCube(BLOCK_SIZE, board.getBoard().red[i][j], board.getBoard().green[i][j], board.getBoard().blue[i][j], 0.4);
				} else {
					glDepthMask(GL_TRUE);
					DrawCube(BLOCK_SIZE, board.getBoard().red[i][j], board.getBoard().green[i][j], board.getBoard().blue[i][j]);
				}
			}
			glPopMatrix();
		}
	}
	glDepthMask(GL_TRUE);
}

/**
*	@brief		次のミノセット関数
*	@return		なし
*/
void Tetris::Next_Mino() {
	tetrimino.setMino(nextmino.getMino());
	tetrimino.setColor(nextmino.getR(), nextmino.getG(),nextmino.getB());
	if(page == TETRIS) nextmino.create(2);
	else if(page == TETRISRAND) nextmino.create(0);
	tetrimino.setPoint(mino_pos);
}

/**
*	@brief		ホールドミノセット関数
*	@return		なし
*/
void Tetris::Mino_Hold() {
	hold_check = false;
	TmpMino temp = holdmino.getMino();
	double color[3] = { holdmino.getR(), holdmino.getG(), holdmino.getB() };
	//ホールドされているミノが既にあるかの判定
	if(temp.mino[1][1] == false) {
		//ホールドミノがない
		holdmino.setMino(tetrimino.getMino());
		holdmino.setColor(tetrimino.getR(), tetrimino.getG(), tetrimino.getB());
		Next_Mino();
	} else {
		//ホールドミノがある
		holdmino.setMino(tetrimino.getMino());
		holdmino.setColor(tetrimino.getR(), tetrimino.getG(), tetrimino.getB());
		tetrimino.setMino(temp);
		tetrimino.setColor(color[0], color[1], color[2]);
		tetrimino.setPoint(mino_pos);
	}
}

/**
*	@brief		テトリス中の情報の描画
*	@param [in]	score	点数
*	@param [in]	line	ライン数
*	@return		なし
*/
void Tetris::Draw_Information(int score, int line) {
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

	//LINEの文字の描画
	glPushMatrix();
	draw_str line_str("line");
	glTranslated(6 * BLOCK_SIZE, (BOARD_HEIGHT/2 - 6) * BLOCK_SIZE, 0);
	glScaled(2, 2, 0);
	line_str.draw_block();
	glPopMatrix();

	//消したLINE数の描画
	glPushMatrix();
	draw_str draw_line(line);
	glTranslated(6 * BLOCK_SIZE, (BOARD_HEIGHT/2 - 8) * BLOCK_SIZE, 0);
	glScaled(2, 2, 0);
	draw_line.draw_block();
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
	Create_Block(holdmino.getMino().mino, holdmino.getR(), holdmino.getG(), holdmino.getB());
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
	Create_Block(nextmino.getMino().mino, nextmino.getR(), nextmino.getG(), nextmino.getB());
	glPopMatrix();
	glPopMatrix();
}

/**
*	@brief		通常テトリスモードの描画のメイン関数
*	@return		なし
*/
void Tetris::Tetris_Display() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(viewpoint.x + center.x, viewpoint.y + center.y, viewpoint.z + center.z,
		center.x, center.y, center.z,
		0.0, angle_of_top, 0.0);
	glPushMatrix();

	//テトリミノの描画
	glPushMatrix();
	glTranslated(tetrimino.getX() * BLOCK_SIZE, tetrimino.getY() * BLOCK_SIZE, 0);
	Create_Block(tetrimino.getMino().mino, tetrimino.getR(), tetrimino.getG(), tetrimino.getB());
	glPopMatrix();

	//落下速度の指定(１ライン消すごとに0.9倍, 初期1秒)
	speed = 1000 * pow(0.9, score.getLine() / 1);
	if(clock() - start > speed) {
		start = clock();
		//落下処理
		if(tetrimino.translate(0, -1, false, &board)) {
			//下にミノが着いたとき
			hold_check = true;
			Next_Mino();
		}
	}

	//テトリミノの落下予測位置の計測
	forecastmino.setMino(tetrimino.getMino());
	forecastmino_pos = tetrimino.getXY();
	forecastmino.setPoint(forecastmino_pos);
	while(!forecastmino.translate(0, -1, true, &board));
	//落下予測位置にテトリミノの描画(透明度60%)
	glPushMatrix();
	glTranslated(forecastmino.getX() * BLOCK_SIZE, forecastmino.getY() * BLOCK_SIZE, 0);
	Create_Block(forecastmino.getMino().mino, 1.0, 0, 0, 0.4);
	glPopMatrix();

	//ボードの描画
	Create_Board(board.getBoard().board);

	//テトリス中の情報の描画
	Draw_Information(score.getScore(), score.getLine());

	//ゲームオーバーの判定
	if(board.boardCheck(score)) {
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
void Tetris::Tetris_Keyboard(unsigned char k, int x, int y) {
	switch(k) {
	case 'v':	//視点のリセット
		View_Reset();
		break;
	case 'r':	//タイトルへ戻る
		Tetris_Init();
		mode = TITLE;
		break;
	case 'z':	//回転(左)
		tetrimino.rotate(1, &board);
		break;
	case 'x':	//回転(右)
		tetrimino.rotate(0, &board);
		break;
	case ' ':	//ホールド
		//2度連続でホールドしていないかの判定
		if(hold_check) Mino_Hold();
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
*	@brief		テトリスモードの特殊キー操作関数
*	@param [in]	k	キー
*	@param [in]	x	マウスx座標
*	@param [in]	y	マウスy座標
*	@return		なし
*/
void Tetris::Tetris_Specialkeyboard(int k, int x, int y) {
	switch(k) {
	case GLUT_KEY_RIGHT:	//移動(右)
		tetrimino.translate(1, 0, false, &board);
		break;
	case GLUT_KEY_LEFT:		//移動(左)
		tetrimino.translate(-1, 0, false, &board);
		break;
	case GLUT_KEY_DOWN:		//移動(下)
		//着地判定
		if(tetrimino.translate(0, -1, false, &board)) {
			hold_check = true;
			Next_Mino();
		}
		break;
	case GLUT_KEY_UP:		//移動(着地)
		//着地するまで移動
		while(!tetrimino.translate(0, -1, false, &board));
		hold_check = true;
		Next_Mino();
		break;
	default:
		break;
	}
}
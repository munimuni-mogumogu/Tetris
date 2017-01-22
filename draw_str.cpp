/**
*	@file	draw_str.cpp
*	@brief	文字列の描画
*	@author	三木 陽平
*	@date	2017/01/22
*/

#include "draw_str.h"
#include "GL/freeglut.h"

/**
*	@brief		draw_strのコンストラクタ
*	@return		なし
*/
draw_str::draw_str() {
	str = "null";
	color[0] = 0;
	color[1] = 0;
	color[2] = 0;
	str_pos = 0;
	while(str[str_pos++] != '\0');
}

/**
*	@brief		draw_strのコンストラクタ
*	@param [in]	figure[]	描画したい文字列
*	@param [in]	Red		赤色(=0, 0 < Red < 1)
*	@param [in]	blue	青色(=0. 0 < Blue < 1)
*	@param [in]	Green	緑色(=0, 0 < Green < 1)
*	@return		なし
*/
draw_str::draw_str(char figure[], GLdouble Red, GLdouble Blue, GLdouble Green) {
	str = figure;
	color[0] = Red;
	color[1] = Blue;
	color[2] = Green;
	str_pos = 0;
	while(str[str_pos++] != '\0');
}

/**
*	@brief		draw_strのコンストラクタ
*	@param [in]	number	描画したい数字
*	@param [in]	Red		赤色(=0, 0 < Red < 1)
*	@param [in]	blue	青色(=0. 0 < Blue < 1)
*	@param [in]	Green	緑色(=0, 0 < Green < 1)
*	@return		なし
*/
draw_str::draw_str(int number, GLdouble Red, GLdouble Blue, GLdouble Green) {
	int pos_check = 10;
	str_pos = 1;
	while(number >= pos_check) {
		pos_check *= 10;
		str_pos++;
	}
	str = new char[str_pos + 1];
	for(int i = str_pos - 1; i >= 0; i--) {
		str[i] = (char)(number % 10) + '0';
		number /= 10;
	}
	str[str_pos] = '\0';
	color[0] = Red;
	color[1] = Blue;
	color[2] = Green;
}

/**
*	@brief		セット関数
*	@param [in]	figure[]	描画したい文字列
*	@param [in]	Red		赤色(=0, 0 < Red < 1)
*	@param [in]	blue	青色(=0. 0 < Blue < 1)
*	@param [in]	Green	緑色(=0, 0 < Green < 1)
*	@return		なし
*/
void draw_str::set_str(char figure[], GLdouble Red, GLdouble Blue, GLdouble Green) {
	str = figure;
	color[0] = Red;
	color[1] = Blue;
	color[2] = Green;
	str_pos = 0;
	while(str[str_pos++] != '\0');
}

/**
*	@brief		セット関数
*	@param [in]	figure[]	描画したい数字
*	@param [in]	Red		赤色(=0, 0 < Red < 1)
*	@param [in]	blue	青色(=0. 0 < Blue < 1)
*	@param [in]	Green	緑色(=0, 0 < Green < 1)
*	@return		なし
*/
void draw_str::set_str(int number, GLdouble Red, GLdouble Blue, GLdouble Green) {
	int pos_check = 10;
	str_pos = 1;
	while(number >= pos_check) {
		pos_check *= 10;
		str_pos++;
	}
	str = new char[str_pos + 1];
	for(int i = str_pos - 1; i >= 0; i--) {
		str[i] = (char)(number % 10) + '0';
		number /= 10;
	}
	str[str_pos] = '\0';
	color[0] = Red;
	color[1] = Blue;
	color[2] = Green;
}

/**
*	@brief		描画関数(文字の描画)
*	@param [in]	block[STR_BLOCK_SIZE][STR_BLOCK_SIZE]
*	@return		なし
*/
void draw_str::glDrawStr(bool block[STR_BLOCK_SIZE][STR_BLOCK_SIZE]) {
	glColor3d(color[0], color[1], color[2]);
	for(int j = 1; j <= STR_BLOCK_SIZE; j++) {
		for(int k = 0; k < STR_BLOCK_SIZE; k++) {
			glPushMatrix();
			glTranslated(k, STR_BLOCK_SIZE - j, 0);
			if(block[STR_BLOCK_SIZE - j][k]) glutSolidCube(1);
			glPopMatrix();
		}
	}
}

/**
*	@brief		文字の描画
*	@param [in]	pos	どこに描画するか(=LEFT, CENTER)
*	@return		なし
*/
void draw_str::draw_block(int pos) {
	//真ん中に描画するとき
	if(pos == CENTER) glTranslated(-STR_BLOCK_SIZE * ((double)str_pos / 2), 0, 0);
	for(int i = 0; i < str_pos; i++) {
		glPushMatrix();
		//文字数分移動
		glTranslated((STR_BLOCK_SIZE + 1) * i, 0, 0);
		//文字作成
		bool block[STR_BLOCK_SIZE][STR_BLOCK_SIZE];
		switch(str[i]) {
		case 'a':
		case 'A':
			block[4][0] = 0; block[4][1] = 1; block[4][2] = 1; block[4][3] = 1; block[4][4] = 0;
			block[3][0] = 1; block[3][1] = 0; block[3][2] = 0; block[3][3] = 0; block[3][4] = 1;
			block[2][0] = 1; block[2][1] = 1; block[2][2] = 1; block[2][3] = 1; block[2][4] = 1;
			block[1][0] = 1; block[1][1] = 0; block[1][2] = 0; block[1][3] = 0; block[1][4] = 1;
			block[0][0] = 1; block[0][1] = 0; block[0][2] = 0; block[0][3] = 0; block[0][4] = 1;
			break;
		case 'b':
		case 'B':
			block[4][0] = 1; block[4][1] = 1; block[4][2] = 1; block[4][3] = 1; block[4][4] = 0;
			block[3][0] = 1; block[3][1] = 0; block[3][2] = 0; block[3][3] = 0; block[3][4] = 1;
			block[2][0] = 1; block[2][1] = 1; block[2][2] = 1; block[2][3] = 1; block[2][4] = 0;
			block[1][0] = 1; block[1][1] = 0; block[1][2] = 0; block[1][3] = 0; block[1][4] = 1;
			block[0][0] = 1; block[0][1] = 1; block[0][2] = 1; block[0][3] = 1; block[0][4] = 0;
			break;
		case 'c':
		case 'C':
			block[4][0] = 0; block[4][1] = 1; block[4][2] = 1; block[4][3] = 1; block[4][4] = 0;
			block[3][0] = 1; block[3][1] = 0; block[3][2] = 0; block[3][3] = 0; block[3][4] = 1;
			block[2][0] = 1; block[2][1] = 0; block[2][2] = 0; block[2][3] = 0; block[2][4] = 0;
			block[1][0] = 1; block[1][1] = 0; block[1][2] = 0; block[1][3] = 0; block[1][4] = 1;
			block[0][0] = 0; block[0][1] = 1; block[0][2] = 1; block[0][3] = 1; block[0][4] = 0;
			break;
		case 'd':
		case 'D':
			block[4][0] = 1; block[4][1] = 1; block[4][2] = 1; block[4][3] = 1; block[4][4] = 0;
			block[3][0] = 1; block[3][1] = 0; block[3][2] = 0; block[3][3] = 0; block[3][4] = 1;
			block[2][0] = 1; block[2][1] = 0; block[2][2] = 0; block[2][3] = 0; block[2][4] = 1;
			block[1][0] = 1; block[1][1] = 0; block[1][2] = 0; block[1][3] = 0; block[1][4] = 1;
			block[0][0] = 1; block[0][1] = 1; block[0][2] = 1; block[0][3] = 1; block[0][4] = 0;
			break;
		case 'e':
		case 'E':
			block[4][0] = 1; block[4][1] = 1; block[4][2] = 1; block[4][3] = 1; block[4][4] = 1;
			block[3][0] = 1; block[3][1] = 0; block[3][2] = 0; block[3][3] = 0; block[3][4] = 0;
			block[2][0] = 1; block[2][1] = 1; block[2][2] = 1; block[2][3] = 1; block[2][4] = 1;
			block[1][0] = 1; block[1][1] = 0; block[1][2] = 0; block[1][3] = 0; block[1][4] = 0;
			block[0][0] = 1; block[0][1] = 1; block[0][2] = 1; block[0][3] = 1; block[0][4] = 1;
			break;
		case 'f':
		case 'F':
			block[4][0] = 1; block[4][1] = 1; block[4][2] = 1; block[4][3] = 1; block[4][4] = 1;
			block[3][0] = 1; block[3][1] = 0; block[3][2] = 0; block[3][3] = 0; block[3][4] = 0;
			block[2][0] = 1; block[2][1] = 1; block[2][2] = 1; block[2][3] = 1; block[2][4] = 1;
			block[1][0] = 1; block[1][1] = 0; block[1][2] = 0; block[1][3] = 0; block[1][4] = 0;
			block[0][0] = 1; block[0][1] = 0; block[0][2] = 0; block[0][3] = 0; block[0][4] = 0;
			break;
		case 'g':
		case 'G':
			block[4][0] = 0; block[4][1] = 1; block[4][2] = 1; block[4][3] = 1; block[4][4] = 0;
			block[3][0] = 1; block[3][1] = 0; block[3][2] = 0; block[3][3] = 0; block[3][4] = 0;
			block[2][0] = 1; block[2][1] = 0; block[2][2] = 1; block[2][3] = 1; block[2][4] = 1;
			block[1][0] = 1; block[1][1] = 0; block[1][2] = 0; block[1][3] = 0; block[1][4] = 1;
			block[0][0] = 0; block[0][1] = 1; block[0][2] = 1; block[0][3] = 1; block[0][4] = 0;
			break;
		case 'h':
		case 'H':
			block[4][0] = 1; block[4][1] = 0; block[4][2] = 0; block[4][3] = 0; block[4][4] = 1;
			block[3][0] = 1; block[3][1] = 0; block[3][2] = 0; block[3][3] = 0; block[3][4] = 1;
			block[2][0] = 1; block[2][1] = 1; block[2][2] = 1; block[2][3] = 1; block[2][4] = 1;
			block[1][0] = 1; block[1][1] = 0; block[1][2] = 0; block[1][3] = 0; block[1][4] = 1;
			block[0][0] = 1; block[0][1] = 0; block[0][2] = 0; block[0][3] = 0; block[0][4] = 1;
			break;
		case 'i':
		case 'I':
			block[4][0] = 0; block[4][1] = 1; block[4][2] = 1; block[4][3] = 1; block[4][4] = 0;
			block[3][0] = 0; block[3][1] = 0; block[3][2] = 1; block[3][3] = 0; block[3][4] = 0;
			block[2][0] = 0; block[2][1] = 0; block[2][2] = 1; block[2][3] = 0; block[2][4] = 0;
			block[1][0] = 0; block[1][1] = 0; block[1][2] = 1; block[1][3] = 0; block[1][4] = 0;
			block[0][0] = 0; block[0][1] = 1; block[0][2] = 1; block[0][3] = 1; block[0][4] = 0;
			break;
		case 'j':
		case 'J':
			block[4][0] = 0; block[4][1] = 0; block[4][2] = 1; block[4][3] = 1; block[4][4] = 1;
			block[3][0] = 0; block[3][1] = 0; block[3][2] = 0; block[3][3] = 1; block[3][4] = 0;
			block[2][0] = 0; block[2][1] = 0; block[2][2] = 0; block[2][3] = 1; block[2][4] = 0;
			block[1][0] = 1; block[1][1] = 0; block[1][2] = 0; block[1][3] = 1; block[1][4] = 0;
			block[0][0] = 0; block[0][1] = 1; block[0][2] = 1; block[0][3] = 0; block[0][4] = 0;
			break;
		case 'k':
		case 'K':
			block[4][0] = 0; block[4][1] = 1; block[4][2] = 0; block[4][3] = 0; block[4][4] = 1;
			block[3][0] = 0; block[3][1] = 1; block[3][2] = 0; block[3][3] = 1; block[3][4] = 0;
			block[2][0] = 0; block[2][1] = 1; block[2][2] = 1; block[2][3] = 0; block[2][4] = 0;
			block[1][0] = 0; block[1][1] = 1; block[1][2] = 0; block[1][3] = 1; block[1][4] = 0;
			block[0][0] = 0; block[0][1] = 1; block[0][2] = 0; block[0][3] = 0; block[0][4] = 1;
			break;
		case 'l':
		case 'L':
			block[4][0] = 0; block[4][1] = 1; block[4][2] = 0; block[4][3] = 0; block[4][4] = 0;
			block[3][0] = 0; block[3][1] = 1; block[3][2] = 0; block[3][3] = 0; block[3][4] = 0;
			block[2][0] = 0; block[2][1] = 1; block[2][2] = 0; block[2][3] = 0; block[2][4] = 0;
			block[1][0] = 0; block[1][1] = 1; block[1][2] = 0; block[1][3] = 0; block[1][4] = 0;
			block[0][0] = 0; block[0][1] = 1; block[0][2] = 1; block[0][3] = 1; block[0][4] = 1;
			break;
		case 'm':
		case 'M':
			block[4][0] = 1; block[4][1] = 0; block[4][2] = 0; block[4][3] = 0; block[4][4] = 1;
			block[3][0] = 1; block[3][1] = 1; block[3][2] = 0; block[3][3] = 1; block[3][4] = 1;
			block[2][0] = 1; block[2][1] = 0; block[2][2] = 1; block[2][3] = 0; block[2][4] = 1;
			block[1][0] = 1; block[1][1] = 0; block[1][2] = 0; block[1][3] = 0; block[1][4] = 1;
			block[0][0] = 1; block[0][1] = 0; block[0][2] = 0; block[0][3] = 0; block[0][4] = 1;
			break;
		case 'n':
		case 'N':
			block[4][0] = 1; block[4][1] = 0; block[4][2] = 0; block[4][3] = 0; block[4][4] = 1;
			block[3][0] = 1; block[3][1] = 1; block[3][2] = 0; block[3][3] = 0; block[3][4] = 1;
			block[2][0] = 1; block[2][1] = 0; block[2][2] = 1; block[2][3] = 0; block[2][4] = 1;
			block[1][0] = 1; block[1][1] = 0; block[1][2] = 0; block[1][3] = 1; block[1][4] = 1;
			block[0][0] = 1; block[0][1] = 0; block[0][2] = 0; block[0][3] = 0; block[0][4] = 1;
			break;
		case 'o':
		case 'O':
			block[4][0] = 0; block[4][1] = 1; block[4][2] = 1; block[4][3] = 1; block[4][4] = 0;
			block[3][0] = 1; block[3][1] = 0; block[3][2] = 0; block[3][3] = 0; block[3][4] = 1;
			block[2][0] = 1; block[2][1] = 0; block[2][2] = 0; block[2][3] = 0; block[2][4] = 1;
			block[1][0] = 1; block[1][1] = 0; block[1][2] = 0; block[1][3] = 0; block[1][4] = 1;
			block[0][0] = 0; block[0][1] = 1; block[0][2] = 1; block[0][3] = 1; block[0][4] = 0;
			break;
		case 'p':
		case 'P':
			block[4][0] = 1; block[4][1] = 1; block[4][2] = 1; block[4][3] = 1; block[4][4] = 0;
			block[3][0] = 1; block[3][1] = 0; block[3][2] = 0; block[3][3] = 0; block[3][4] = 1;
			block[2][0] = 1; block[2][1] = 1; block[2][2] = 1; block[2][3] = 1; block[2][4] = 0;
			block[1][0] = 1; block[1][1] = 0; block[1][2] = 0; block[1][3] = 0; block[1][4] = 0;
			block[0][0] = 1; block[0][1] = 0; block[0][2] = 0; block[0][3] = 0; block[0][4] = 0;
			break;
		case 'q':
		case 'Q':
			block[4][0] = 0; block[4][1] = 1; block[4][2] = 1; block[4][3] = 1; block[4][4] = 0;
			block[3][0] = 1; block[3][1] = 0; block[3][2] = 0; block[3][3] = 0; block[3][4] = 1;
			block[2][0] = 1; block[2][1] = 0; block[2][2] = 0; block[2][3] = 0; block[2][4] = 1;
			block[1][0] = 1; block[1][1] = 0; block[1][2] = 0; block[1][3] = 1; block[1][4] = 1;
			block[0][0] = 0; block[0][1] = 1; block[0][2] = 1; block[0][3] = 1; block[0][4] = 1;
			break;
		case 'r':
		case 'R':
			block[4][0] = 1; block[4][1] = 1; block[4][2] = 1; block[4][3] = 1; block[4][4] = 0;
			block[3][0] = 1; block[3][1] = 0; block[3][2] = 0; block[3][3] = 0; block[3][4] = 1;
			block[2][0] = 1; block[2][1] = 1; block[2][2] = 1; block[2][3] = 1; block[2][4] = 0;
			block[1][0] = 1; block[1][1] = 0; block[1][2] = 0; block[1][3] = 1; block[1][4] = 0;
			block[0][0] = 1; block[0][1] = 0; block[0][2] = 0; block[0][3] = 0; block[0][4] = 1;
			break;
		case 's':
		case 'S':
			block[4][0] = 0; block[4][1] = 1; block[4][2] = 1; block[4][3] = 1; block[4][4] = 1;
			block[3][0] = 1; block[3][1] = 0; block[3][2] = 0; block[3][3] = 0; block[3][4] = 0;
			block[2][0] = 0; block[2][1] = 1; block[2][2] = 1; block[2][3] = 1; block[2][4] = 0;
			block[1][0] = 0; block[1][1] = 0; block[1][2] = 0; block[1][3] = 0; block[1][4] = 1;
			block[0][0] = 1; block[0][1] = 1; block[0][2] = 1; block[0][3] = 1; block[0][4] = 0;
			break;
		case 't':
		case 'T':
			block[4][0] = 1; block[4][1] = 1; block[4][2] = 1; block[4][3] = 1; block[4][4] = 1;
			block[3][0] = 0; block[3][1] = 0; block[3][2] = 1; block[3][3] = 0; block[3][4] = 0;
			block[2][0] = 0; block[2][1] = 0; block[2][2] = 1; block[2][3] = 0; block[2][4] = 0;
			block[1][0] = 0; block[1][1] = 0; block[1][2] = 1; block[1][3] = 0; block[1][4] = 0;
			block[0][0] = 0; block[0][1] = 0; block[0][2] = 1; block[0][3] = 0; block[0][4] = 0;
			break;
		case 'u':
		case 'U':
			block[4][0] = 1; block[4][1] = 0; block[4][2] = 0; block[4][3] = 0; block[4][4] = 1;
			block[3][0] = 1; block[3][1] = 0; block[3][2] = 0; block[3][3] = 0; block[3][4] = 1;
			block[2][0] = 1; block[2][1] = 0; block[2][2] = 0; block[2][3] = 0; block[2][4] = 1;
			block[1][0] = 1; block[1][1] = 0; block[1][2] = 0; block[1][3] = 0; block[1][4] = 1;
			block[0][0] = 0; block[0][1] = 1; block[0][2] = 1; block[0][3] = 1; block[0][4] = 0;
			break;
		case 'v':
		case 'V':
			block[4][0] = 1; block[4][1] = 0; block[4][2] = 0; block[4][3] = 0; block[4][4] = 1;
			block[3][0] = 1; block[3][1] = 0; block[3][2] = 0; block[3][3] = 0; block[3][4] = 1;
			block[2][0] = 0; block[2][1] = 1; block[2][2] = 0; block[2][3] = 1; block[2][4] = 0;
			block[1][0] = 0; block[1][1] = 1; block[1][2] = 0; block[1][3] = 1; block[1][4] = 0;
			block[0][0] = 0; block[0][1] = 0; block[0][2] = 1; block[0][3] = 0; block[0][4] = 0;
			break;
		case 'w':
		case 'W':
			block[4][0] = 1; block[4][1] = 0; block[4][2] = 0; block[4][3] = 0; block[4][4] = 1;
			block[3][0] = 1; block[3][1] = 0; block[3][2] = 1; block[3][3] = 0; block[3][4] = 1;
			block[2][0] = 1; block[2][1] = 0; block[2][2] = 1; block[2][3] = 0; block[2][4] = 1;
			block[1][0] = 0; block[1][1] = 1; block[1][2] = 0; block[1][3] = 1; block[1][4] = 0;
			block[0][0] = 0; block[0][1] = 1; block[0][2] = 0; block[0][3] = 1; block[0][4] = 0;
			break;
		case 'x':
		case 'X':
			block[4][0] = 1; block[4][1] = 0; block[4][2] = 0; block[4][3] = 0; block[4][4] = 1;
			block[3][0] = 0; block[3][1] = 1; block[3][2] = 0; block[3][3] = 1; block[3][4] = 0;
			block[2][0] = 0; block[2][1] = 0; block[2][2] = 1; block[2][3] = 0; block[2][4] = 0;
			block[1][0] = 0; block[1][1] = 1; block[1][2] = 0; block[1][3] = 1; block[1][4] = 0;
			block[0][0] = 1; block[0][1] = 0; block[0][2] = 0; block[0][3] = 0; block[0][4] = 1;
			break;
		case 'y':
		case 'Y':
			block[4][0] = 1; block[4][1] = 0; block[4][2] = 0; block[4][3] = 0; block[4][4] = 1;
			block[3][0] = 0; block[3][1] = 1; block[3][2] = 0; block[3][3] = 1; block[3][4] = 0;
			block[2][0] = 0; block[2][1] = 0; block[2][2] = 1; block[2][3] = 0; block[2][4] = 0;
			block[1][0] = 0; block[1][1] = 0; block[1][2] = 1; block[1][3] = 0; block[1][4] = 0;
			block[0][0] = 0; block[0][1] = 0; block[0][2] = 1; block[0][3] = 0; block[0][4] = 0;
			break;
		case 'z':
		case 'Z':
			block[4][0] = 1; block[4][1] = 1; block[4][2] = 1; block[4][3] = 1; block[4][4] = 1;
			block[3][0] = 0; block[3][1] = 0; block[3][2] = 0; block[3][3] = 1; block[3][4] = 0;
			block[2][0] = 0; block[2][1] = 0; block[2][2] = 1; block[2][3] = 0; block[2][4] = 0;
			block[1][0] = 0; block[1][1] = 1; block[1][2] = 0; block[1][3] = 0; block[1][4] = 0;
			block[0][0] = 1; block[0][1] = 1; block[0][2] = 1; block[0][3] = 1; block[0][4] = 1;
			break;
		case '0':
			block[4][0] = 0; block[4][1] = 1; block[4][2] = 1; block[4][3] = 1; block[4][4] = 0;
			block[3][0] = 1; block[3][1] = 0; block[3][2] = 0; block[3][3] = 1; block[3][4] = 1;
			block[2][0] = 1; block[2][1] = 0; block[2][2] = 1; block[2][3] = 0; block[2][4] = 1;
			block[1][0] = 1; block[1][1] = 1; block[1][2] = 0; block[1][3] = 0; block[1][4] = 1;
			block[0][0] = 0; block[0][1] = 1; block[0][2] = 1; block[0][3] = 1; block[0][4] = 0;
			break;
		case '1':
			block[4][0] = 0; block[4][1] = 0; block[4][2] = 1; block[4][3] = 0; block[4][4] = 0;
			block[3][0] = 0; block[3][1] = 1; block[3][2] = 1; block[3][3] = 0; block[3][4] = 0;
			block[2][0] = 0; block[2][1] = 0; block[2][2] = 1; block[2][3] = 0; block[2][4] = 0;
			block[1][0] = 0; block[1][1] = 0; block[1][2] = 1; block[1][3] = 0; block[1][4] = 0;
			block[0][0] = 0; block[0][1] = 0; block[0][2] = 1; block[0][3] = 0; block[0][4] = 0;
			break;
		case '2':
			block[4][0] = 0; block[4][1] = 1; block[4][2] = 1; block[4][3] = 1; block[4][4] = 0;
			block[3][0] = 1; block[3][1] = 0; block[3][2] = 0; block[3][3] = 0; block[3][4] = 1;
			block[2][0] = 0; block[2][1] = 0; block[2][2] = 1; block[2][3] = 1; block[2][4] = 0;
			block[1][0] = 0; block[1][1] = 1; block[1][2] = 0; block[1][3] = 0; block[1][4] = 0;
			block[0][0] = 1; block[0][1] = 1; block[0][2] = 1; block[0][3] = 1; block[0][4] = 1;
			break;
		case '3':
			block[4][0] = 0; block[4][1] = 1; block[4][2] = 1; block[4][3] = 1; block[4][4] = 0;
			block[3][0] = 0; block[3][1] = 0; block[3][2] = 0; block[3][3] = 0; block[3][4] = 1;
			block[2][0] = 0; block[2][1] = 1; block[2][2] = 1; block[2][3] = 1; block[2][4] = 0;
			block[1][0] = 0; block[1][1] = 0; block[1][2] = 0; block[1][3] = 0; block[1][4] = 1;
			block[0][0] = 0; block[0][1] = 1; block[0][2] = 1; block[0][3] = 1; block[0][4] = 0;
			break;
		case '4':
			block[4][0] = 0; block[4][1] = 0; block[4][2] = 0; block[4][3] = 1; block[4][4] = 0;
			block[3][0] = 0; block[3][1] = 0; block[3][2] = 1; block[3][3] = 1; block[3][4] = 0;
			block[2][0] = 0; block[2][1] = 1; block[2][2] = 0; block[2][3] = 1; block[2][4] = 0;
			block[1][0] = 1; block[1][1] = 1; block[1][2] = 1; block[1][3] = 1; block[1][4] = 1;
			block[0][0] = 0; block[0][1] = 0; block[0][2] = 0; block[0][3] = 1; block[0][4] = 0;
			break;
		case '5':
			block[4][0] = 0; block[4][1] = 1; block[4][2] = 1; block[4][3] = 1; block[4][4] = 1;
			block[3][0] = 0; block[3][1] = 1; block[3][2] = 0; block[3][3] = 0; block[3][4] = 0;
			block[2][0] = 0; block[2][1] = 1; block[2][2] = 1; block[2][3] = 1; block[2][4] = 0;
			block[1][0] = 0; block[1][1] = 0; block[1][2] = 0; block[1][3] = 0; block[1][4] = 1;
			block[0][0] = 0; block[0][1] = 1; block[0][2] = 1; block[0][3] = 1; block[0][4] = 0;
			break;
		case '6':
			block[4][0] = 0; block[4][1] = 1; block[4][2] = 1; block[4][3] = 1; block[4][4] = 0;
			block[3][0] = 1; block[3][1] = 0; block[3][2] = 0; block[3][3] = 0; block[3][4] = 0;
			block[2][0] = 1; block[2][1] = 1; block[2][2] = 1; block[2][3] = 1; block[2][4] = 0;
			block[1][0] = 1; block[1][1] = 0; block[1][2] = 0; block[1][3] = 0; block[1][4] = 1;
			block[0][0] = 0; block[0][1] = 1; block[0][2] = 1; block[0][3] = 1; block[0][4] = 0;
			break;
		case '7':
			block[4][0] = 1; block[4][1] = 1; block[4][2] = 1; block[4][3] = 1; block[4][4] = 0;
			block[3][0] = 0; block[3][1] = 0; block[3][2] = 0; block[3][3] = 1; block[3][4] = 0;
			block[2][0] = 0; block[2][1] = 0; block[2][2] = 1; block[2][3] = 0; block[2][4] = 0;
			block[1][0] = 0; block[1][1] = 0; block[1][2] = 1; block[1][3] = 0; block[1][4] = 0;
			block[0][0] = 0; block[0][1] = 0; block[0][2] = 1; block[0][3] = 0; block[0][4] = 0;
			break;
		case '8':
			block[4][0] = 0; block[4][1] = 1; block[4][2] = 1; block[4][3] = 1; block[4][4] = 0;
			block[3][0] = 1; block[3][1] = 0; block[3][2] = 0; block[3][3] = 0; block[3][4] = 1;
			block[2][0] = 0; block[2][1] = 1; block[2][2] = 1; block[2][3] = 1; block[2][4] = 0;
			block[1][0] = 1; block[1][1] = 0; block[1][2] = 0; block[1][3] = 0; block[1][4] = 1;
			block[0][0] = 0; block[0][1] = 1; block[0][2] = 1; block[0][3] = 1; block[0][4] = 0;
			break;
		case '9':
			block[4][0] = 0; block[4][1] = 1; block[4][2] = 1; block[4][3] = 1; block[4][4] = 0;
			block[3][0] = 1; block[3][1] = 0; block[3][2] = 0; block[3][3] = 0; block[3][4] = 1;
			block[2][0] = 0; block[2][1] = 1; block[2][2] = 1; block[2][3] = 1; block[2][4] = 1;
			block[1][0] = 0; block[1][1] = 0; block[1][2] = 0; block[1][3] = 0; block[1][4] = 1;
			block[0][0] = 0; block[0][1] = 1; block[0][2] = 1; block[0][3] = 1; block[0][4] = 0;
			break;
		case '/':
			block[4][0] = 0; block[4][1] = 0; block[4][2] = 0; block[4][3] = 0; block[4][4] = 1;
			block[3][0] = 0; block[3][1] = 0; block[3][2] = 0; block[3][3] = 1; block[3][4] = 0;
			block[2][0] = 0; block[2][1] = 0; block[2][2] = 1; block[2][3] = 0; block[2][4] = 0;
			block[1][0] = 0; block[1][1] = 1; block[1][2] = 0; block[1][3] = 0; block[1][4] = 0;
			block[0][0] = 1; block[0][1] = 0; block[0][2] = 0; block[0][3] = 0; block[0][4] = 0;
			break;
		default:
			block[4][0] = 0; block[4][1] = 0; block[4][2] = 0; block[4][3] = 0; block[4][4] = 0;
			block[3][0] = 0; block[3][1] = 0; block[3][2] = 0; block[3][3] = 0; block[3][4] = 0;
			block[2][0] = 0; block[2][1] = 0; block[2][2] = 0; block[2][3] = 0; block[2][4] = 0;
			block[1][0] = 0; block[1][1] = 0; block[1][2] = 0; block[1][3] = 0; block[1][4] = 0;
			block[0][0] = 0; block[0][1] = 0; block[0][2] = 0; block[0][3] = 0; block[0][4] = 0;
			break;
		}
		//描画
		glDrawStr(block);
		glPopMatrix();
	}
}

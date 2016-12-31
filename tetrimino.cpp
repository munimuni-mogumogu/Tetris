#include "tetris.h"
#include "time.h"
#include <cmath>
#include <iostream>

Tetrimino::Tetrimino() {
	srand((unsigned int)time(NULL));
	for (int i = 0; MINO_HEIGHT; i++)
		for (int j = 0; MINO_WIDTH; j++)
			mino[i][j] = false;
}

TmpPoint Tetrimino::getXY() {
	TmpPoint tmp;
	tmp.x = x;
	tmp.y = y;
	return tmp;
}

/* ミノ配列の取得 */
/* 戻り値はtmp構造体 */
TmpMino Tetrimino::getMino() {
	TmpMino tmp;
	for (int i = 0; i < MINO_HEIGHT; i++)
		for (int j = 0; j < MINO_WIDTH; j++)
			tmp.mino[i][j] = mino[i][j];
	return tmp;
}

void Tetrimino::setMino(TmpMino tmp) {
	for (int i = 0; i < MINO_HEIGHT; i++)
		for (int j = 0; j < MINO_WIDTH; j++)
			mino[i][j] = tmp.mino[i][j];
}

void Tetrimino::setPoint(TmpPoint tmp) {
	x = tmp.x;
	y = tmp.y;
}

/* テトリミノ生成 */
/* テトリミノは最大 3 * 3 の大きさで中央だけは固定 */
/* 他はランダムで生成される */
void Tetrimino::create() {
	x = BOARD_WIDTH + 2;		/* (NEXT)初期位置 */
	y = 0;						/* (NEXT)初期位置 */
	
	mino[1][1] = true;

	for (int i = 0; i < MINO_HEIGHT; i++) {
		for (int j = 0; j < MINO_WIDTH; j++) {
			if (i == 1 && j == 1) continue;
			mino[i][j] = (rand() % 4 == 1) ? true : false;
		}
	}
	/* create デバッグ用 */
	/*
	for (int i = 0; i < MINO_HEIGHT; i++) {
		for (int j = 0; j < MINO_WIDTH; j++) {
			std::cout << mino[MINO_HEIGHT - 1 - i][j];
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	*/
}

/* テトリミノを回転させる */
/* 引数 : bool 回転方向*/
/* vec == 1 : 右回転 */
/* vec == 0 : 左回転 */
void Tetrimino::rotate(bool vec) {
	int horVec;	/* 横ベクトル -1 : 左, 1 : 右 */
	int verVec;	/* 縦ベクトル -1 : 上, 1 : 下 */
	bool temp = mino[0][0];
	bool temp2;
	if (!vec) {
		verVec = 0;
		horVec = 1;
		for (int i = 0, x = 0, y = 0; i < 8; i++) {
			switch (i) {
			case 2 :
				verVec = 1;
				horVec = 0;
				break;
			case 4 :
				verVec = 0;
				horVec = -1;
				break;
			case 6:
				verVec = -1;
				horVec = 0;
				break;
			}
			x += horVec;
			y += verVec;
			temp2 = temp;
			temp = mino[y][x];
			mino[y][x] = temp2;
		}
	}
	else {
		verVec = 1;
		horVec = 0;
		for (int i = 0, x = 0, y = 0; i < 8; i++) {
			switch (i) {
			case 2:
				verVec = 0;
				horVec = 1;
				break;
			case 4:
				verVec = -1;
				horVec = 0;
				break;
			case 6:
				verVec = 0;
				horVec = -1;
				break;
			}
			x += horVec;
			y += verVec;
			temp2 = temp;
			temp = mino[y][x];
			mino[y][x] = temp2;
		}
	}
}

/* テトリミノを任意の方向に移動させる */
/* 引数 int, int 横方向ベクトル, 縦方向ベクトル */
/* horVec = -1 : 左, 1 : 右 */
/* verVec = -1 : 下, 1 : 上 */ 
bool Tetrimino::translate(int horVec, int verVec, Board* b) {
	/*
	for (int i = 0; i < MINO_HEIGHT; i++) {
		for (int j = 0; j < MINO_WIDTH; j++) {
			std::cout << mino[MINO_HEIGHT - 1 - i][j];
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	*/
	if (verVec == -1) {
		if (b->landCheck(*this)) {
			b->set(*this);
			return true;
		}
	}
	if (!b->translateCheck(*this, horVec, verVec)) return false;
	this->x += horVec;
	this->y += verVec;
	return false;
}
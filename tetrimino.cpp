#include "tetris.h"
#include "time.h"
#include <cmath>
#include <iostream>

Tetrimino::Tetrimino() {
	srand((unsigned int)time(NULL));
}

bool* Tetrimino::getMino() {
	bool temp[9];
	for (int i = 0; i < 9; i++) {
		temp[i] = mino[i / 3][i % 3];
	}
	return temp;
}

/* テトリミノ生成 */
/* テトリミノは最大 3 * 3 の大きさで中央だけは固定 */
/* 他はランダムで生成される */
void Tetrimino::create() {
	x = 5;
	y = 5;
	
	mino[1][1] = true;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (i == 1 && j == 1) continue;
			mino[i][j] = (rand() % 2 == 1) ? true : false;
		}
	}

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
/* verVec = -1 : 上, 1 : 下 */ 
void Tetrimino::translate(int horVec, int verVec, Board* b) {
	if (verVec == 1) {
		if (b->landCheck(*this)) {
			b->set(*this);
		}
	}
	if (!b->translateCheck(*this, horVec, verVec)) return;
	this->x += horVec;
	this->y += verVec;
}
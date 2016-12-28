#include "tetris.h"
#include "time.h"
#include <cmath>

Tetrimino::Tetrimino() {
	srand((unsigned int)time(NULL));
}

/* テトリミノ生成 */
/* テトリミノは最大 3 * 3 の大きさで中央だけは固定 */
/* 他はランダムで生成される */
void Tetrimino::create() {
	x = 4;
	y = 4;
	
	mino[1][1] = 1;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			mino[i][j] = rand() % 2;
		}
	}
}

/* テトリミノを回転させる */
/* 引数 : bool 回転方向*/
/* vec == 1 : 右回転 */
/* vec == 0 : 左回転 */
void Tetrimino::rotate(bool vec) {
	int verVec;	/* 縦ベクトル -1 : 左, 1 : 右 */
	int horVec;	/* 横ベクトル -1 : 上, 1 : 下 */
	bool temp = mino[0][0];

	if (vec == true) {
		for (int i = 0, int x = 0, int y = 0, verVec = 1, horVec = 0; i < 8; i++) {
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
			temp ^= mino[x + horVec][y + verVec];
			mino[x + horVec][y + verVec] ^= temp;
			temp ^= mino[x + horVec][y + verVec];
		}
	}
	else {
		for (int i = 0, int x = 0, int y = 0, verVec = 0, horVec = 1; i < 8; i++) {
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
			temp ^= mino[x + horVec][y + verVec];
			mino[x + horVec][y + verVec] ^= temp;
			temp ^= mino[x + horVec][y + verVec];
		}
	}
}

/* テトリミノを任意の方向に移動させる */
/* 引数 int, int 横方向ベクトル, 縦方向ベクトル */
/* horVec = -1 : 左, 1 : 右 */
/* verVec = -1 : 下, 1 : 上 */ 
void Tetrimino::translate(int horVec, int verVec) {
	this->x += horVec;
	this->y += verVec;
}
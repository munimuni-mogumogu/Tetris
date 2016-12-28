#include "tetris.h"
#include "time.h"
#include <cmath>

Tetrimino::Tetrimino() {
	srand((unsigned int)time(NULL));
}

/* �e�g���~�m���� */
/* �e�g���~�m�͍ő� 3 * 3 �̑傫���Œ��������͌Œ� */
/* ���̓����_���Ő�������� */
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

/* �e�g���~�m����]������ */
/* ���� : bool ��]����*/
/* vec == 1 : �E��] */
/* vec == 0 : ����] */
void Tetrimino::rotate(bool vec) {
	int verVec;	/* �c�x�N�g�� -1 : ��, 1 : �E */
	int horVec;	/* ���x�N�g�� -1 : ��, 1 : �� */
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

/* �e�g���~�m��C�ӂ̕����Ɉړ������� */
/* ���� int, int �������x�N�g��, �c�����x�N�g�� */
/* horVec = -1 : ��, 1 : �E */
/* verVec = -1 : ��, 1 : �� */ 
void Tetrimino::translate(int horVec, int verVec) {
	this->x += horVec;
	this->y += verVec;
}
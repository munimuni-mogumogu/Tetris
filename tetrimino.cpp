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

/* �e�g���~�m���� */
/* �e�g���~�m�͍ő� 3 * 3 �̑傫���Œ��������͌Œ� */
/* ���̓����_���Ő�������� */
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

/* �e�g���~�m����]������ */
/* ���� : bool ��]����*/
/* vec == 1 : �E��] */
/* vec == 0 : ����] */
void Tetrimino::rotate(bool vec) {
	int horVec;	/* ���x�N�g�� -1 : ��, 1 : �E */
	int verVec;	/* �c�x�N�g�� -1 : ��, 1 : �� */
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

/* �e�g���~�m��C�ӂ̕����Ɉړ������� */
/* ���� int, int �������x�N�g��, �c�����x�N�g�� */
/* horVec = -1 : ��, 1 : �E */
/* verVec = -1 : ��, 1 : �� */ 
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
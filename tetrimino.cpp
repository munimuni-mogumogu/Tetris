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

/* �~�m�z��̎擾 */
/* �߂�l��tmp�\���� */
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

/* �e�g���~�m���� */
/* �e�g���~�m�͍ő� 3 * 3 �̑傫���Œ��������͌Œ� */
/* ���̓����_���Ő�������� */
void Tetrimino::create() {
	x = BOARD_WIDTH + 2;		/* (NEXT)�����ʒu */
	y = 0;						/* (NEXT)�����ʒu */
	
	mino[1][1] = true;

	for (int i = 0; i < MINO_HEIGHT; i++) {
		for (int j = 0; j < MINO_WIDTH; j++) {
			if (i == 1 && j == 1) continue;
			mino[i][j] = (rand() % 4 == 1) ? true : false;
		}
	}
	/* create �f�o�b�O�p */
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
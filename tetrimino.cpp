#include "tetris.h"
#include "time.h"
#include <cmath>
#include <iostream>

TetriminoTemplate Tetrimino::TetriminoTemp = TetriminoTemplate();

Tetrimino::Tetrimino() {
	srand((unsigned int)time(NULL));
	for (int i = 0; i < MINO_HEIGHT; i++)
		for (int j = 0; j < MINO_WIDTH; j++)
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

void Tetrimino::clear() {
	for (int i = 0; i < MINO_HEIGHT; i++)
		for (int j = 0; j < MINO_WIDTH; j++)
			mino[i][j] = 0;
}

/* �e�g���~�m���� */
/* �e�g���~�m�͍ő� 3 * 3 �̑傫���Œ��������͌Œ� */
/* ���̓����_���Ő�������� */
void Tetrimino::create(int mode) {
	x = BOARD_WIDTH + 2;		/* (NEXT)�����ʒu */
	y = 0;						/* (NEXT)�����ʒu */
	clear();
	mino[1][1] = true;
	if (mode == 0) {
		for (int i = 0; i < MINO_HEIGHT; i++) {
			for (int j = 0; j < MINO_WIDTH; j++) {
				if (i == 1 && j == 1) continue;
				mino[i][j] = (rand() % 2 == 1) ? true : false;
			}
		}
	}
	else if (mode == 1) {
		int loopCounter = 0;
		while (loopCounter < 3) {
			int random = rand() % 9;
			if (mino[random / 3][random % 3] == false) {
				mino[random / 3][random % 3] = true;
				loopCounter++;
			}
		}
	}
	else if (mode == 2) {
		int ran = rand() % 7;
		for (int i = 0; i < MINO_HEIGHT; i++) {
			for (int j = 0; j < MINO_WIDTH; j++) {
				mino[i][j] = TetriminoTemp.getTemplate(ran).mino[i][j];
			}
		}
		for (int i = 0; i < rand() % 3; i++)
			createRotate();
	}
	red = rand() % 2;
	green = rand() % 2;
	blue = rand() % 2;

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

void Tetrimino::createRotate() {
	bool tmp[MINO_HEIGHT][MINO_WIDTH];

	for (int i = 0; i < MINO_HEIGHT; i++)
		for (int j = 0; j < MINO_WIDTH; j++)
			tmp[j][MINO_HEIGHT - 1 - i] = mino[i][j];

	for (int i = 0; i < MINO_HEIGHT; i++)
		for (int j = 0; j < MINO_WIDTH; j++)
			mino[i][j] = tmp[i][j];
}

/* �e�g���~�m����]������ */
/* ���� : bool ��]����*/
/* vec == 1 : �E��] */
/* vec == 0 : ����] */
void Tetrimino::rotate(bool vec, Board* b) {
	Tetrimino tmpMino = *this;
	bool tmp[MINO_HEIGHT][MINO_WIDTH];

	if (vec) 
		for (int i = 0; i < MINO_HEIGHT; i++)
			for (int j = 0; j < MINO_WIDTH; j++)
				tmp[j][MINO_HEIGHT - 1 - i] = mino[i][j];
	else
		for (int i = 0; i < MINO_HEIGHT; i++)
			for (int j = 0; j < MINO_WIDTH; j++)
				tmp[MINO_WIDTH - 1 - j][i] = mino[i][j];

	for (int i = 0; i < MINO_HEIGHT; i++)
		for (int j = 0; j < MINO_WIDTH; j++)
			mino[i][j] = tmp[i][j];

	switch (thouchWall()) {
	case 0:		/* �ǂɂ͐G��Ă��Ȃ� */
		break;
	case 1:		/* ���ǂɐG��Ă��� */
		this->x++;
		break;
	case 2:		/* �E�ǂɐG��Ă��� */
		this->x--;
		break;
	}

	if (thouchMino(b)) this->y++;
	if (thouchMino(b)) *this = tmpMino;
}

/* �e�g���~�m��C�ӂ̕����Ɉړ������� */
/* ���� int, int, bool �������x�N�g��, �c�����x�N�g�� */
/* horVec = -1 : ��, 1 : �E */
/* verVec = -1 : ��, 1 : �� */
/* ghost = true : ���̂�����������ł͂Ȃ�, true : ���̂����� */
/* �߂�l bool �e�g���~�m�����n�������ǂ�����2�l�ŕԂ� */
bool Tetrimino::translate(int horVec, int verVec, bool ghost, Board* b) {
	if (verVec == -1) {
		if (b->landCheck(*this)) {
			if (!ghost) b->set(*this);
			return true;
		}
	}
	else
		if (!b->translateCheck(*this, horVec, verVec)) return false;
	this->x += horVec;
	this->y += verVec;
	return false;
}

int Tetrimino::thouchWall() {
	if (this->x == 0 && (mino[0][0] || mino[1][0] || mino[2][0])) return 1;
	if (this->x == BOARD_WIDTH - 3 && (mino[0][2] || mino[1][2] || mino[2][2])) return 2;
	return 0;
}

bool Tetrimino::thouchMino(Board* b) {
	TmpBoard tmp = b->getBoard();
	for (int i = 0; i < MINO_HEIGHT; i++)
		for (int j = 0; j < MINO_WIDTH; j++)
			if (mino[i][j] && tmp.board[this->y + i][this->x + j]) return true;
	return false;
}
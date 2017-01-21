#include "tetrimino3d.h"

/* library header */
#include "board3d.h"
#include "tmp_struct.h"

#include <cmath>
#include "time.h"

Tetrimino3D::Tetrimino3D() {
	srand((unsigned int)time(NULL));
	for (int i = 0; i < MINO_DEPTH; i++)
		for (int j = 0; j < MINO_HEIGHT; j++)
			for (int k = 0; k < MINO_WIDTH; k++)
				mino[i][j][k] = false;
}

TmpPoint3D Tetrimino3D::getXYZ() {
	TmpPoint3D tmp;
	tmp.x = x;
	tmp.y = y;
	tmp.z = z;
	return tmp;
}

TmpMino3D Tetrimino3D::getMino() {
	TmpMino3D tmp;
	for (int i = 0; i < MINO_DEPTH; i++)
		for (int j = 0; j < MINO_HEIGHT; j++)
			for (int k = 0; k < MINO_WIDTH; k++)
				tmp.mino[i][j][k] = mino[i][j][k];
	return tmp;
}

void Tetrimino3D::setMino(TmpMino3D tmp) {
	for (int i = 0; i < MINO_DEPTH; i++)
		for (int j = 0; j < MINO_HEIGHT; j++)
			for (int k = 0; k < MINO_WIDTH; k++)
				mino[i][j][k] = tmp.mino[i][j][k];
}

void Tetrimino3D::setColor(double r, double g, double b) {
	red = r;
	green = g;
	blue = b;
}

void Tetrimino3D::setPoint(TmpPoint3D tmp) {
	x = tmp.x;
	y = tmp.y;
	z = tmp.z;
}

void Tetrimino3D::create() {
	x = BOARD_WIDTH + 2;
	y = 0;
}

void Tetrimino3D::clear() {
	for (int i = 0; i < MINO_DEPTH; i++)
		for (int j = 0; j < MINO_HEIGHT; j++)
			for (int k = 0; k < MINO_WIDTH; k++)
				mino[i][j][k] = false;
}

void Tetrimino3D::rotate(bool vec, bool x_axis, bool y_axis, bool z_axis, Board3D* b) {
	Tetrimino3D tmpMino = *this;
	bool tmp[MINO_DEPTH][MINO_HEIGHT][MINO_WIDTH];

	if (vec) {
		for (int i = 0; i < MINO_DEPTH; i++) {
			for (int j = 0; j < MINO_HEIGHT; j++) {
				for (int k = 0; k < MINO_WIDTH; k++) {
					if (x_axis) tmp[j][MINO_DEPTH - 1 - i][k] = mino[i][j][k];
					if (y_axis) tmp[k][j][MINO_DEPTH - 1 - i] = mino[i][j][k];
					if (z_axis) tmp[i][k][MINO_HEIGHT - 1 - j] = mino[i][j][k];
				}
			}
		}
		for (int i = 0; i < MINO_DEPTH; i++) {
			for (int j = 0; j < MINO_HEIGHT; j++) {
				for (int k = 0; k < MINO_WIDTH; k++) {
					if (x_axis) tmp[MINO_WIDTH - 1 - j][i][k] = mino[i][j][k];
					if (y_axis) tmp[MINO_HEIGHT - 1 - j][j][i] = mino[i][j][k];
					if (z_axis) tmp[i][MINO_DEPTH - 1 - k][j] = mino[i][j][k];
				}
			}
		}
	}

	for (int i = 0; i < MINO_DEPTH; i++)
		for (int j = 0; j < MINO_HEIGHT; j++)
			for (int k = 0; k < MINO_WIDTH; k++)
				mino[i][j][k] = tmp[i][j][k];
	
	switch (thouchWall()) {
	case 0:
		break;
	case 1:
		this->x++;
		break;
	case 2:
		this->z++;
		break;
	case 3:
		this->x--;
		break;
	case 4:
		this->z--;
		break;
	}

	if (thouchMino(b)) this->y++;
	if (thouchMino(b)) *this = tmpMino;
}

bool Tetrimino3D::translate(int xVec, int yVec, int zVec, bool ghost, Board3D* b) {
	if (xVec == -1) {
		if (b->landCheck(*this)) {
			if (!ghost) b->set(*this);
			return true;
		}
	}
	else
		if (!b->translateCheck(*this, xVec, yVec, zVec)) return false;
	this->x += xVec;
	this->y += yVec;
	this->z += zVec;
	return false;
}

int Tetrimino3D::thouchWall() {
	for (int i = 0; i < MINO_DEPTH; i++) {
		for (int j = 0; j < MINO_HEIGHT; j++) {
			for (int k = 0; k < MINO_WIDTH; k++) {
				if (this->x == 0 && mino[i][j][0]) return 1;
				if (this->z == 0 && mino[0][j][k]) return 2;
				if (this->x == BOARD_WIDTH - 3 && mino[i][j][2]) return 3;
				if (this->z == BOARD_DEPTH - 3 && mino[2][j][k]) return 4;
			}
		}
	}
	return 0;
}

bool Tetrimino3D::thouchMino(Board3D* b) {
	TmpBoard3D tmp = b->getBoard();
	for (int i = 0; i < MINO_DEPTH; i++)
		for (int j = 0; j < MINO_HEIGHT; j++)
			for (int k = 0; k < MINO_WIDTH; k++)
				if (mino[i][j][k] && tmp.board[this->z + i][this->y + j][this->x + k]) return true;
	return false;
}
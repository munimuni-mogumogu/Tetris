#include "board3d.h"

/* library header */
#include "tmp_struct.h"
#include "tetrimino3d.h"
#include "score.h"

Board3D::Board3D() {

}

void Board3D::init() {
	for (int i = 0; i < BOARD_DEPTH; i++) {
		for (int j = 0; j < BOARD_HEIGHT; j++) {
			for (int k = 0; k < BOARD_WIDTH; k++) {
				if (i == 0 || j == 0 || k == 0 || i == BOARD_DEPTH - 1 || k == BOARD_WIDTH - 1) {
					board[i][j][k] = true;
					red[i][j][k] = 0;
					green[i][j][k] = 0;
					blue[i][j][k] = 1;
				}
				else {
					board[i][j][k] = false;
					red[i][j][k] = 1;
					green[i][j][k] = 1;
					blue[i][j][k] = 1;
				}
			}
		}
	}
}

TmpBoard3D Board3D::getBoard() {
	TmpBoard3D tmp;
	for (int i = 0; i < BOARD_DEPTH; i++) {
		for (int j = 0; j < BOARD_HEIGHT; j++) {
			for (int k = 0; k < BOARD_WIDTH; k++) {
				tmp.board[i][j][k] = board[i][j][k];
				tmp.red[i][j][k] = red[i][j][k];
				tmp.green[i][j][k] = green[i][j][k];
				tmp.blue[i][j][k] = blue[i][j][k];
			}
		}
	}
	return tmp;
}

void Board3D::set(Tetrimino3D tm) {
	TmpMino3D tmp = tm.getMino();
	for (int i = 0; i < MINO_DEPTH; i++) {
		for (int j = 0; j < MINO_HEIGHT; j++) {
			for (int k = 0; k < MINO_WIDTH; k++) {
				if (!tmp.mino[i][j][k]) continue;
				board[tm.getZ() + i][tm.getY() + j][tm.getZ() + k] = tmp.mino[i][j][k];
				red[tm.getZ() + i][tm.getY() + j][tm.getZ() + k] = tm.getR();
				green[tm.getZ() + i][tm.getY() + j][tm.getZ() + k] = tm.getG();
				blue[tm.getZ() + i][tm.getY() + j][tm.getZ() + k] = tm.getB();
			}
		}
	}
}

bool Board3D::boardCheck(Score& score) {
	int eraseCounter = 0;
	for (int i = BOARD_HEIGHT - 1; i > 0; i--) {
		if (planeCheck(i)) {
			planeErase(i);
			eraseCounter++;
		}
	}
	if (eraseCounter > 0)
		score.additional(eraseCounter++);
	return (gameOverCheck()) ? true : false;
}

bool Board3D::planeCheck(int plane) {
	for (int i = 0; i < BOARD_DEPTH; i++)
		for (int k = 0; k < BOARD_WIDTH; k++)
			if (!board[i][plane][k]) return false;
	return true;
}

void Board3D::planeErase(int plane) {
	for (int i = 1; i < BOARD_DEPTH - 1; i++) {
		for (int plane_num = plane; plane_num < BOARD_HEIGHT - 1; plane_num++) {
			for (int k = 1; k < BOARD_WIDTH - 1; k++) {
				board[i][plane_num][k] = board[i][plane_num + 1][k];
				red[i][plane_num][k] = red[i][plane_num + 1][k];
				green[i][plane_num][k] = green[i][plane_num + 1][k];
				blue[i][plane_num][k] = blue[i][plane_num + 1][k];
				board[i][plane_num + 1][k] = false;
			}
		}
	}
}

bool Board3D::gameOverCheck() {
	for (int i = 1; i < BOARD_DEPTH - 1; i++)
		for (int k = 1; k < BOARD_WIDTH - 1; k++)
			if (board[i][BOARD_HEIGHT - 1][k] == true) return true;
	return false;
}

bool Board3D::translateCheck(Tetrimino3D tm, int xVec, int yVec, int zVec) {
	for (int i = -1; i < MINO_DEPTH - 1; i++) {
		for (int j = -1; j < MINO_HEIGHT - 1; j++) {
			for (int k = -1; k < MINO_WIDTH - 1; k++) {
				if (!(tm.getMino().mino[i + 1][j + 1][k + 1])) continue;
				if (board[tm.getZ() + i + 1 + zVec][tm.getY() + j + 1][tm.getX() + k + 1 + xVec])
					return false;
			}
		}
	}
	return true;
}

bool Board3D::landCheck(Tetrimino3D tm) {
	for (int i = -1; i < MINO_DEPTH - 1; i++) {
		for (int j = -1; j < MINO_HEIGHT - 1; j++) {
			for (int k = -1; k < MINO_WIDTH - 1; k++) {
				return true;
			}
		}
	}
	return false;
}
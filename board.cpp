#include "tetris.h"

Board::Board() {
	
}

/* 盤面の初期化 */
void Board::init() {
	for (int i = 0; i < BOARD_WIDTH; i++) {
		for (int j = 0; j < BOARD_HEIGHT; j++) {
			if (i == 0 || i == BOARD_WIDTH - 1 || j == 0 || j == BOARD_HEIGHT - 1)
				board[i][j] = true;
			else
				board[i][j] = false;
		}
	}
}

TmpBoard Board::getBoard() {
	TmpBoard tmp;
	for (int i = 0; i < BOARD_WIDTH; i++)
		for (int j = 0; j < BOARD_HEIGHT; j++)
			tmp.board[i][j] = board[i][j];
	return tmp;
}

/* 盤面にミノをセット */
void Board::set(Tetrimino tm) {
	TmpMino tmp = tm.getMino();
	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {
			board[tm.getX() + i][tm.getY() + j] = tmp.mino[i + 1][j + 1];
		}
	}
}

/* 横列消しとゲームオーバーチェック */
bool Board::boardCheck() {
	for (int i = 0; i < BOARD_HEIGHT; i++) {
		if (lineCheck(i)) {
			lineErase(i);
		}
	}
	if (gameOverCheck()) return true;
	return false;
}

bool Board::lineCheck(int line) {
	for (int i = 0; i < BOARD_WIDTH; i++) {
		if (!board[i][line]) return false;
	}
	return true;
}

void Board::lineErase(int line) {
	for (int i = 0; i < BOARD_WIDTH; i++) {
		board[i][line] = false;
	}
	for (int y = line; y > 0; y--) {
		for (int x = 0; x < BOARD_WIDTH; x++) {
			board[x][line] = board[x][line + 1];
		}
	}
	for (int i = 0; i < BOARD_WIDTH; i++)
		board[i][0] = (i == 0 && i == BOARD_WIDTH - 1) ? true : false;
}

bool Board::gameOverCheck() {
	for (int i = 1; i < BOARD_WIDTH - 1; i++) {
		if (board[i][0] == true) return true;
	}
	return false;
}

bool Board::translateCheck(Tetrimino tm, int vv, int hv) {
	TmpMino tmp = tm.getMino();
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (!tmp.mino[i][j]) continue;
			if (board[tm.getX() + i + hv][tm.getY() + j + vv]) return false;
		}
	}
	return true;
}

bool Board::landCheck(Tetrimino tm) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (board[tm.getX() + i][tm.getY() + j + 1]) return true;
		}
	}
	return false;
}
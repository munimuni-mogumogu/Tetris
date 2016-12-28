#include "tetris.h"

Board::Board() {
	
}

/* 盤面の初期化 */
void Board::init() {
	for (int i = 0; i < BOARD_WIDTH; i++) {
		for (int j = 0; j < BOARD_HEIGHT; j++) {
			board[i][j] = false;
		}
	}
}

bool* Board::getBoard() {
	bool temp[BOARD_WIDTH * BOARD_HEIGHT];
	for (int i = 0; i < BOARD_WIDTH; i++) {
		for (int j = 0; j < BOARD_HEIGHT; j++) {
			temp[i * BOARD_HEIGHT + 3] = board[i][j];
		}
	}
	return temp;
}

/* 盤面にミノをセット */
void Board::set(Tetrimino tm) {
	bool* temp = tm.getMino();
	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {
			board[tm.getX() + i][tm.getY() + j] = temp[i + 1 * 3 + j + 1];
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
	bool* temp = tm.getMino();
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (!temp[i * 3 + j]) continue;
			if (board[tm.getX() + i + hv][tm.getY() + j + vv]) return false;
		}
	}
	return true;
}

bool Board::landCheck(Tetrimino tm) {
	bool* temp = tm.getMino();
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (board[tm.getX() + i][tm.getY() + j + 1]) return true;
		}
	}
	return false;
}
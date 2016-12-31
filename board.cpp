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

/* 盤面取得 */
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
	for (int i = 0; i < MINO_SIZE; i++) {
		for (int j = 0; j < MINO_SIZE; j++) {
			board[tm.getX() + i][tm.getY() + j] = tmp.mino[i][j];
		}
	}
}

/* 横列消しとゲームオーバーチェック */
bool Board::boardCheck() {
	for (int i = 0; i < BOARD_HEIGHT; i++)
		if (lineCheck(i)) lineErase(i);
	return (gameOverCheck()) ? true : false;
}

/* 指定した列が全て埋まっているか確認 */
bool Board::lineCheck(int line) {
	for (int i = 0; i < BOARD_WIDTH; i++)
		if (!board[i][line]) return false;
	return true;
}

/* 指定した列を消去 */
/* 指定列より上段の列を一つずつずらす */
void Board::lineErase(int line) {
	for (int i = 1; i < BOARD_WIDTH - 1; i++)
		board[i][line] = false;
	for (int line_num = line; line_num > 0; line_num--) {
		for (int x = 1; x < BOARD_WIDTH - 1; x++)
			board[x][line] = board[x][line + 1];
	}
	for (int i = 0; i < BOARD_WIDTH; i++)
		board[i][0] = (i == 0 && i == BOARD_WIDTH - 1) ? true : false;
}

bool Board::gameOverCheck() {
	for (int i = 1; i < BOARD_WIDTH - 1; i++)
		if (board[i][0] == true) return true;
	return false;
}

bool Board::translateCheck(Tetrimino tm, int vv, int hv) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (!tm.getMino().mino[i][j]) continue;
			if (board[tm.getX() + i + hv][tm.getY() + j + vv]) return false;
		}
	}
	return true;
}

bool Board::landCheck(Tetrimino tm) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (!tm.getMino().mino[i][j]) continue;
			if (board[tm.getX() + i][tm.getY() + j + 2]) return true;
		}
	}
	return false;
}
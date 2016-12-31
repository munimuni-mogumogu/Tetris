#include "tetris.h"

Board::Board() {
	
}

/* 盤面の初期化 */
void Board::init() {
	for (int i = 0; i < BOARD_HEIGHT; i++) {
		for (int j = 0; j < BOARD_WIDTH; j++) {
			if (i == 0 || j == 0 || j == BOARD_WIDTH - 1)
				board[i][j] = true;
			else
				board[i][j] = false;
		}
	}
	/* デバッグ ボードの縦横確認
	for (int j = 0; j < BOARD_WIDTH; j++) board[2][j] = true;
	for (int i = 0; i < BOARD_HEIGHT; i++) board[i][2] = true;
	*/
}

/* 盤面取得 */
TmpBoard Board::getBoard() {
	TmpBoard tmp;
	for (int i = 0; i < BOARD_HEIGHT; i++)
		for (int j = 0; j < BOARD_WIDTH; j++)
			tmp.board[i][j] = board[i][j];
	return tmp;
}

/* 盤面にミノをセット */
void Board::set(Tetrimino tm) {
	TmpMino tmp = tm.getMino();
	for (int i = 0; i < MINO_HEIGHT; i++)
		for (int j = 0; j < MINO_WIDTH; j++)
			board[tm.getY() - i][tm.getX() + j] = tmp.mino[MINO_HEIGHT - 1 - i][j];
}

/* 横列消しとゲームオーバーチェック */
bool Board::boardCheck() {
	for (int i = 1; i < BOARD_HEIGHT - 1; i++)
		if (lineCheck(i)) lineErase(i);
	return (gameOverCheck()) ? true : false;
}

/* 指定した列が全て埋まっているか確認 */
bool Board::lineCheck(int line) {
	for (int j = 0; j < BOARD_WIDTH; j++)
		if (!board[line][j]) return false;
	return true;
}

/* 指定した列を消去 */
/* 指定列より上段の列を一つずつずらす */
void Board::lineErase(int line) {
	for (int j = 1; j < BOARD_WIDTH - 1; j++)
		board[line][j] = false;
	for (int line_num = line; line_num < BOARD_HEIGHT; line_num++)
		for (int j = 1; j < BOARD_WIDTH - 1; j++)
			board[line][j] = board[line + 1][j];
}

bool Board::gameOverCheck() {
	for (int j = 1; j < BOARD_WIDTH - 1; j++)
		if (board[BOARD_HEIGHT - 1][j] == true) return true;
	return false;
}

bool Board::translateCheck(Tetrimino tm, int vv, int hv) {
	for (int i = -1; i < MINO_HEIGHT-1; i++) {
		for (int j = -1; j < MINO_WIDTH-1; j++) {
			if (!(tm.getMino().mino[i][j])) continue;
			if (board[tm.getY() - i + vv][tm.getX() + j + hv]) return false;
		}
	}
	return true;
}

bool Board::landCheck(Tetrimino tm) {
	/*
	for (int i = 0; i < MINO_SIZE; i++) {
		for (int j = 0; j < MINO_SIZE; j++) {
			std::cout << tm.getMino().mino[i][j];
		}
		std::cout << std::endl;
	}
	*/
	for (int i = -1; i < MINO_HEIGHT - 1; i++) {
		for (int j = -1; j < MINO_WIDTH - 1; j++) {
			if (!(tm.getMino().mino[i][j])) continue;
			if (board[tm.getY() - i][tm.getX() + j]) {
				std::cout << tm.getY() - i << std::endl << std::endl;
				return true;
			}
		}
	}
	return false;
}
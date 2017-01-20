#include "board.h"

/* library header */
#include "tmp_struct.h"
#include "tetrimino.h"
#include "score.h"

/* デバッグ用変数 */
// Score score;

Board::Board() {
	
}

/* 盤面の初期化 */
void Board::init() {
	for (int i = 0; i < BOARD_HEIGHT; i++) {
		for (int j = 0; j < BOARD_WIDTH; j++) {
			if (i == 0 || j == 0 || j == BOARD_WIDTH - 1) {
				board[i][j] = true;
				red[i][j] = 0;
				green[i][j] = 0;
				blue[i][j] = 1;
			}
			else {
				board[i][j] = false;
				red[i][j] = 1;
				green[i][j] = 1;
				blue[i][j] = 1;
			}
		}
	}
	/* デバッグ ボードの縦横確認 */
	// for (int j = 0; j < BOARD_WIDTH; j++) board[15][j] = true;
	// for (int i = 0; i < BOARD_HEIGHT; i++) board[i][2] = true;
	
}

/* 盤面取得 */
TmpBoard Board::getBoard() {
	TmpBoard tmp;
	for (int i = 0; i < BOARD_HEIGHT; i++) {
		for (int j = 0; j < BOARD_WIDTH; j++) {
			tmp.board[i][j] = board[i][j];
			tmp.red[i][j] = red[i][j];
			tmp.green[i][j] = green[i][j];
			tmp.blue[i][j] = blue[i][j];
		}
	}
	return tmp;
}

/* 盤面にミノをセット */
void Board::set(Tetrimino tm) {
	TmpMino tmp = tm.getMino();
	for (int i = 0; i < MINO_HEIGHT; i++) {
		for (int j = 0; j < MINO_WIDTH; j++) {
			if (!tmp.mino[i][j]) continue;
			board[tm.getY() + i][tm.getX() + j] = tmp.mino[i][j];
			red[tm.getY() + i][tm.getX() + j] = tm.getR();
			green[tm.getY() + i][tm.getX() + j] = tm.getG();
			blue[tm.getY() + i][tm.getX() + j] = tm.getB();

		}
	}
}

/* 横列消しとゲームオーバーチェック */
bool Board::boardCheck(Score& score) {
	int eraseCounter = 0;
	for (int i = BOARD_HEIGHT - 1; i > 0; i--) {
		if (lineCheck(i)) {
			lineErase(i);
			eraseCounter++;
		}
	}
	if (eraseCounter > 0)
		score.additional(eraseCounter++);
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
	for (int line_num = line; line_num < BOARD_HEIGHT - 1; line_num++) {
		for (int j = 1; j < BOARD_WIDTH - 1; j++) {
			board[line_num][j] = board[line_num + 1][j];
			red[line_num][j] = red[line_num + 1][j];
			green[line_num][j] = green[line_num + 1][j];
			blue[line_num][j] = blue[line_num + 1][j];
			board[line_num + 1][j] = false;
		}
	}
}

bool Board::gameOverCheck() {
	for (int j = 1; j < BOARD_WIDTH - 1; j++)
		if (board[BOARD_HEIGHT - 1][j] == true) return true;
	return false;
}

bool Board::translateCheck(Tetrimino tm, int vv, int hv) {
	for (int i = -1; i < MINO_HEIGHT-1; i++) {
		for (int j = -1; j < MINO_WIDTH-1; j++) {
			if (!(tm.getMino().mino[i + 1][j + 1])) {
				continue;
			}
			if (board[tm.getY() + i + 1][tm.getX() + j + 1 + vv]) {
				// std::cout << tm.getY() << " " << tm.getX() << std::endl;
				// std::cout << tm.getY() + i << " " << tm.getX() + j << std::endl << std::endl;
				return false;
			}
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
			if (!(tm.getMino().mino[i+1][j+1])) continue;
			if (board[tm.getY() + i][tm.getX() + j + 1]) {
				// std::cout << tm.getY() - i << std::endl << std::endl;
				return true;
			}
		}
	}
	return false;
}
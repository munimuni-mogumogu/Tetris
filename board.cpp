#include "tetris.h"

Board::Board() {
	
}

/* �Ֆʂ̏����� */
void Board::init() {
	for (int i = 0; i < BOARD_HEIGHT; i++) {
		for (int j = 0; j < BOARD_WIDTH; j++) {
			if (i == 0 || j == 0 || j == BOARD_WIDTH - 1)
				board[i][j] = true;
			else
				board[i][j] = false;
		}
	}
	/* �f�o�b�O �{�[�h�̏c���m�F */
	// for (int j = 0; j < BOARD_WIDTH; j++) board[15][j] = true;
	// for (int i = 0; i < BOARD_HEIGHT; i++) board[i][2] = true;
	
}

/* �Ֆʎ擾 */
TmpBoard Board::getBoard() {
	TmpBoard tmp;
	for (int i = 0; i < BOARD_HEIGHT; i++)
		for (int j = 0; j < BOARD_WIDTH; j++)
			tmp.board[i][j] = board[i][j];
	return tmp;
}

/* �ՖʂɃ~�m���Z�b�g */
void Board::set(Tetrimino tm) {
	TmpMino tmp = tm.getMino();
	for (int i = 0; i < MINO_HEIGHT; i++) {
		for (int j = 0; j < MINO_WIDTH; j++) {
			if (!tmp.mino[i][j]) continue;
			board[tm.getY() + i][tm.getX() + j] = tmp.mino[i][j];
		}
	}
}

/* ��������ƃQ�[���I�[�o�[�`�F�b�N */
bool Board::boardCheck() {
	for (int i = 1; i < BOARD_HEIGHT - 1; i++)
		if (lineCheck(i)) lineErase(i);
	return (gameOverCheck()) ? true : false;
}

/* �w�肵���񂪑S�Ė��܂��Ă��邩�m�F */
bool Board::lineCheck(int line) {
	for (int j = 0; j < BOARD_WIDTH; j++)
		if (!board[line][j]) return false;
	return true;
}

/* �w�肵��������� */
/* �w������i�̗��������炷 */
void Board::lineErase(int line) {
	for (int j = 1; j < BOARD_WIDTH - 1; j++)
		board[line][j] = false;
	for (int line_num = line; line_num < BOARD_HEIGHT - 1; line_num++) {
		for (int j = 1; j < BOARD_WIDTH - 1; j++) {
			board[line_num][j] = board[line_num + 1][j];
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
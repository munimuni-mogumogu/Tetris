#include "tetris.h"

Board::Board() {
	
}

/* �Ֆʂ̏����� */
void Board::init() {
	for (int i = 0; i < BOARD_HEIGHT; i++) {
		for (int j = 0; j < BOARD_WIDTH; j++) {
			if (i == 0 || i == BOARD_HEIGHT - 1 || j == 0 || j == BOARD_WIDTH - 1)
				board[i][j] = true;
			else
				board[i][j] = false;
		}
	}
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
	for (int i = 0; i < MINO_HEIGHT; i++)
		for (int j = 0; j < MINO_WIDTH; j++)
			board[tm.getX() + i][tm.getY() + j] = tmp.mino[i][j];
}

/* ��������ƃQ�[���I�[�o�[�`�F�b�N */
bool Board::boardCheck() {
	for (int i = 1; i < BOARD_HEIGHT - 1; i++)
		if (lineCheck(i)) lineErase(i);
	return (gameOverCheck()) ? true : false;
}

/* �w�肵���񂪑S�Ė��܂��Ă��邩�m�F */
bool Board::lineCheck(int line) {
	for (int i = 0; i < BOARD_WIDTH; i++)
		if (!board[i][line]) return false;
	return true;
}

/* �w�肵��������� */
/* �w������i�̗��������炷 */
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
	/*
	for (int i = 0; i < MINO_SIZE; i++) {
		for (int j = 0; j < MINO_SIZE; j++) {
			std::cout << tm.getMino().mino[i][j];
		}
		std::cout << std::endl;
	}
	*/
	for (int i = 0; i < MINO_HEIGHT; i++) {
		for (int j = 0; j < MINO_WIDTH; j++) {
			if (!tm.getMino().mino[i][j]) continue;
			if (board[tm.getX() + i][tm.getY() - j - 1]) {
				std::cout << tm.getY() - j - 1 << std::endl << std::endl;
				return true;
			}
		}
	}
	return false;
}
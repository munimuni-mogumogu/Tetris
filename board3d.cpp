#include "board3d.h"

/* library header */
#include "tmp_struct.h"

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
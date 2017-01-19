#ifndef BOARD3D_H
#define BOARD3D_H

#include "tetris.h"

struct TmpBoard3D;

class Board3D {
private:
	bool board[BOARD_DEPTH][BOARD_HEIGHT][BOARD_WIDTH];
	bool red[BOARD_DEPTH][BOARD_HEIGHT][BOARD_WIDTH];
	bool green[BOARD_DEPTH][BOARD_HEIGHT][BOARD_WIDTH];
	bool blue[BOARD_DEPTH][BOARD_HEIGHT][BOARD_WIDTH];
public:
	Board3D();
	void init();
	TmpBoard3D getBoard();
};

#endif
#ifndef TMP_STRUCT_H
#define TMP_STRUCT_H

#include "tetris.h"

struct TmpBoard {
	bool board[BOARD_HEIGHT][BOARD_WIDTH];
	double red[BOARD_HEIGHT][BOARD_WIDTH];
	double green[BOARD_HEIGHT][BOARD_WIDTH];
	double blue[BOARD_HEIGHT][BOARD_WIDTH];
};

struct TmpBoard3D {
	bool board[BOARD_DEPTH][BOARD_HEIGHT][BOARD_WIDTH];
	bool red[BOARD_DEPTH][BOARD_HEIGHT][BOARD_WIDTH];
	bool green[BOARD_DEPTH][BOARD_HEIGHT][BOARD_WIDTH];
	bool blue[BOARD_DEPTH][BOARD_HEIGHT][BOARD_WIDTH];
};

struct TmpMino {
	bool mino[MINO_HEIGHT][MINO_WIDTH];
};

struct TmpPoint {
	int x;
	int y;
};

#endif
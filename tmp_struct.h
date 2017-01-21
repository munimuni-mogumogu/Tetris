#ifndef TMP_STRUCT_H
#define TMP_STRUCT_H

#include "tetris_def.h"

struct TmpBoard {
	bool board[BOARD_HEIGHT][BOARD_WIDTH];
	double red[BOARD_HEIGHT][BOARD_WIDTH];
	double green[BOARD_HEIGHT][BOARD_WIDTH];
	double blue[BOARD_HEIGHT][BOARD_WIDTH];
};

struct TmpBoard3D {
	bool board[BOARD_DEPTH][BOARD_HEIGHT][BOARD_WIDTH];
	double red[BOARD_DEPTH][BOARD_HEIGHT][BOARD_WIDTH];
	double green[BOARD_DEPTH][BOARD_HEIGHT][BOARD_WIDTH];
	double blue[BOARD_DEPTH][BOARD_HEIGHT][BOARD_WIDTH];
};

struct TmpMino {
	bool mino[MINO_HEIGHT][MINO_WIDTH];
};

struct TmpMino3D {
	bool mino[MINO_DEPTH][MINO_HEIGHT][MINO_WIDTH];
};

struct TmpPoint {
	int x;
	int y;
};

struct TmpPoint3D {
	int x;
	int y;
	int z;
};

#endif
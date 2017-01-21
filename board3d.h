#ifndef BOARD3D_H
#define BOARD3D_H

#include "tetris_def.h"

struct TmpBoard3D;
class Tetrimino3D;
class Score;

class Board3D {
private:
	bool board[BOARD_DEPTH][BOARD_HEIGHT][BOARD_WIDTH];
	double red[BOARD_DEPTH][BOARD_HEIGHT][BOARD_WIDTH];
	double green[BOARD_DEPTH][BOARD_HEIGHT][BOARD_WIDTH];
	double blue[BOARD_DEPTH][BOARD_HEIGHT][BOARD_WIDTH];
public:
	Board3D();
	void init();
	TmpBoard3D getBoard();
	void set(Tetrimino3D);
	bool boardCheck(Score&);
	bool planeCheck(int);
	void planeErase(int);
	bool gameOverCheck();
	bool translateCheck(Tetrimino3D, int, int, int);
	bool landCheck(Tetrimino3D);
};

#endif
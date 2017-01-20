#ifndef BOARD_H
#define BOARD_H

#include "tetris_def.h"

struct TmpBoard;
class Score;
class Tetrimino;

class Board {
private:
	bool board[BOARD_HEIGHT][BOARD_WIDTH];
	double red[BOARD_HEIGHT][BOARD_WIDTH];
	double green[BOARD_HEIGHT][BOARD_WIDTH];
	double blue[BOARD_HEIGHT][BOARD_WIDTH];
public:
	Board();
	void init();
	TmpBoard getBoard();
	void set(Tetrimino);
	bool boardCheck(Score&);
	bool lineCheck(int);
	void lineErase(int);
	bool gameOverCheck();
	bool landCheck(Tetrimino);
	bool translateCheck(Tetrimino, int, int);
};

#endif
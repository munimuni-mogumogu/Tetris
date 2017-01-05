#ifndef TETRIS_H
#define TETRIS_H

#include <iostream>
#include <vector>

#define BOARD_WIDTH		12
#define BOARD_HEIGHT	22

#define MINO_WIDTH		3
#define MINO_HEIGHT		3

class Tetrimino;
class Board;

struct TmpBoard {
	bool board[BOARD_HEIGHT][BOARD_WIDTH];
};

struct TmpMino {
	bool mino[MINO_HEIGHT][MINO_WIDTH];
};

struct TmpPoint {
	int x;
	int y;
};

class Tetrimino {
private:
	bool mino[MINO_HEIGHT][MINO_WIDTH];
	int x;
	int y;
public:
	Tetrimino();
	int getX() { return x; }
	int getY() { return y; }
	TmpPoint getXY();
	TmpMino getMino();
	void setMino(TmpMino);
	void setPoint(TmpPoint);
	void create();
	void rotate(bool, Board*);
	bool translate(int, int, bool, Board*);
	int thouchWall();
	bool thouchMino(Board*);
};

class Board {
private:
	bool board[BOARD_HEIGHT][BOARD_WIDTH];
public:
	Board();
	void init();
	TmpBoard getBoard();
	void set(Tetrimino);
	bool boardCheck();
	bool lineCheck(int);
	void lineErase(int);
	bool gameOverCheck();
	bool landCheck(Tetrimino);
	bool translateCheck(Tetrimino, int, int);
};
#endif
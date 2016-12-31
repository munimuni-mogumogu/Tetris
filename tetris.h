#ifndef TETRIS_H
#define TETRIS_H

#define BOARD_WIDTH		12
#define BOARD_HEIGHT	22

#define MINO_SIZE		3

class Tetrimino;
class Board;

struct TmpBoard {
	bool board[BOARD_WIDTH][BOARD_HEIGHT];
};

struct TmpMino {
	bool mino[MINO_SIZE][MINO_SIZE];
};

class Tetrimino {
private:
	bool mino[MINO_SIZE][MINO_SIZE];
	int x;
	int y;
public:
	Tetrimino();
	int getX() { return x; }
	int getY() { return y; }
	TmpMino getMino();
	void create();
	void rotate(bool);
	void translate(int, int, Board*);
};

class Board {
private:
	bool board[BOARD_WIDTH][BOARD_HEIGHT];
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
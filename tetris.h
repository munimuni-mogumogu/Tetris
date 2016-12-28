#ifndef TETRIS_H
#define TETRIS_H

#define BOARD_WIDTH	12
#define BOARD_HEIGHT	22

class Tetrimino;
class Board;

class Tetrimino {
private:
	bool mino[3][3];
	int x;
	int y;
public:
	Tetrimino();
	int getX() { return x; }
	int getY() { return y; }
	bool* getMino();
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
	bool* getBoard();
	void set(Tetrimino);
	bool boardCheck();
	bool lineCheck(int);
	void lineErase(int);
	bool gameOverCheck();
	bool landCheck(Tetrimino);
	bool translateCheck(Tetrimino, int, int);
};
#endif
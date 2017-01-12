#ifndef TETRIS_H
#define TETRIS_H

#include <iostream>
#include <vector>

#define BOARD_WIDTH		12
#define BOARD_HEIGHT	22

#define MINO_WIDTH		3
#define MINO_HEIGHT		3

#define TEMPLATE_PATTERN	7

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

struct TemplatePattern {
	bool mino[MINO_HEIGHT][MINO_WIDTH];
};

class TetriminoTemplate {
private:
	TemplatePattern temp[TEMPLATE_PATTERN];
public:
	TetriminoTemplate();
	void setTemplate(TemplatePattern&, int);
	TemplatePattern getTemplate(int n) { return temp[n]; }
	void copyPtn(TemplatePattern&, TemplatePattern);
};

class Score {
private:
	int score;
	int line;
public:
	Score();
	void clear();
	void additional(int);
	int getScore() { return score; }
	int getLine() { return line; }
};

class Tetrimino {
private:
	static TetriminoTemplate TetriminoTemp;
	bool mino[MINO_HEIGHT][MINO_WIDTH];
	int x;
	int y;
	int red;
	int green;
	int blue;
public:
	Tetrimino();
	int getX() { return x; }
	int getY() { return y; }
	int getR() { return red; }
	int getG() { return green; }
	int getB() { return blue; }
	TmpPoint getXY();
	TmpMino getMino();
	void setMino(TmpMino);
	void setPoint(TmpPoint);
	void create(int = 0);
	void clear();
	void rotate(bool, Board*);
	void createRotate();
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
	bool boardCheck(Score&);
	bool lineCheck(int);
	void lineErase(int);
	bool gameOverCheck();
	bool landCheck(Tetrimino);
	bool translateCheck(Tetrimino, int, int);
};

#endif
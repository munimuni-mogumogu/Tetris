#ifndef TETRIMINO_H
#define TETRIMINO_H

#include "tetris_def.h"

struct TmpPoint;
struct TmpMino;
class TetriminoTemplate;
class Board;

class Tetrimino {
private:
	static TetriminoTemplate TetriminoTemp;
	bool mino[MINO_HEIGHT][MINO_WIDTH];
	int x;
	int y;
	double red;
	double green;
	double blue;
public:
	Tetrimino();
	int getX() { return x; }
	int getY() { return y; }
	double getR() { return red; }
	double getG() { return green; }
	double getB() { return blue; }
	TmpPoint getXY();
	TmpMino getMino();
	void setMino(TmpMino);
	void setColor(double, double, double);
	void setPoint(TmpPoint);
	void create(int = 2);
	void clear();
	void rotate(bool, Board*);
	void createRotate();
	bool translate(int, int, bool, Board*);
	int thouchWall();
	bool thouchMino(Board*);
};

#endif
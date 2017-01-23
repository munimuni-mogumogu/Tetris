#ifndef TETRIMINO3D_H
#define TETRIMINO3D_H

#include "tetris_def.h"

struct TmpMino3D;
struct TmpPoint3D;
class Board3D;
class TetriminoTemplate;

class Tetrimino3D {
private:
	static TetriminoTemplate tetriminoTemp;
	bool mino[MINO_DEPTH][MINO_HEIGHT][MINO_WIDTH];
	int x;
	int y;
	int z;
	double red;
	double green;
	double blue;
public:
	Tetrimino3D();
	int getX() { return x; }
	int getY() { return y; }
	int getZ() { return z; }
	double getR() { return red; }
	double getG() { return green; }
	double getB() { return blue; }
	TmpPoint3D getXYZ();
	TmpMino3D getMino();
	void setMino(TmpMino3D);
	void setColor(double, double, double);
	void setPoint(TmpPoint3D);
	void create(int = 4);
	void clear();
	void rotate(bool, bool, bool, bool, Board3D*);
	bool translate(int, int, int, bool, Board3D*);
	int thouchWall();
	bool thouchMino(Board3D*);
};

#endif
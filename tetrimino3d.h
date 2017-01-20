#ifndef TETRIMINO3D_H
#define TETRIMINO3D_H

#include "tetris_def.h"

struct TmpMino3D;
class Board3D;

class Tetrimino3D {
private:
	bool mino[MINO_DEPTH][MINO_HEIGHT][MINO_WIDTH];
	int x;
	int y;
	int z;
	double red;
	double green;
	double blue;
public:
	Tetrimino3D();
	void create();
	// TmpMino3D getMino();
};

#endif
#ifndef DISPLAY_H
#define DISPLAY_H

#define TETRIS_WIDTH 12
#define TETRIS_HEIGHT 22

#define MINO_WIDTH 3
#define MINO_HEIGHT 3

#define BLOCK_SIZE 10

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600

#define VIEW_DISTANCE 100

struct ViewPoint {
	int x;
	int y;
	int z;
};

struct MousePoint {
	int x;
	int y;
};

#endif

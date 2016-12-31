#ifndef DISPLAY_H
#define DISPLAY_H

#define BOARD_WIDTH 12
#define BOARD_HEIGHT 22

#define MINO_WIDTH 3
#define MINO_HEIGHT 3

#define BLOCK_SIZE 10

#define MENU_SIZE 8

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600

#define GLUT_KEY_ENTER 0x000d

struct Point2 {
	int x;
	int y;
};

struct Point3 {
	int x;
	int y;
	int z;
};

#endif

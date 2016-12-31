#ifndef DRWA_STR_H
#define DRAW_STR_H

#define STR_BLOCK_SIZE 5

class draw_str {
private:
	char* str;
	int color[3];
	void glDrawStr(bool brock[STR_BLOCK_SIZE][STR_BLOCK_SIZE]);
public:
	draw_str();
	draw_str(char[]);
	draw_str(int);
	draw_str(char[], int Red, int Blue, int Green);
	draw_str(int, int Red, int Blue, int Green);
	void draw_block();
};

#endif
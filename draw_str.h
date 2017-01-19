#ifndef DRWA_STR_H
#define DRAW_STR_H

#define STR_BLOCK_SIZE 5
#define LEFT 0
#define CENTER 1

class draw_str {
private:
	char* str;
	GLdouble color[3];
	void glDrawStr(bool brock[STR_BLOCK_SIZE][STR_BLOCK_SIZE]);
	int str_pos;
public:
	draw_str();
	draw_str(char[], GLdouble = 0, GLdouble = 0, GLdouble = 0);
	draw_str(int, GLdouble = 0, GLdouble = 0, GLdouble = 0);
	void set_str(char[], GLdouble = 0, GLdouble = 0, GLdouble = 0);
	void set_str(int ,GLdouble = 0, GLdouble = 0, GLdouble = 0);
	void draw_block(int = LEFT);
};

#endif
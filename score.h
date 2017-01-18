#ifndef SCORE_H
#define SCORE_H

#include <iostream>
#include "tetris.h"

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

#endif
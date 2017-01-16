#include "tetris.h"

Score::Score() {
	clear();
}

void Score::clear() {
	line = 0;
	score = 0;
}

void Score::additional(int lineNum) {
	line += lineNum;
	score += 100 * pow(2, (lineNum - 1) * 2);
	//std::cout << "line = " << line
	//		  << ", score = " << score << std::endl;
}
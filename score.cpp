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
	switch (lineNum) {
	case 1:
		score += lineNum * 100;
		break;
	case 2:
		score += lineNum * 100 * 2;
		break;
	case 3:
		score += lineNum * 100 * 8;
		break;
	default:
		break;
	}
	//std::cout << "line = " << line
	//		  << ", score = " << score << std::endl;
}
#include "tetris.h"

int main(int argc, char* argv[]) {
	Tetris tetris;
	while(tetris.Run(argc, argv))
	return 0;
}
#ifndef TETRIMINO_TEMPLATE_H
#define TETRIMINO_TEMPLATE_H

#include "tetris_def.h"

struct TemplatePattern {
	bool mino[MINO_HEIGHT][MINO_WIDTH];
};

class TetriminoTemplate {
private:
	static TemplatePattern Imino;
	static TemplatePattern Omino;
	static TemplatePattern Tmino;
	static TemplatePattern Jmino;
	static TemplatePattern Lmino;
	static TemplatePattern Smino;
	static TemplatePattern Zmino;
public:
	TetriminoTemplate();
	TemplatePattern getTemplate(int n);
};

#endif
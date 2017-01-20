#ifndef TETRIMINO_TEMPLATE_H
#define TETRIMINO_TEMPLATE_H

#include "tetris_def.h"

struct TemplatePattern {
	bool mino[MINO_HEIGHT][MINO_WIDTH];
};

class TetriminoTemplate {
private:
	TemplatePattern temp[TEMPLATE_PATTERN];
public:
	TetriminoTemplate();
	void setTemplate(TemplatePattern&, int);
	TemplatePattern getTemplate(int n) { return temp[n]; }
	void copyPtn(TemplatePattern&, TemplatePattern);
};

#endif
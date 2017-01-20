#include "tetrimino_template.h"

TetriminoTemplate::TetriminoTemplate() {
	for (int i = 0; i < 7; i++)
		setTemplate(temp[i], i);
}

void TetriminoTemplate::setTemplate(TemplatePattern& ptn, int n) {
	TemplatePattern* tmpPtn;
	switch (n) {
	case 0:
		tmpPtn = new TemplatePattern{ { { false, true, false },
										{ false, true, false },
										{ false, true, false } } };
		// ptn[2][0] = false; ptn[2][1] = true; ptn[2][0] = false;
		// { { false, true, false },
		// 		{ false, true, false },
		// 		{ false, true, false } };
		copyPtn(ptn, *tmpPtn);
		break;
	case 1:
		tmpPtn = new TemplatePattern{ { { false, true , true  },
										{ true , true , false },
										{ false, false, false } } };
		copyPtn(ptn, *tmpPtn);
		break;
	case 2:
		tmpPtn = new TemplatePattern{ { { false, true , true  },
										{ true , true , false },
										{ false, false, false } } };
		copyPtn(ptn, *tmpPtn);
		break;
	case 3:
		tmpPtn = new TemplatePattern{ { { false, true , true  },
										{ false, true , false },
										{ false, true , false } } };
		copyPtn(ptn, *tmpPtn);
		break;
	case 4:
		tmpPtn = new TemplatePattern{ { { true , true , false },
										{ false, true , false },
										{ false, true , false } } };
		copyPtn(ptn, *tmpPtn);
		break;
	case 5:
		tmpPtn = new TemplatePattern{ { { false, false, false },
										{ false, true , true  },
										{ false, true , true  } } };
		copyPtn(ptn, *tmpPtn);
		break;
	case 6:
		tmpPtn = new TemplatePattern{ { { false, true , false },
										{ true , true , true  },
										{ false, false, false } } };
		copyPtn(ptn, *tmpPtn);
		break;
	}
}

void TetriminoTemplate::copyPtn(TemplatePattern& tmpPtn, TemplatePattern tmp) {
	for (int i = 0; i < MINO_HEIGHT; i++)
		for (int j = 0; j < MINO_WIDTH; j++)
			tmpPtn.mino[i][j] = tmp.mino[i][j];
}

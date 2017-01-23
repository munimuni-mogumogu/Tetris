#include "tetrimino_template.h"

TemplatePattern TetriminoTemplate::Imino = { { { false, true , false },
											   { false, true , false },
											   { false, true , false } } };

TemplatePattern TetriminoTemplate::Omino = { { { false, false, false },
											   { false, true , true  },
											   { false, true , true  } } };

TemplatePattern TetriminoTemplate::Tmino = { { { true , true , true  },
											   { false, true , false },
											   { false, false, false } } };

TemplatePattern TetriminoTemplate::Jmino = { { { false, true , false },
											   { false, true , false },
											   { true , true , false } } };

TemplatePattern TetriminoTemplate::Lmino = { { { false, true , false },
											   { false, true , false },
											   { false, true , true  } } };

TemplatePattern TetriminoTemplate::Smino = { { { false, true , true  },
											   { false, true , false },
											   { true , true , false } } };

TemplatePattern TetriminoTemplate::Zmino = { { { true , true , false },
											   { false, true , false },
											   { false, true , true } } };

TetriminoTemplate::TetriminoTemplate() { }

TemplatePattern TetriminoTemplate::getTemplate(int n) {
	switch (n) {
	case 0:
		return Imino;
	case 1:
		return Omino;
	case 2:
		return Tmino;
	case 3:
		return Jmino;
	case 4:
		return Lmino;
	case 5:
		return Smino;
	case 6:
		return Zmino;
	default:
		/* ƒGƒ‰[‰ñ”ğ */
		return Omino;
	}
}
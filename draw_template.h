#ifndef DRAW_TEMPLATE_H
#define DRAW_TEMPLATE_H

#include "GL/freeglut.h"

struct Draw_Rect {
	GLdouble vertex[8][3];
	int face[6][4];
	GLdouble normal[6][3];
	GLdouble vertex2[8][3];

	Draw_Rect();
};

#endif
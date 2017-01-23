#include "draw_template.h"

Draw_Rect::Draw_Rect() {
	vertex[0][0] = -0.49; vertex[0][1] = -0.49; vertex[0][2] = -0.49;
	vertex[1][0] =  0.49; vertex[1][1] = -0.49; vertex[1][2] = -0.49;
	vertex[2][0] =  0.49; vertex[2][1] =  0.49; vertex[2][2] = -0.49;
	vertex[3][0] = -0.49; vertex[3][1] =  0.49; vertex[3][2] = -0.49;
	vertex[4][0] = -0.49; vertex[4][1] = -0.49; vertex[4][2] =  0.49;
	vertex[5][0] =  0.49; vertex[5][1] = -0.49; vertex[5][2] =  0.49;
	vertex[6][0] =  0.49; vertex[6][1] =  0.49; vertex[6][2] =  0.49;
	vertex[7][0] = -0.49; vertex[7][1] =  0.49; vertex[7][2] =  0.49;

	face[0][0] = 3; face[0][1] = 2; face[0][2] = 1; face[0][3] = 0;
	face[1][0] = 1; face[1][1] = 2; face[1][2] = 6; face[1][3] = 5;
	face[2][0] = 4; face[2][1] = 5; face[2][2] = 6; face[2][3] = 7;
	face[3][0] = 0; face[3][1] = 4; face[3][2] = 7; face[3][3] = 3;
	face[4][0] = 0; face[4][1] = 1; face[4][2] = 5; face[4][3] = 4;
	face[5][0] = 2; face[5][1] = 3; face[5][2] = 7; face[5][3] = 6;

	normal[0][0] =  0.0; normal[0][1] =  0.0; normal[0][2] = -1.0;
	normal[1][0] =  1.0; normal[1][1] =  0.0; normal[1][2] =  0.0;
	normal[2][0] =  0.0; normal[2][1] =  0.0; normal[2][2] =  1.0;
	normal[3][0] = -1.0; normal[3][1] =  0.0; normal[3][2] =  0.0;
	normal[4][0] =  0.0; normal[4][1] = -1.0; normal[4][2] =  0.0;
	normal[5][0] =  0.0; normal[5][1] =  1.0; normal[5][2] =  0.0;
	
	vertex2[0][0] = -0.5; vertex2[0][1] = -0.5; vertex2[0][2] = -0.5;
	vertex2[1][0] =  0.5; vertex2[1][1] = -0.5; vertex2[1][2] = -0.5;
	vertex2[2][0] =  0.5; vertex2[2][1] =  0.5; vertex2[2][2] = -0.5;
	vertex2[3][0] = -0.5; vertex2[3][1] =  0.5; vertex2[3][2] = -0.5;
	vertex2[4][0] = -0.5; vertex2[4][1] = -0.5; vertex2[4][2] =  0.5;
	vertex2[5][0] =  0.5; vertex2[5][1] = -0.5; vertex2[5][2] =  0.5;
	vertex2[6][0] =  0.5; vertex2[6][1] =  0.5; vertex2[6][2] =  0.5;
	vertex2[7][0] = -0.5; vertex2[7][1] =  0.5; vertex2[7][2] =  0.5;
}
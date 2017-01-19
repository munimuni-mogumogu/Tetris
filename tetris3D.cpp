#include "tetris.h"

void Tetris::Tetris3D() {
	glutDisplayFunc(Tetris3D_Display);
	glutKeyboardFunc(Tetris3D_Keyboard);
	glutSpecialFunc(Tetris3D_Specialkeyboard);
}

void Tetris::Create_Block3D(bool block[MINO_DEPTH][MINO_HEIGHT][MINO_WIDTH], GLdouble Red = 0, GLdouble Green = 0, GLdouble Blue = 0, GLdouble shadow = 1) {
	glPushMatrix();
	glColor4d(Red, Green, Blue, shadow);
	for(int i = 0; i < MINO_DEPTH; i++) {
		for(int j = 0; j < MINO_HEIGHT; j++){
			for(int k = 0; k < MINO_WIDTH; k++) {
				glPushMatrix();
				glTranslated(k * BLOCK_SIZE, j * BLOCK_SIZE, i * BLOCK_SIZE);
				if(block[i][j][k]) glutSolidCube(BLOCK_SIZE);
				glPopMatrix();
			}
		}
	}
	glPopMatrix();
}

void Tetris::Create_Board3D(bool block[BOARD_DEPTH][BOARD_HEIGHT][BOARD_WIDTH]) {
	for(int i = 0; i < BOARD_DEPTH; i++) {
		for(int j = 0; j < BOARD_HEIGHT; j++){
			for(int k = 0; k < BOARD_WIDTH; k++) {
				glPushMatrix();
				glTranslated(k * BLOCK_SIZE, j * BLOCK_SIZE, i * BLOCK_SIZE);
				if(block[i][j]) {
					if(i == 0 || j == 0 || k == 0 || i == BOARD_DEPTH - 1 || k == BOARD_WIDTH - 1) {
						glColor4d(board.getBoard().red[i][j], board.getBoard().green[i][j], board.getBoard().blue[i][j], 0.4);
					} else {
						glColor3d(board.getBoard().red[i][j], board.getBoard().green[i][j], board.getBoard().blue[i][j]);
					}
					glutSolidCube(BLOCK_SIZE);
				}
			}
			glPopMatrix();
		}
	}
}

void Tetris::Tetris3D_Display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(viewpoint.x + center.x, viewpoint.y + center.y, viewpoint.z + center.z,
		center.x, center.y, center.z,
		0.0, angle_of_top, 0.0);
		glPushMatrix();
	
	glPopMatrix();
	glutSwapBuffers();

}

void Tetris::Tetris3D_Keyboard(unsigned char k, int x, int y) {
	switch(k) {
	case 'v':
		View_Reset();
		break;
	case 'r':
		Tetris_Init();
		mode = 0;
		break;
	case 'l':
		light_check = !light_check;
		if(light_check) glEnable(GL_LIGHTING);
		else glDisable(GL_LIGHTING);
		break;
	default:
		break;
	}
}

void Tetris::Tetris3D_Specialkeyboard(int k, int x, int y) {
	switch(k) {
	case GLUT_KEY_RIGHT:
		break;
	case GLUT_KEY_LEFT:
		break;
	case GLUT_KEY_DOWN:
		break;
	case GLUT_KEY_UP:
		break;
	default:
		break;
	}
}
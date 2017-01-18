#include "tetris.h"

void Tetris::Title() {
	glutDisplayFunc(Title_Display);
	glutKeyboardFunc(Title_Keyboard);
	glutSpecialFunc(Title_Specialkeyboard);
}

void Tetris::Title_Display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(viewpoint.x + center.x, viewpoint.y + center.y, viewpoint.z + center.z,
		center.x, center.y, center.z,
		0.0, angle_of_top, 0.0);

	glPushMatrix();
	glTranslated((BOARD_WIDTH + MENU_SIZE - 15) / 2 * BLOCK_SIZE, (BOARD_HEIGHT / 2 - 3 - (title_pos * 2)) * BLOCK_SIZE - 6, 0);
	glColor3d(1, 0, 0);
	glutSolidSphere(5, 5, 5);
	glPopMatrix();
	glPushMatrix();

	draw_str Title_str("tetris");
	glTranslated((BOARD_WIDTH + MENU_SIZE) / 2 * BLOCK_SIZE,  BOARD_HEIGHT / 2 * BLOCK_SIZE, 0);
	glScaled(6, 6, 6);
	Title_str.draw_block(CENTER);
	glPopMatrix();

	glPushMatrix();
	draw_str Start_str("start tetris");
	glTranslated((BOARD_WIDTH + MENU_SIZE) / 2 * BLOCK_SIZE, (BOARD_HEIGHT / 2 - 4) * BLOCK_SIZE, 0);
	glScaled(2, 2, 2);
	Start_str.draw_block(CENTER);
	glPopMatrix();

	glPushMatrix();
	draw_str ranking_str("ranking");
	glTranslated((BOARD_WIDTH + MENU_SIZE) / 2 * BLOCK_SIZE, (BOARD_HEIGHT / 2 - 6) * BLOCK_SIZE, 0);
	glScaled(2, 2, 2);
	ranking_str.draw_block(CENTER);
	glPopMatrix();

	glutSwapBuffers();
}

void Tetris::Title_Keyboard(unsigned char k, int x, int y) {
	
	switch(k) {
	case GLUT_KEY_ENTER:
		if(title_pos == 0) {
			mode = TETRIS;
			Tetris_Init();
		} else if(title_pos == 1) {
			Set_Get_Ranking();
			mode = RANKING;
		}
		break;
	case 'v':
		View_Reset();
		break;
	case 'r':
		Tetris_Init();
		mode = TITLE;
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

void Tetris::Title_Specialkeyboard(int k, int x, int y) {
	switch(k) {
	case GLUT_KEY_DOWN:
		if(title_pos < 1)title_pos++;
		break;
	case GLUT_KEY_UP:
		if(title_pos > 0)title_pos--;
		break;
	default:
		break;
	}
}
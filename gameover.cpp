#include "tetris.h"

void Tetris::Gameover() {
	glutDisplayFunc(Gameover_Display);
	glutKeyboardFunc(Gameover_Keyboard);
	glutSpecialFunc(Gameover_Specialkeyboard);
}

void Tetris::Gameover_Display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(viewpoint.x + center.x, viewpoint.y + center.y, viewpoint.z + center.z,
		center.x, center.y, center.z,
		0.0, angle_of_top, 0.0);

	if(page == 0) Create_Board(board.getBoard().board);
	else if(page == 1) Create_Board3D(board3d.getBoard().board);
	Draw_Information(score.getScore(), score.getLine());

	draw_str gameover_str("gameover", 1, 0, 0);
	glPushMatrix();
	glTranslated((BOARD_WIDTH + MENU_SIZE) / 2 * BLOCK_SIZE, BOARD_HEIGHT / 2 * BLOCK_SIZE, 30);
	glScaled(4, 4, 4);
	gameover_str.draw_block(CENTER);
	glPopMatrix();

	draw_str end_str("please push enter ", 1, 0, 0);
	glPushMatrix();
	glTranslated((BOARD_WIDTH + MENU_SIZE) / 2 * BLOCK_SIZE, (BOARD_HEIGHT - 4) / 2 * BLOCK_SIZE, 30);
	glScaled(2, 2, 2);
	end_str.draw_block(CENTER);
	glPopMatrix();

	glutSwapBuffers();
}

void Tetris::Gameover_Keyboard(unsigned char k, int x, int y) {
	switch(k) {
	case GLUT_KEY_ENTER:
		if(page == 0) Set_Get_Ranking(RANKINGTXT);
		else if(page == 1) Set_Get_Ranking(RANKING3DTXT);
		mode = RANKING;
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

void Tetris::Gameover_Specialkeyboard(int k, int x, int y) {
	switch(k) {
	case GLUT_KEY_UP:
	default:
		break;
	}
}
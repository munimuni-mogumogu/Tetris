#include "tetris.h"

void Tetris::Tetris_Main() {
	glutDisplayFunc(Tetris_Display);
	glutKeyboardFunc(Tetris_Keyboard);
	glutSpecialFunc(Tetris_Specialkeyboard);
}

void Tetris::Create_Block(bool block[MINO_HEIGHT][MINO_WIDTH], GLdouble Red = 0, GLdouble Green = 0, GLdouble Blue = 0, GLdouble shadow = 1) {
	glPushMatrix();
	if(shadow != 1) glDepthMask(GL_FALSE);
	glColor4d(Red, Green, Blue, shadow);
	for(int i = 0; i < MINO_HEIGHT; i++) {
		for(int j = 0; j < MINO_WIDTH; j++){
			glPushMatrix();
			glTranslated(j * BLOCK_SIZE, i * BLOCK_SIZE, 0.0);
			if(block[i][j]) glutSolidCube(BLOCK_SIZE);
			glPopMatrix();
		}
	}
	glDepthMask(GL_TRUE);
	glPopMatrix();
}

void Tetris::Create_Board(bool block[BOARD_HEIGHT][BOARD_WIDTH]) {
	for(int i = 0; i < BOARD_HEIGHT; i++) {
		for(int j = 0; j < BOARD_WIDTH; j++){
			glPushMatrix();
			glTranslated(j * BLOCK_SIZE, i * BLOCK_SIZE, 0.0);
			if(block[i][j]) {
				if(i == 0 || j == 0 || j == BOARD_WIDTH - 1) {
					glDepthMask(GL_FALSE);
					glColor4d(board.getBoard().red[i][j], board.getBoard().green[i][j], board.getBoard().blue[i][j], 0.4);
				} else {
					glDepthMask(GL_TRUE);
					glColor3d(board.getBoard().red[i][j], board.getBoard().green[i][j], board.getBoard().blue[i][j]);
				}
				glutSolidCube(BLOCK_SIZE);
			}
			glPopMatrix();
		}
	}
	glDepthMask(GL_TRUE);
}

void Tetris::Next_Mino() {
	tetrimino.setMino(nextmino.getMino());
	tetrimino.setColor(nextmino.getR(), nextmino.getG(),nextmino.getB());
	nextmino.create();
	tetrimino.setPoint(mino_pos);
}

void Tetris::Mino_Hold() {
	hold_check = false;
	TmpMino temp = holdmino.getMino();
	double color[3] = { holdmino.getR(), holdmino.getG(), holdmino.getB() };
	if(temp.mino[1][1] == false) {
		holdmino.setMino(tetrimino.getMino());
		holdmino.setColor(tetrimino.getR(), tetrimino.getG(), tetrimino.getB());
		Next_Mino();
	} else {
		holdmino.setMino(tetrimino.getMino());
		holdmino.setColor(tetrimino.getR(), tetrimino.getG(), tetrimino.getB());
		tetrimino.setMino(temp);
		tetrimino.setColor(color[0], color[1], color[2]);
		tetrimino.setPoint(mino_pos);
	}
}

void Tetris::Draw_Information(int score, int line) {
	glPushMatrix();
	draw_str score_str("score");
	glTranslated((BOARD_WIDTH + 1) * BLOCK_SIZE, (BOARD_HEIGHT - 2) * BLOCK_SIZE, 0);
	glScaled(2, 2, 0);
	score_str.draw_block();
	glPopMatrix();

	glPushMatrix();
	draw_str draw_score(score);
	glTranslated((BOARD_WIDTH + 1) * BLOCK_SIZE, (BOARD_HEIGHT - 4) * BLOCK_SIZE, 0);
	glScaled(2, 2, 0);
	draw_score.draw_block();
	glPopMatrix();

	glPushMatrix();
	draw_str line_str("line");
	glTranslated((BOARD_WIDTH + 1) * BLOCK_SIZE, (BOARD_HEIGHT - 6) * BLOCK_SIZE, 0);
	glScaled(2, 2, 0);
	line_str.draw_block();
	glPopMatrix();

	glPushMatrix();
	draw_str draw_line(line);
	glTranslated((BOARD_WIDTH + 1) * BLOCK_SIZE, (BOARD_HEIGHT - 8) * BLOCK_SIZE, 0);
	glScaled(2, 2, 0);
	draw_line.draw_block();
	glPopMatrix();

	glPushMatrix();
	draw_str hold_str("hold");
	glTranslated((BOARD_WIDTH + 1) * BLOCK_SIZE, (BOARD_HEIGHT - 11) * BLOCK_SIZE, 0);
	glScaled(2, 2, 0);
	hold_str.draw_block();
	glPopMatrix();

	glPushMatrix();
	glTranslated(holdmino.getX() * BLOCK_SIZE, holdmino.getY() * BLOCK_SIZE, 0);
	Create_Block(holdmino.getMino().mino, holdmino.getR(), holdmino.getG(), holdmino.getB());
	glPopMatrix();

	glPushMatrix();
	draw_str next_str("next");
	glTranslated((BOARD_WIDTH + 1) * BLOCK_SIZE, 4 * BLOCK_SIZE, 0);
	glScaled(2, 2, 0);
	next_str.draw_block();
	glPopMatrix();

	glPushMatrix();
	glTranslated(nextmino.getX() * BLOCK_SIZE, nextmino.getY() * BLOCK_SIZE, 0);
	Create_Block(nextmino.getMino().mino, nextmino.getR(), nextmino.getG(), nextmino.getB());
	glPopMatrix();
}

void Tetris::Tetris_Display() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(viewpoint.x + center.x, viewpoint.y + center.y, viewpoint.z + center.z,
		center.x, center.y, center.z,
		0.0, angle_of_top, 0.0);
	glPushMatrix();

	glPushMatrix();
	glTranslated(tetrimino.getX() * BLOCK_SIZE, tetrimino.getY() * BLOCK_SIZE, 0);
	Create_Block(tetrimino.getMino().mino, tetrimino.getR(), tetrimino.getG(), tetrimino.getB());
	glPopMatrix();

	speed = 1000 * pow(0.9, score.getLine() / 1);

	if(clock() - start > speed) {
		start = clock();
		if(tetrimino.translate(0, -1, false, &board)) {
			hold_check = true;
			Next_Mino();
		}
	}

	Draw_Information(score.getScore(), score.getLine());

	forecastmino.setMino(tetrimino.getMino());
	forecastmino_pos = tetrimino.getXY();
	forecastmino.setPoint(forecastmino_pos);
	while(!forecastmino.translate(0, -1, true, &board));

	glPushMatrix();
	glTranslated(forecastmino.getX() * BLOCK_SIZE, forecastmino.getY() * BLOCK_SIZE, 0);
	Create_Block(forecastmino.getMino().mino, 1.0, 0, 0, 0.4);
	glPopMatrix();

	Create_Board(board.getBoard().board);
	if(board.boardCheck(score)) {
		page = 0;
		mode = GAMEOVER;
	}
	glPopMatrix();

	glutSwapBuffers();
}


void Tetris::Tetris_Keyboard(unsigned char k, int x, int y) {
	switch(k) {
	case 'v':
		View_Reset();
		break;
	case 'r':
		Tetris_Init();
		mode = 0;
		break;
	case 'z':
		tetrimino.rotate(1, &board);
		break;
	case 'x':
		tetrimino.rotate(0, &board);
		break;
	case 'a':
		if(hold_check) Mino_Hold();
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

void Tetris::Tetris_Specialkeyboard(int k, int x, int y) {
	switch(k) {
	case GLUT_KEY_RIGHT:
		tetrimino.translate(1, 0, false, &board);
		break;
	case GLUT_KEY_LEFT:
		tetrimino.translate(-1, 0, false, &board);
		break;
	case GLUT_KEY_DOWN:
		if(tetrimino.translate(0, -1, false, &board)) {
			hold_check = true;
			Next_Mino();
		}
		break;
	case GLUT_KEY_UP:
		while(!tetrimino.translate(0, -1, false, &board));
		hold_check = true;
		Next_Mino();
		break;
	default:
		break;
	}
}
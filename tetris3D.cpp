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
				glTranslated(k * BLOCK_SIZE, j * BLOCK_SIZE, -i * BLOCK_SIZE);
				if(block[i][j][k]) {
					if(i == 0 || j == 0 || k == 0 || i == BOARD_DEPTH - 1 || k == BOARD_WIDTH - 1) {
						if((i == 0 && j == 0) || (i == 0 && k == 0) || (i == 0 && k == BOARD_WIDTH - 1) || (i == BOARD_DEPTH - 1 && j == 0) || (i == BOARD_DEPTH - 1 && k == 0) || (i == BOARD_DEPTH - 1 && k == BOARD_WIDTH - 1) || (j == 0 && k == 0) || (j == 0 && k == BOARD_WIDTH - 1)) {
							glColor4d(board3d.getBoard().red[i][j][k], board3d.getBoard().green[i][j][k], board3d.getBoard().blue[i][j][k], 0.4);
						} else {
							glColor4d(board3d.getBoard().red[i][j][k], board3d.getBoard().green[i][j][k], board3d.getBoard().blue[i][j][k], 0.01);
						}
					} else {
						glColor3d(board3d.getBoard().red[i][j][k], board3d.getBoard().green[i][j][k], board3d.getBoard().blue[i][j][k]);
					}
					glutSolidCube(BLOCK_SIZE);
				}
				glPopMatrix();
			}
		}
	}
}

void Tetris::Next_Mino3D() {
	tetrimino3d.setMino(nextmino3d.getMino());
	tetrimino3d.setColor(nextmino3d.getR(), nextmino3d.getG(),nextmino3d.getB());
	nextmino3d.create();
	tetrimino3d.setPoint(mino_pos3d);
}

void Tetris::Mino_Hold3D() {
	hold_check = false;
	TmpMino3D temp = holdmino3d.getMino();
	double color[3] = { holdmino3d.getR(), holdmino3d.getG(), holdmino3d.getB() };
	if(temp.mino[1][1] == false) {
		holdmino3d.setMino(tetrimino3d.getMino());
		holdmino3d.setColor(tetrimino3d.getR(), tetrimino3d.getG(), tetrimino3d.getB());
		Next_Mino();
	} else {
		holdmino3d.setMino(tetrimino3d.getMino());
		holdmino3d.setColor(tetrimino3d.getR(), tetrimino3d.getG(), tetrimino3d.getB());
		tetrimino3d.setMino(temp);
		tetrimino3d.setColor(color[0], color[1], color[2]);
		tetrimino3d.setPoint(mino_pos3d);
	}
}

void Tetris::Draw_Information3D(int score, int line) {
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
	glTranslated(holdmino3d.getX() * BLOCK_SIZE, holdmino3d.getY() * BLOCK_SIZE, holdmino3d.getZ() * BLOCK_SIZE);
	Create_Block3D(holdmino3d.getMino().mino, holdmino3d.getR(), holdmino3d.getG(), holdmino3d.getB());
	glPopMatrix();

	glPushMatrix();
	draw_str next_str("next");
	glTranslated((BOARD_WIDTH + 1) * BLOCK_SIZE, 4 * BLOCK_SIZE, 0);
	glScaled(2, 2, 0);
	next_str.draw_block();
	glPopMatrix();

	glPushMatrix();
	glTranslated(nextmino3d.getX() * BLOCK_SIZE, nextmino3d.getY() * BLOCK_SIZE, nextmino3d.getZ() * BLOCK_SIZE);
	Create_Block3D(nextmino3d.getMino().mino, nextmino3d.getR(), nextmino3d.getG(), nextmino3d.getB());
	glPopMatrix();
}

void Tetris::Tetris3D_Display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(viewpoint.x + center.x, viewpoint.y + center.y, viewpoint.z + center.z,
		center.x, center.y, center.z,
		0.0, angle_of_top, 0.0);
	glPushMatrix();

	glPushMatrix();
	glTranslated(tetrimino3d.getX() * BLOCK_SIZE, tetrimino3d.getY() * BLOCK_SIZE, tetrimino3d.getZ() * BLOCK_SIZE);
	Create_Block3D(tetrimino3d.getMino().mino, tetrimino3d.getR(), tetrimino3d.getG(), tetrimino3d.getB());
	glPopMatrix();

	forecastmino3d.setMino(tetrimino3d.getMino());
	forecastmino_pos3d = tetrimino3d.getXYZ();
	forecastmino3d.setPoint(forecastmino_pos3d);
	//while(!forecastmino3d.translate(0, -1, 0, true, &board3d));

	glPushMatrix();
	glTranslated(forecastmino3d.getX() * BLOCK_SIZE, forecastmino3d.getY() * BLOCK_SIZE, forecastmino3d.getZ() * BLOCK_SIZE);
	Create_Block3D(forecastmino3d.getMino().mino, 1.0, 0, 0, 0.4);
	glPopMatrix();

	glPopMatrix();

	speed = 1000 * pow(0.9, score.getLine() / 1);

	if(clock() - start > speed) {
		start = clock();
		if(tetrimino3d.translate(0, -1, 0, false, &board3d)) {
			hold_check = true;
			Next_Mino3D();
		}
	}

	Draw_Information3D(score.getScore(), score.getLine());
	Create_Board3D(board3d.getBoard().board);
	if(board3d.boardCheck(score)) {
		mode = GAMEOVER;
	}
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
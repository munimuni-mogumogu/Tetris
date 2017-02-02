/**
*	@file	tetris_run.cpp
*	@brief	�ʏ�e�g���X���[�h
*	@author	�O�� �z��
*	@date	2017/01/22
*/

#include "tetris.h"

/**
*	@brief		�ʏ�e�g���X���[�h�̃��C���֐�
*	@return		�Ȃ�
*/
void Tetris::Tetris_Main() {
	glutDisplayFunc(Tetris_Display);
	glutKeyboardFunc(Tetris_Keyboard);
	glutSpecialFunc(Tetris_Specialkeyboard);
}

/**
*	@brief		�����̂̕`��(���t��)
*	@param [in]	block[MINO_HEIGHT][MINO_WIDTH]	�e�g���~�m
*	@param [in]	Red		�ԐF(=0, 0 < Red < 1)
*	@param [in]	blue	�F(=0. 0 < Blue < 1)
*	@param [in]	Green	�ΐF(=0, 0 < Green < 1)
*	@param [in]	shadow	�����x(=1, 0 < shadow < 1)
*	@return		�Ȃ�
*/
void Tetris::DrawCube(int size, GLdouble Red, GLdouble Green, GLdouble Blue, GLdouble shadow) {
	glPushMatrix();
	glScaled(size, size, size);
	glColor4d(Red, Green, Blue, shadow);
	glBegin(GL_QUADS);
	for (int j = 0; j < 6; ++j) {
		glNormal3dv(draw_rect.normal[j]); //�@���x�N�g���̎w��
		for (int i = 0; i < 4; ++i) {
			glVertex3dv(draw_rect.vertex[draw_rect.face[j][i]]);
		}
	}
	glEnd();
	glColor4d(Red / 2, Green / 2, Blue / 2, shadow);
	glBegin(GL_LINE_LOOP);
	for(int i = 0; i < 4; i++)
		glVertex3d(draw_rect.vertex2[i][0], draw_rect.vertex2[i][1], draw_rect.vertex2[i][2]);
	glEnd();
	glBegin(GL_LINE_LOOP);
	for(int i = 4; i < 8; i++)
		glVertex3d(draw_rect.vertex2[i][0], draw_rect.vertex2[i][1], draw_rect.vertex2[i][2]);
	glEnd();
	for(int i = 0; i < 4; i++) {
		glBegin(GL_LINE_LOOP);
		glVertex3d(draw_rect.vertex2[i][0], draw_rect.vertex2[i][1], draw_rect.vertex2[i][2]);
		glVertex3d(draw_rect.vertex2[i + 4][0], draw_rect.vertex2[i + 4][1], draw_rect.vertex2[i + 4][2]);
		glEnd();
	}
	glPopMatrix();
}

/**
*	@brief		�e�g���~�m�̕`��֐�
*				�����x�𗘗p����ꍇ���̂��̂���`�悷�邱�Ƃɒ���
*	@param [in]	block[MINO_HEIGHT][MINO_WIDTH]	�e�g���~�m
*	@param [in]	Red		�ԐF(=0, 0 < Red < 1)
*	@param [in]	blue	�F(=0. 0 < Blue < 1)
*	@param [in]	Green	�ΐF(=0, 0 < Green < 1)
*	@param [in]	shadow	�����x(=1, 0 < shadow < 1)
*	@return		�Ȃ�
*/
void Tetris::Create_Block(bool block[MINO_HEIGHT][MINO_WIDTH], GLdouble Red = 0, GLdouble Green = 0, GLdouble Blue = 0, GLdouble shadow = 1) {
	glPushMatrix();
	//�����x���p���̓f�v�X�o�b�t�@�ւ̏������݂����Ȃ�
	if(shadow != 1) glDepthMask(GL_FALSE);
	for(int i = 0; i < MINO_HEIGHT; i++) {
		for(int j = 0; j < MINO_WIDTH; j++){
			glPushMatrix();
			glTranslated(j * BLOCK_SIZE, i * BLOCK_SIZE, 0.0);
			if(block[i][j]) DrawCube(BLOCK_SIZE, Red, Green, Blue, shadow);
			glPopMatrix();
		}
	}
	glDepthMask(GL_TRUE);
	glPopMatrix();
}

/**
*	@brief		�{�[�h�̕`��֐�
*				�����x�𗘗p���邽�ߕ`�揇�ɒ���
*	@param [in]	board[MINO_HEIGHT][MINO_WIDTH]	�{�[�h
*	@return		�Ȃ�
*/
void Tetris::Create_Board(bool block[BOARD_HEIGHT][BOARD_WIDTH]) {
	for(int i = 0; i < BOARD_HEIGHT; i++) {
		for(int j = 0; j < BOARD_WIDTH; j++){
			glPushMatrix();
			glTranslated(j * BLOCK_SIZE, i * BLOCK_SIZE, 0.0);
			if(block[i][j]) {
				if(i == 0 || j == 0 || j == BOARD_WIDTH - 1) {
					//�g�͔������ɕ`��
					glDepthMask(GL_FALSE);
					DrawCube(BLOCK_SIZE, board.getBoard().red[i][j], board.getBoard().green[i][j], board.getBoard().blue[i][j], 0.4);
				} else {
					glDepthMask(GL_TRUE);
					DrawCube(BLOCK_SIZE, board.getBoard().red[i][j], board.getBoard().green[i][j], board.getBoard().blue[i][j]);
				}
			}
			glPopMatrix();
		}
	}
	glDepthMask(GL_TRUE);
}

/**
*	@brief		���̃~�m�Z�b�g�֐�
*	@return		�Ȃ�
*/
void Tetris::Next_Mino() {
	tetrimino.setMino(nextmino.getMino());
	tetrimino.setColor(nextmino.getR(), nextmino.getG(),nextmino.getB());
	if(page == TETRIS) nextmino.create(2);
	else if(page == TETRISRAND) nextmino.create(0);
	tetrimino.setPoint(mino_pos);
}

/**
*	@brief		�z�[���h�~�m�Z�b�g�֐�
*	@return		�Ȃ�
*/
void Tetris::Mino_Hold() {
	hold_check = false;
	TmpMino temp = holdmino.getMino();
	double color[3] = { holdmino.getR(), holdmino.getG(), holdmino.getB() };
	//�z�[���h����Ă���~�m�����ɂ��邩�̔���
	if(temp.mino[1][1] == false) {
		//�z�[���h�~�m���Ȃ�
		holdmino.setMino(tetrimino.getMino());
		holdmino.setColor(tetrimino.getR(), tetrimino.getG(), tetrimino.getB());
		Next_Mino();
	} else {
		//�z�[���h�~�m������
		holdmino.setMino(tetrimino.getMino());
		holdmino.setColor(tetrimino.getR(), tetrimino.getG(), tetrimino.getB());
		tetrimino.setMino(temp);
		tetrimino.setColor(color[0], color[1], color[2]);
		tetrimino.setPoint(mino_pos);
	}
}

/**
*	@brief		�e�g���X���̏��̕`��
*	@param [in]	score	�_��
*	@param [in]	line	���C����
*	@return		�Ȃ�
*/
void Tetris::Draw_Information(int score, int line) {
	glPushMatrix();
	glTranslated(center.x, center.y, center.z);
	glRotated(azimuth/M_PI*180, 0, -1, 0);
	glRotated(-elevation/M_PI*180,info_pos.x,0,-info_pos.z);
	glTranslated(0, 0, view_distance - tmp_view_distance);

	//SCORE�̕����̕`��
	glPushMatrix();
	draw_str score_str("score");
	glTranslated(6 * BLOCK_SIZE, (BOARD_HEIGHT/2 - 2) * BLOCK_SIZE, 0);
	glScaled(2, 2, 0);
	score_str.draw_block();
	glPopMatrix();

	//�_���̕`��
	glPushMatrix();
	draw_str draw_score(score);
	glTranslated(6 * BLOCK_SIZE, (BOARD_HEIGHT/2 - 4) * BLOCK_SIZE, 0);
	glScaled(2, 2, 0);
	draw_score.draw_block();
	glPopMatrix();

	//LINE�̕����̕`��
	glPushMatrix();
	draw_str line_str("line");
	glTranslated(6 * BLOCK_SIZE, (BOARD_HEIGHT/2 - 6) * BLOCK_SIZE, 0);
	glScaled(2, 2, 0);
	line_str.draw_block();
	glPopMatrix();

	//������LINE���̕`��
	glPushMatrix();
	draw_str draw_line(line);
	glTranslated(6 * BLOCK_SIZE, (BOARD_HEIGHT/2 - 8) * BLOCK_SIZE, 0);
	glScaled(2, 2, 0);
	draw_line.draw_block();
	glPopMatrix();

	//HOLD�̕����̕`��
	glPushMatrix();
	draw_str hold_str("hold");
	glTranslated(6 * BLOCK_SIZE, (BOARD_HEIGHT/2 - 11) * BLOCK_SIZE, 0);
	glScaled(2, 2, 0);
	hold_str.draw_block();
	glPopMatrix();

	//�z�[���h�~�m�̕`��
	glPushMatrix();
	glTranslated(7 * BLOCK_SIZE, -4 * BLOCK_SIZE, 0);
	Create_Block(holdmino.getMino().mino, holdmino.getR(), holdmino.getG(), holdmino.getB());
	glPopMatrix();

	//NEXT�̕����̕`��
	glPushMatrix();
	draw_str next_str("next");
	glTranslated(6 * BLOCK_SIZE, -7 * BLOCK_SIZE, 0);
	glScaled(2, 2, 0);
	next_str.draw_block();
	glPopMatrix();

	//�l�N�X�g�~�m�̕`��
	glPushMatrix();
	glTranslated(7 * BLOCK_SIZE,-11 * BLOCK_SIZE, 0);
	Create_Block(nextmino.getMino().mino, nextmino.getR(), nextmino.getG(), nextmino.getB());
	glPopMatrix();
	glPopMatrix();
}

/**
*	@brief		�ʏ�e�g���X���[�h�̕`��̃��C���֐�
*	@return		�Ȃ�
*/
void Tetris::Tetris_Display() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(viewpoint.x + center.x, viewpoint.y + center.y, viewpoint.z + center.z,
		center.x, center.y, center.z,
		0.0, angle_of_top, 0.0);
	glPushMatrix();

	//�e�g���~�m�̕`��
	glPushMatrix();
	glTranslated(tetrimino.getX() * BLOCK_SIZE, tetrimino.getY() * BLOCK_SIZE, 0);
	Create_Block(tetrimino.getMino().mino, tetrimino.getR(), tetrimino.getG(), tetrimino.getB());
	glPopMatrix();

	//�������x�̎w��(�P���C���������Ƃ�0.9�{, ����1�b)
	speed = 1000 * pow(0.9, score.getLine() / 1);
	if(clock() - start > speed) {
		start = clock();
		//��������
		if(tetrimino.translate(0, -1, false, &board)) {
			//���Ƀ~�m���������Ƃ�
			hold_check = true;
			Next_Mino();
		}
	}

	//�e�g���~�m�̗����\���ʒu�̌v��
	forecastmino.setMino(tetrimino.getMino());
	forecastmino_pos = tetrimino.getXY();
	forecastmino.setPoint(forecastmino_pos);
	while(!forecastmino.translate(0, -1, true, &board));
	//�����\���ʒu�Ƀe�g���~�m�̕`��(�����x60%)
	glPushMatrix();
	glTranslated(forecastmino.getX() * BLOCK_SIZE, forecastmino.getY() * BLOCK_SIZE, 0);
	Create_Block(forecastmino.getMino().mino, 1.0, 0, 0, 0.4);
	glPopMatrix();

	//�{�[�h�̕`��
	Create_Board(board.getBoard().board);

	//�e�g���X���̏��̕`��
	Draw_Information(score.getScore(), score.getLine());

	//�Q�[���I�[�o�[�̔���
	if(board.boardCheck(score)) {
		mode = GAMEOVER;
	}
	glPopMatrix();

	glutSwapBuffers();
}

/**
*	@brief		�e�g���X���[�h�̃L�[����֐�
*	@param [in]	k	�L�[
*	@param [in]	x	�}�E�Xx���W
*	@param [in]	y	�}�E�Xy���W
*	@return		�Ȃ�
*/
void Tetris::Tetris_Keyboard(unsigned char k, int x, int y) {
	switch(k) {
	case 'v':	//���_�̃��Z�b�g
		View_Reset();
		break;
	case 'r':	//�^�C�g���֖߂�
		Tetris_Init();
		mode = TITLE;
		break;
	case 'z':	//��](��)
		tetrimino.rotate(1, &board);
		break;
	case 'x':	//��](�E)
		tetrimino.rotate(0, &board);
		break;
	case ' ':	//�z�[���h
		//2�x�A���Ńz�[���h���Ă��Ȃ����̔���
		if(hold_check) Mino_Hold();
		break;
	case 'l':	//���C�e�B���O��on/off�؂�ւ�
		light_check = !light_check;
		if(light_check) glEnable(GL_LIGHTING);
		else glDisable(GL_LIGHTING);
		break;
	default:
		break;
	}
}

/**
*	@brief		�e�g���X���[�h�̓���L�[����֐�
*	@param [in]	k	�L�[
*	@param [in]	x	�}�E�Xx���W
*	@param [in]	y	�}�E�Xy���W
*	@return		�Ȃ�
*/
void Tetris::Tetris_Specialkeyboard(int k, int x, int y) {
	switch(k) {
	case GLUT_KEY_RIGHT:	//�ړ�(�E)
		tetrimino.translate(1, 0, false, &board);
		break;
	case GLUT_KEY_LEFT:		//�ړ�(��)
		tetrimino.translate(-1, 0, false, &board);
		break;
	case GLUT_KEY_DOWN:		//�ړ�(��)
		//���n����
		if(tetrimino.translate(0, -1, false, &board)) {
			hold_check = true;
			Next_Mino();
		}
		break;
	case GLUT_KEY_UP:		//�ړ�(���n)
		//���n����܂ňړ�
		while(!tetrimino.translate(0, -1, false, &board));
		hold_check = true;
		Next_Mino();
		break;
	default:
		break;
	}
}
/**
*	@file	tetris3D.cpp
*	@brief	3D�e�g���X���[�h
*	@author	�O�� �z��
*	@date	2017/01/22
*/

#include "tetris.h"

/**
*	@brief		3D�e�g���X���[�h�̃��C���֐�
*	@return		�Ȃ�
*/
void Tetris::Tetris3D() {
	glutDisplayFunc(Tetris3D_Display);
	glutKeyboardFunc(Tetris3D_Keyboard);
	glutSpecialFunc(Tetris3D_Specialkeyboard);
}

/**
*	@brief		�e�g���~�m3D�̕`��֐�
*				�����x�𗘗p����ꍇ���̂��̂���`�悷�邱�Ƃɒ���
*	@param [in]	block[MINO_DEPTH][MINO_HEIGHT][MINO_WIDTH]	�e�g���~�m
*	@param [in]	Red		�ԐF(=0, 0 < Red < 1)
*	@param [in]	blue	�F(=0. 0 < Blue < 1)
*	@param [in]	Green	�ΐF(=0, 0 < Green < 1)
*	@param [in]	shadow	�����x(=1, 0 < shadow < 1)
*	@return		�Ȃ�
*/
void Tetris::Create_Block3D(bool block[MINO_DEPTH][MINO_HEIGHT][MINO_WIDTH], GLdouble Red = 0, GLdouble Green = 0, GLdouble Blue = 0, GLdouble shadow = 1) {
	glPushMatrix();
	//�����x���p���̓f�v�X�o�b�t�@�ւ̏������݂����Ȃ�
	if(shadow != 1) glDepthMask(GL_FALSE);
	for(int i = 0; i < MINO_DEPTH; i++) {
		for(int j = 0; j < MINO_HEIGHT; j++){
			for(int k = 0; k < MINO_WIDTH; k++) {
				glPushMatrix();
				glTranslated(k * BLOCK_SIZE, j * BLOCK_SIZE, -i * BLOCK_SIZE);
				if(block[i][j][k]) DrawCube(BLOCK_SIZE, Red, Green, Blue, shadow);
				glPopMatrix();
			}
		}
	}
	glDepthMask(GL_TRUE);
	glPopMatrix();
}

/**
*	@brief		�{�[�h�̕`��֐�
*				�����x�𗘗p���邽�ߕ`�揇�ɒ���
*	@param [in]	board[BOARD_DEPTH][MINO_HEIGHT][MINO_WIDTH]	�{�[�h
*	@return		�Ȃ�
*/
void Tetris::Create_Board3D(bool block[BOARD_DEPTH][BOARD_HEIGHT][BOARD_WIDTH]) {
	for(int i = 1; i < BOARD_DEPTH - 1; i++) {
		for(int j = 1; j < BOARD_HEIGHT - 1; j++){
			for(int k = 1; k < BOARD_WIDTH - 1; k++) {
				glPushMatrix();
				glTranslated(k * BLOCK_SIZE, j * BLOCK_SIZE, -i * BLOCK_SIZE);
				if(block[i][j][k]) {
					DrawCube(BLOCK_SIZE, board3d.getBoard().red[i][j][k], board3d.getBoard().green[i][j][k], board3d.getBoard().blue[i][j][k]);
				}
				glPopMatrix();
			}
		}
	}
	//�����\���ʒu�Ƀe�g���~�m�̕`��(�����x60%)
	glPushMatrix();
	glTranslated(forecastmino3d.getX() * BLOCK_SIZE, forecastmino3d.getY() * BLOCK_SIZE, -forecastmino3d.getZ() * BLOCK_SIZE);
	Create_Block3D(forecastmino3d.getMino().mino, 0, 0, 0, 0.4);
	glPopMatrix();
	//3D�Ȃ̂Ń{�[�h�͓��ߏ������s�����߃��C�e�B���O�̉e�����󂯂Ȃ�
	glDisable(GL_LIGHTING);
	for(int i = 0; i < BOARD_DEPTH; i++) {
		for(int j = 0; j < BOARD_HEIGHT; j++){
			for(int k = 0; k < BOARD_WIDTH; k++) {
				glPushMatrix();
				glTranslated(k * BLOCK_SIZE, j * BLOCK_SIZE, -i * BLOCK_SIZE);
				if(block[i][j][k]) {
					if(i == 0 || j == 0 || k == 0 || i == BOARD_DEPTH - 1 || k == BOARD_WIDTH - 1) {
						//���͔������ɕ`��,���͔����`��
						if((i == 0 && j == 0) || (i == 0 && k == 0) || (i == 0 && k == BOARD_WIDTH - 1) || (i == BOARD_DEPTH - 1 && j == 0) || (i == BOARD_DEPTH - 1 && k == 0) || (i == BOARD_DEPTH - 1 && k == BOARD_WIDTH - 1) || (j == 0 && k == 0) || (j == 0 && k == BOARD_WIDTH - 1)) {
							//���̎�
							glDepthMask(GL_FALSE);
							DrawCube(BLOCK_SIZE, board3d.getBoard().red[i][j][k], board3d.getBoard().green[i][j][k], board3d.getBoard().blue[i][j][k], 0.4);
						} else {
							//���̎�
							glDepthMask(GL_FALSE);
							DrawCube(BLOCK_SIZE, board3d.getBoard().red[i][j][k], board3d.getBoard().green[i][j][k], board3d.getBoard().blue[i][j][k], 0.01);
						}
					}
				}
				glPopMatrix();
			}
		}
	}
	if(light_check) glEnable(GL_LIGHTING);
	glDepthMask(GL_TRUE);
}

/**
*	@brief		���̃~�m�Z�b�g�֐�
*	@return		�Ȃ�
*/
void Tetris::Next_Mino3D() {
	tetrimino3d.setMino(nextmino3d.getMino());
	tetrimino3d.setColor(nextmino3d.getR(), nextmino3d.getG(),nextmino3d.getB());
	nextmino3d.create();
	tetrimino3d.setPoint(mino_pos3d);
}

/**
*	@brief		�z�[���h�~�m�Z�b�g�֐�
*	@return		�Ȃ�
*/
void Tetris::Mino_Hold3D() {
	hold_check = false;
	TmpMino3D temp = holdmino3d.getMino();
	double color[3] = { holdmino3d.getR(), holdmino3d.getG(), holdmino3d.getB() };
	//�z�[���h����Ă���~�m�����ɂ��邩�̔���
	if(temp.mino[1][1][1] == false) {
		//�z�[���h�~�m���Ȃ�
		holdmino3d.setMino(tetrimino3d.getMino());
		holdmino3d.setColor(tetrimino3d.getR(), tetrimino3d.getG(), tetrimino3d.getB());
		Next_Mino3D();
	} else {
		//�z�[���h�~�m������
		holdmino3d.setMino(tetrimino3d.getMino());
		holdmino3d.setColor(tetrimino3d.getR(), tetrimino3d.getG(), tetrimino3d.getB());
		tetrimino3d.setMino(temp);
		tetrimino3d.setColor(color[0], color[1], color[2]);
		tetrimino3d.setPoint(mino_pos3d);
	}
}

/**
*	@brief		�e�g���X���̏��̕`��
*	@param [in]	score	�_��
*	@param [in]	line	���C����
*	@return		�Ȃ�
*/
void Tetris::Draw_Information3D(int score, int plane) {
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

	//PLANE�̕����̕`��
	glPushMatrix();
	draw_str plane_str("plane");
	glTranslated(6 * BLOCK_SIZE, (BOARD_HEIGHT/2 - 6) * BLOCK_SIZE, 0);
	glScaled(2, 2, 0);
	plane_str.draw_block();
	glPopMatrix();

	//������PLANE���̕`��
	glPushMatrix();
	draw_str draw_plane(plane);
	glTranslated(6 * BLOCK_SIZE, (BOARD_HEIGHT/2 - 8) * BLOCK_SIZE, 0);
	glScaled(2, 2, 0);
	draw_plane.draw_block();
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
	Create_Block3D(holdmino3d.getMino().mino, holdmino3d.getR(), holdmino3d.getG(), holdmino3d.getB());
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
	Create_Block3D(nextmino3d.getMino().mino, nextmino3d.getR(), nextmino3d.getG(), nextmino3d.getB());
	glPopMatrix();
	glPopMatrix();
}

/**
*	@brief		�ʏ�e�g���X���[�h�̕`��̃��C���֐�
*	@return		�Ȃ�
*/
void Tetris::Tetris3D_Display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glEnable(GL_DEPTH_TEST);
	gluLookAt(viewpoint.x + center.x, viewpoint.y + center.y, viewpoint.z + center.z,
		center.x, center.y, center.z,
		0.0, angle_of_top, 0.0);
	glPushMatrix();

	//�e�g���~�m�̕`��
	glPushMatrix();
	glTranslated(tetrimino3d.getX() * BLOCK_SIZE, tetrimino3d.getY() * BLOCK_SIZE, -tetrimino3d.getZ() * BLOCK_SIZE);
	Create_Block3D(tetrimino3d.getMino().mino, tetrimino3d.getR(), tetrimino3d.getG(), tetrimino3d.getB());
	glPopMatrix();

	//�������x�̎w��(�P�v���[���������Ƃ�0.9�{, ����1�b)
	speed = 1000 * pow(0.9, score.getLine() / 1);
	if(clock() - start > speed) {
		start = clock();
		//��������
		if(tetrimino3d.translate(0, -1, 0, false, &board3d)) {
			//���Ƀ~�m���������Ƃ�
			hold_check = true;
			Next_Mino3D();
		}
	}

	//�e�g���X���̏��̕`��
	glDepthMask(GL_FALSE);
	Draw_Information3D(score.getScore(), score.getLine());
	glDepthMask(GL_TRUE);

	//�e�g���~�m�̗����\���ʒu�̌v��
	forecastmino3d.setMino(tetrimino3d.getMino());
	forecastmino_pos3d = tetrimino3d.getXYZ();
	forecastmino3d.setPoint(forecastmino_pos3d);
	while(!forecastmino3d.translate(0, -1, 0, true, &board3d));

	//�{�[�h�̕`��
	Create_Board3D(board3d.getBoard().board);
	//�Q�[���I�[�o�[�̔���
	if(board3d.boardCheck(score)) {
		page = TETRIS3D;
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
void Tetris::Tetris3D_Keyboard(unsigned char k, int x, int y) {
	switch(k) {
	case 'z':	//��](x��)
		tetrimino3d.rotate(1, 1, 0, 0, &board3d);
		break;
	case 'x':	//��](x�E)
		tetrimino3d.rotate(0, 1, 0, 0, &board3d);
		break;
	case 'a':	//��](y��)
		tetrimino3d.rotate(1, 0, 1, 0, &board3d);
		break;
	case 's':	//��](y�E)
		tetrimino3d.rotate(0, 0, 1, 0, &board3d);
		break;
	case 'q':	//��](z��)
		tetrimino3d.rotate(1, 0, 0, 1, &board3d);
		break;
	case 'w':	//��](z�E)
		tetrimino3d.rotate(0, 0, 0, 1, &board3d);
		break;
	case ' ':	//�z�[���h
		//2�x�A���Ńz�[���h���Ă��Ȃ����̔���
		if(hold_check) Mino_Hold3D();
		break;
	case 'v':	//���_�̃��Z�b�g
		View_Reset();
		break;
	case 'r':	//�^�C�g���֖߂�
		Tetris_Init();
		mode = TITLE;
		break;
	case 'l':	//���C�e�B���O��on/off�̐؂�ւ�
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
void Tetris::Tetris3D_Specialkeyboard(int k, int x, int y) {
	switch(k) {
	case GLUT_KEY_RIGHT:	//�ړ�(�E)
		tetrimino3d.translate(1, 0, 0, false, &board3d);
		break;
	case GLUT_KEY_LEFT:		//�ړ�(��)
		tetrimino3d.translate(-1, 0, 0, false, &board3d);
		break;
	case GLUT_KEY_DOWN:		//�ړ�(��)
		tetrimino3d.translate(0, 0, -1, false, &board3d);
		break;
	case GLUT_KEY_UP:		//�ړ�(��)
		tetrimino3d.translate(0, 0, 1, false, &board3d);
	case 112:		//�ړ�(��)Shift��
		//���n����
		if(tetrimino3d.translate(0, -1, 0, false, &board3d)) {
			hold_check = true;
			Next_Mino3D();
		}
		break;
	case 113:		//�ړ�(���n)Shift�E
		//���n����܂ňړ�
		while(!tetrimino3d.translate(0, -1, 0, false, &board3d));
		hold_check = true;
		Next_Mino3D();
		break;
	default:
		break;
	}
}
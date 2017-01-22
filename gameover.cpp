/**
*	@file	gameover.cpp
*	@brief	�Q�[���I�[�o�[���[�h
*	@author	�O�� �z��
*	@date	2017/01/22
*/

#include "tetris.h"

/**
*	@brief		�Q�[���I�[�o�[���[�h�̃��C���֐�
*	@return		�Ȃ�
*/
void Tetris::Gameover() {
	glutDisplayFunc(Gameover_Display);
	glutKeyboardFunc(Gameover_Keyboard);
	glutSpecialFunc(Gameover_Specialkeyboard);
}

/**
*	@brief		�Q�[���I�[�o�[���[�h�̕`��̃��C���֐�
*	@return		�Ȃ�
*/
void Tetris::Gameover_Display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(viewpoint.x + center.x, viewpoint.y + center.y, viewpoint.z + center.z,
		center.x, center.y, center.z,
		0.0, angle_of_top, 0.0);

	//�ǂ̃��[�h���𔻒肵,�{�[�h��`�悷��
	if(page == TETRIS) Create_Board(board.getBoard().board);
	else if(page == TETRIS3D) Create_Board3D(board3d.getBoard().board);
	Draw_Information(score.getScore(), score.getLine());

	//�Q�[���I�[�o�[�̕����`��
	draw_str gameover_str("gameover", 1, 0, 0);
	glPushMatrix();
	glTranslated((BOARD_WIDTH + MENU_SIZE) / 2 * BLOCK_SIZE, BOARD_HEIGHT / 2 * BLOCK_SIZE, 30);
	glScaled(4, 4, 4);
	gameover_str.draw_block(CENTER);
	glPopMatrix();

	//please push enter�̕`��
	draw_str end_str("please push enter ", 1, 0, 0);
	glPushMatrix();
	glTranslated((BOARD_WIDTH + MENU_SIZE) / 2 * BLOCK_SIZE, (BOARD_HEIGHT - 4) / 2 * BLOCK_SIZE, 30);
	glScaled(2, 2, 2);
	end_str.draw_block(CENTER);
	glPopMatrix();

	glutSwapBuffers();
}

/**
*	@brief		�Q�[���I�[�o�[�̃L�[����֐�
*	@param [in]	k	�L�[
*	@param [in] x	�}�E�Xx���W
*	@param [in] y	�}�E�Xy���W
*	@return		�Ȃ�
*/
void Tetris::Gameover_Keyboard(unsigned char k, int x, int y) {
	switch(k) {
	case GLUT_KEY_ENTER:	//Enter�L�[���͎�
		//�ǂ̃��[�h���̔���
		if(page == TETRIS) Set_Get_Ranking(RANKINGTXT);
		else if(page == TETRIS3D) Set_Get_Ranking(RANKING3DTXT);
		mode = RANKING;
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
*	@brief		�Q�[���I�[�o�[���[�h�̓���L�[����֐�
*	@param [in]	k	�L�[
*	@param [in] x	�}�E�Xx���W
*	@param [in] y	�}�E�Xy���W
*	@return		�Ȃ�
*/
void Tetris::Gameover_Specialkeyboard(int k, int x, int y) {
	switch(k) {
	case GLUT_KEY_UP:
	default:
		break;
	}
}
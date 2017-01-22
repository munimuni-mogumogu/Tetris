/**
*	@file	title.cpp
*	@brief	�^�C�g�����[�h
*	@author	�O�� �z��
*	@date	2017/01/22
*/

#include "tetris.h"

/**
*	@brief		�^�C�g�����[�h�̃��C���֐�
*	@return		�Ȃ�
*/
void Tetris::Title() {
	glutDisplayFunc(Title_Display);
	glutKeyboardFunc(Title_Keyboard);
	glutSpecialFunc(Title_Specialkeyboard);
}

/**
*	@brief		�^�C�g�����[�h�̕`��֐�
*	@return		�Ȃ�
*/
void Tetris::Title_Display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(viewpoint.x + center.x, viewpoint.y + center.y, viewpoint.z + center.z,
		center.x, center.y, center.z,
		0.0, angle_of_top, 0.0);

	//�I���R�}���h�̋�
	glPushMatrix();
	glTranslated((BOARD_WIDTH + MENU_SIZE - 18) / 2 * BLOCK_SIZE, (BOARD_HEIGHT / 2 - 3 - (title_pos * 2)) * BLOCK_SIZE - 6, 0);
	glColor3d(1, 0, 0);
	glutSolidSphere(5, 5, 10);
	glPopMatrix();
	glPushMatrix();

	//�^�C�g���̕`��
	draw_str Title_str("tetris");
	glTranslated((BOARD_WIDTH + MENU_SIZE) / 2 * BLOCK_SIZE,  BOARD_HEIGHT / 2 * BLOCK_SIZE, 0);
	glScaled(6, 6, 6);
	Title_str.draw_block(CENTER);
	glPopMatrix();

	//�ʏ�e�g���X�̕`��
	glPushMatrix();
	draw_str Start_str("start tetris");
	glTranslated((BOARD_WIDTH + MENU_SIZE) / 2 * BLOCK_SIZE, (BOARD_HEIGHT / 2 - 4) * BLOCK_SIZE, 0);
	glScaled(2, 2, 2);
	Start_str.draw_block(CENTER);
	glPopMatrix();
	
	//3D�e�g���X�̕`��
	glPushMatrix();
	draw_str start3d("start 3D tetris");
	glTranslated((BOARD_WIDTH + MENU_SIZE) / 2 * BLOCK_SIZE, (BOARD_HEIGHT / 2 - 6) * BLOCK_SIZE, 0);
	glScaled(2, 2, 2);
	start3d.draw_block(CENTER);
	glPopMatrix();

	//�����L���O�̕`��
	glPushMatrix();
	draw_str ranking_str("ranking");
	glTranslated((BOARD_WIDTH + MENU_SIZE) / 2 * BLOCK_SIZE, (BOARD_HEIGHT / 2 - 8) * BLOCK_SIZE, 0);
	glScaled(2, 2, 2);
	ranking_str.draw_block(CENTER);
	glPopMatrix();

	glutSwapBuffers();
}

/**
*	@brief		�^�C�g�����[�h�̃L�[����֐�
*	@param [in]	k	�L�[
*	@param [in] x	�}�E�Xx���W
*	@param [in] y	�}�E�Xy���W
*	@return		�Ȃ�
*/
void Tetris::Title_Keyboard(unsigned char k, int x, int y) {
	switch(k) {
	case GLUT_KEY_ENTER:	//Enter�L�[�̎�
		//�^�C�g���łǂꂪ�I������Ă��邩�̔���
		if(title_pos == 0) {
			//�ʏ�e�g���X�̎�
			Tetris_Init();
			mode = TETRIS;
		} else if (title_pos == 1) {
			//3D�e�g���X�̎�
			mode = TETRIS3D;
		} else if(title_pos == 2) {
			//�����L���O�̎�
			Set_Get_Ranking(RANKINGTXT);
			mode = RANKING;
		}
		break;
	case '\033':	//�e�g���X�S�̂̏I��(Esc�L�[)
		run = false;
		break;
	case 'v':	//���_�̃��Z�b�g
		View_Reset();
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
*	@brief		�^�C�g�����[�h�̓���L�[����֐�
*	@param [in]	k	�L�[
*	@param [in] x	�}�E�Xx���W
*	@param [in] y	�}�E�Xy���W
*	@return		�Ȃ�
*/
void Tetris::Title_Specialkeyboard(int k, int x, int y) {
	switch(k) {
	case GLUT_KEY_DOWN:	//�^�C�g���̑I�������ֈړ�������
		if(title_pos < 2)title_pos++;
		break;
	case GLUT_KEY_UP:	//�^�C�g���̑I������ֈړ�������
		if(title_pos > 0)title_pos--;
		break;
	default:
		break;
	}
}
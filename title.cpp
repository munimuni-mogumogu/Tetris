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
	glTranslated((BOARD_WIDTH + MENU_SIZE - 22) / 2 * BLOCK_SIZE, (BOARD_HEIGHT / 2 - 1 - (title_pos * 2)) * BLOCK_SIZE - 6, 0);
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

	//�ʏ�e�g���X�̕`��
	glPushMatrix();
	draw_str Startrand("start random tetris");
	glTranslated((BOARD_WIDTH + MENU_SIZE) / 2 * BLOCK_SIZE, (BOARD_HEIGHT / 2 - 6) * BLOCK_SIZE, 0);
	glScaled(2, 2, 2);
	Startrand.draw_block(CENTER);
	glPopMatrix();

	//3D�e�g���X�̕`��
	glPushMatrix();
	draw_str start3d("start 3D tetris");
	glTranslated((BOARD_WIDTH + MENU_SIZE) / 2 * BLOCK_SIZE, (BOARD_HEIGHT / 2 - 8) * BLOCK_SIZE, 0);
	glScaled(2, 2, 2);
	start3d.draw_block(CENTER);
	glPopMatrix();

	//�����L���O�̕`��
	glPushMatrix();
	draw_str ranking_str("ranking");
	glTranslated((BOARD_WIDTH + MENU_SIZE) / 2 * BLOCK_SIZE, (BOARD_HEIGHT / 2 - 10) * BLOCK_SIZE, 0);
	glScaled(2, 2, 2);
	ranking_str.draw_block(CENTER);
	glPopMatrix();

	glPushMatrix();
	draw_str finish("finish / esc");
	glTranslated((BOARD_WIDTH + MENU_SIZE - 3) * BLOCK_SIZE, -BLOCK_SIZE * 3, 0);
	finish.draw_block();
	glPopMatrix();

	glutSwapBuffers();
}

/**
*	@brief		�^�C�g�����[�h�̃L�[����֐�
*	@param [in]	k	�L�[
*	@param [in]	x	�}�E�Xx���W
*	@param [in]	y	�}�E�Xy���W
*	@return		�Ȃ�
*/
void Tetris::Title_Keyboard(unsigned char k, int x, int y) {
	switch(k) {
	case GLUT_KEY_ENTER:	//Enter�L�[�̎�
		//�^�C�g���łǂꂪ�I������Ă��邩�̔���
		if(title_pos == TETRIS) {
			//�ʏ�e�g���X�̎�
			page = TETRIS;
			mode = TETRIS;
			Tetris_Init();
		} else if (title_pos == TETRISRAND) {
			//�����_���e�g���X�̎�
			page = TETRISRAND;
			mode = TETRIS;
			Tetris_Init();
			page = TETRISRAND;
		} else if (title_pos == TETRIS3D) {
			//3D�e�g���X�̎�
			page = TETRIS3D;
			mode = TETRIS3D;
			Tetris_Init();
		} else if(title_pos == RANKING) {
			//�����L���O�̎�
			Set_Get_Ranking();
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
	case 'f':
		screen_check = !screen_check;
		if(screen_check) glutFullScreen();
		else glutReshapeWindow(WINDOW_WIDTH, WINDOW_HEIGHT);
		break;
	default:
		break;
	}
}

/**
*	@brief		�^�C�g�����[�h�̓���L�[����֐�
*	@param [in]	k	�L�[
*	@param [in]	x	�}�E�Xx���W
*	@param [in]	y	�}�E�Xy���W
*	@return		�Ȃ�
*/
void Tetris::Title_Specialkeyboard(int k, int x, int y) {
	switch(k) {
	case GLUT_KEY_DOWN:	//�^�C�g���̑I�������ֈړ�������
		if(title_pos < RANKING)title_pos++;
		break;
	case GLUT_KEY_UP:	//�^�C�g���̑I������ֈړ�������
		if(title_pos > TETRIS)title_pos--;
		break;
	default:
		break;
	}
}
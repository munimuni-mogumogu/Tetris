/**
*	@file	tetris_main.cpp
*	@brief	�e�g���X��main�֐�(�R�[���o�b�N�֐�)
*	@author	�O�� �z��
*	@date	2017/01/22
*/

#include "tetris.h"

/**
*	@brief		���s�p�֐�
*	@param [in]	argc
*	@param [in]	**argv
*	@return		�I������false��Ԃ�
*/
bool Tetris::Run(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("TETRIS");
	Gl_Init();
	Tetris_Init();
	Funcgroup();
	glutMainLoop();
	return run;
}

/**
*	@brief		OpenGL�̃R�[���o�b�N�֐��̂܂Ƃ�(�S���ʂ̕�)
*	@return		�Ȃ�
*/
void Tetris::Funcgroup() {
	glutReshapeFunc(Reshape);
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	glutMouseWheelFunc(Mousewheel);
	glutTimerFunc(16, Timer, 0);
}

/**
*	@brief		OpenGL��Reshape�֐�
*				���_�̕K�v�Ȑݒ�
*	@param [in]	w	Window�̉���
*	@param [in]	h	Window�̏c��
*	@return		�Ȃ�
*/
void Tetris::Reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(angle, aspect, 0.1, 1000.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

/**
*	@brief		�}�E�X�̃N���b�N�̏���
*	@param [in]	b	�{�^���N���b�N����
*	@param [in]	s	�{�^���̏��
*	@param [in]	x	x���W
*	@param [in]	y	y���W
*	@return		�Ȃ�
*/
void Tetris::Mouse(int b, int s, int x, int y) {
	switch(b) {
	case GLUT_LEFT_BUTTON:
		mousepoint.x = x;
		mousepoint.y = y;
		break;
	case GLUT_RIGHT_BUTTON:
		mousepoint.x = x;
		mousepoint.y = y;
		//�N���b�N����Ă���Ԃ�true,��������false
		view_check = !view_check;
		break;
	}
}

/**
*	@brief		�h���b�O����
*	@param [in]	x	x���W
*	@param [in]	y	y���W
*	@return		�Ȃ�
*/
void Tetris::Motion(int x, int y) {
	//�E�h���b�O�����h���b�O���̔���
	if(view_check) {
		//���h���b�O�̎�
		//��ʂ̒[����[�̃h���b�O��360���Ƃ���
		azimuth += (double)(x - mousepoint.x) / WINDOW_WIDTH * M_PI * 2;
		elevation += (double)(y - mousepoint.y) / WINDOW_HEIGHT * M_PI * 2;
		//�㉺�̉�]�̌��E(-90���`90��)
		if(elevation > M_PI / 2) elevation = M_PI / 2;
		else if(elevation < -M_PI / 2) elevation = -M_PI / 2;

		//���_�̐ݒ�Fview_distance�𔼌a�Ƃ��鋅��̈�_
		viewpoint.x = -view_distance * cos(elevation) * sin(azimuth);
		viewpoint.y = view_distance * sin(elevation);
		viewpoint.z = view_distance * cos(elevation) * cos(azimuth);
		//std::cout << viewpoint.x << ", " << viewpoint.y << ", " << viewpoint.z << std::endl;
		mousepoint.x = x;
		mousepoint.y = y;
	} else {
		//�E�h���b�O�̎�
		double dx = (x - mousepoint.x) / 2;
		double dy = (y - mousepoint.y) / 2;
		//���_�̐ݒ�F�����_�𕽍s�ړ����邱�ƂŎ��_�����s�ړ�
		center.x -= dx * cos(azimuth) - dy * sin(elevation) * sin(azimuth);
		center.y += dy * cos(elevation);
		center.z += -dx * sin(azimuth) - dy * sin(elevation) * cos(azimuth);
		//std::cout << center.x << ", " << center.y << ", " << center.z << std::endl;
		mousepoint.x = x;
		mousepoint.y = y;
	}
}

/**
*	@brief		�}�E�X�z�C�[���̏���
*	@param [in]	wheel_number	�}�E�X�z�C�[���̔ԍ�
*	@param [in]	direction	�ǂ���ɉ񂵂Ă��邩(��O:-1, ��:1)
*	@param [in]	x	x���W
*	@param [in]	y	y���W
*	@return		�Ȃ�
*/
void Tetris::Mousewheel(int wheel_number, int direction, int x, int y)
{
	view_distance -= direction * 2;
	viewpoint.x = -view_distance * cos(elevation) * sin(azimuth);
	viewpoint.y = view_distance * sin(elevation);
	viewpoint.z = view_distance * cos(elevation) * cos(azimuth);
	//std::cout << wheel_number << " " << direction << " " << x << " " << y << std::endl;
}

/**
*	@brief		�w�肵�����Ԃ��ƂɌĂяo�����֐�
*	@param [in]	value
*	@return		�Ȃ�
*/
void Tetris::Timer(int value) {
	//�Q�[���̃��[�h�̐؂�ւ�
	switch(mode) {
	case TITLE:	//�^�C�g�����
		Title();
		break;
	case TETRIS:	//�ʏ�̃e�g���X
		Tetris_Main();
		break;
	case TETRIS3D:	//3D�̃e�g���X
		Tetris3D();
		break;
	case GAMEOVER:	//�Q�[���I�[�o�[��
		Gameover();
		break;
	case RANKING:	//�����L���O�̕`��
		Ranking();
		break;
	}
	//�^�C�g����Esc�L�[�������ꂽ���Ƀ��C�����[�v�I��
	if(!run) glutLeaveMainLoop();
	glutPostRedisplay();
	glutTimerFunc(value, Timer, 16);
}
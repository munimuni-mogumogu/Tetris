#ifndef TETRIS_DEF_H
#define TETRIS_DEF_H

#define BOARD_WIDTH 12		//�{�[�h�̕�
#define BOARD_HEIGHT 22		//�{�[�h�̍���
#define BOARD_DEPTH 12		//�{�[�h�̉��s��

#define MINO_WIDTH 3		//�~�m�̕�
#define MINO_HEIGHT 3		//�~�m�̍���
#define MINO_DEPTH 3		//�~�m�̉��s��

#define BLOCK_SIZE 10		//1�̃u���b�N�̑傫��

#define MENU_SIZE 8			//���j���[�̑傫��

#define WINDOW_WIDTH 1600	//�E�B���h�E�̕�
#define WINDOW_HEIGHT 800	//�E�B���h�E�̍���

#define GLUT_KEY_ENTER 0x000d	//�G���^�[�L�[

//���[�h
#define TITLE 0
#define TETRIS 1
#define TETRIS3D 2
#define GAMEOVER 3
#define RANKING 4

//�����L���O�̖��O�̕���������(5����)
#define RANKNAME 6

//�����L���O�̓ǂݍ���/�ۑ���
#define RANKINGTXT "ranking.txt"
#define RANKING3DTXT "ranking3d.txt"

/* �e���v���[�g�p�^�[���� */
#define TEMPLATE_PATTERN	7

#endif
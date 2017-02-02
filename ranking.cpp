/**
*	@file	ranking.cpp
*	@brief	�����L���O���[�h
*	@author	�O�� �z��
*	@date	2017/01/22
*/

#include "tetris.h"
#include <fstream>
#include <iostream>

/**
*	@brief		�����L���O���[�h�̃��C���֐�
*	@return		�Ȃ�
*/
void Tetris::Ranking() {
	glutDisplayFunc(Ranking_Display);
	glutKeyboardFunc(Ranking_Keyboard);
	glutSpecialFunc(Ranking_Specialkeyboard);
}

/**
*	@brief		char�z��̒�������
*	@param [in, out]	name1[]	����ւ��镨
*	@param [in, out]	name2[]	����ւ��镨
*	@param [in]			size	�z��T�C�Y
*	@return		�Ȃ�
*/
void Tetris::Change_Name(char name1[], char name2[], int size) {
	char temp[RANKNAME];
	for(int j = 0; j < size; j++) {
		temp[j] = name1[j];
	}
	for(int j = 0; j < size; j++) {
		name1[j] = name2[j];
	}
	for(int j = 0; j < size; j++) {
		name2[j] = temp[j];
	}
}



/**
*	@brief		�����L���O���t�@�C������Ăяo��,���ʂ�Score��Line��g�ݍ���
*	@param [in]	file_name[]	�t�@�C���̖��O
*	@return		�Ȃ�
*/
void Tetris::Set_Get_Ranking() {
	//�����L���O���ʂ̏�����
	rank_pos = -1;
	//�t�@�C���I�[�v��
	std::ifstream fin(SAVEDATA);
	if(fin.fail()) {
		std::cerr << "Error : Cannot open file" << std::endl;
	}

	int index = 1;
	do {
		while(true) {
			char check;
			fin.get(check);
			if(check == '/') break;
		}
	}while (!(index++ == page));

	for(int i = 0; i < 10; i++) {
		fin >> ranking[i].x >> ranking[i].y;
		char c;
		fin.get(c);
		for(int j = 0; j < RANKNAME; j++) fin.get(rank_name[i][j]);
	}

	//���O�̖�����\0������
	for(int i = 0; i < 10; i++) rank_name[i][RANKNAME - 1] = '\0';

	//����̏��ʂ�g�ݍ���
	Point2 temp1 = {score.getScore(), score.getLine()};
	Point2 temp2;
	char tempname1[RANKNAME] = {' ', ' ', ' ', ' ', ' ', '\0'};
	for(int i = 0; i < 10; i++) {
		//�����L���O�ɓ����Ă��邩�̔���
		if(ranking[i].x < temp1.x) {
			//�����Ă��鎞
			if(rank_pos == -1) {
				rank_pos = i;
			}
			temp2.x = ranking[i].x; temp2.y = ranking[i].y;
			ranking[i].x = temp1.x; ranking[i].y = temp1.y;
			temp1.x = temp2.x; temp1.y = temp2.y;
			Change_Name(rank_name[i], tempname1, RANKNAME);
		}else if(ranking[i].x == temp1.x) {
			//������Line�����������̔���
			if(ranking[i].y < temp1.y) {
				//Line����������
				if(rank_pos == -1) {
					rank_pos = i;
				}
				temp2.x = ranking[i].x; temp2.y = ranking[i].y;
				ranking[i].x = temp1.x; ranking[i].y = temp1.y;
				temp1.x = temp2.x; temp1.y = temp2.y;
				Change_Name(rank_name[i], tempname1, RANKNAME);
			}
		}
	}
	//Score�̏�����
	score.clear();
	fin.close();
}

/**
*	@brief		�����L���O���t�@�C���ɕۑ�����
*	@param [in]	file_name[]	�t�@�C���̖��O
*	@return		�Ȃ�
*/
void Tetris::Save_Ranking_Name() {
	//�t�@�C���I�[�v��
	std::ifstream fin(SAVEDATA);
	if(fin.fail()) {
		std::cerr << "Error : Cannot open file" << std::endl;
	}
	std::ofstream fout("temp");
	if(fout.fail()) {
		std::cerr << "Error : Cannot open file" << std::endl;
	}

	char c;
	while(!fin.eof()) {
		fin.get(c);
		fout << c;
	}
	fin.close();
	fout.close();

	//�t�@�C���I�[�v��
	fin.open("temp");
	if(fin.fail()) {
		std::cerr << "Error : Cannot open file" << std::endl;
	}
	fout.open(SAVEDATA);
	if(fout.fail()) {
		std::cerr << "Error : Cannot open file" << std::endl;
	}

	fin.get(c);
	fout << "/";
	for(int index = TETRIS; index <= TETRIS3D; index++) {
		if(page == index) {
			fout << std::endl;
			//Score,Line,���O���t�@�C���ɕۑ�
			for(int i = 0; i < 10; i++) {
				fout << ranking[i].x << " " << ranking[i].y << " ";
				for(int j = 0; j < RANKNAME; j++) {
					fout << rank_name[i][j];
				}
				fout << std::endl;
			}
			char c;
			fin.get(c);
			while(true) {
				fin.get(c);
				if(c == '/') break;
			}
			fout << '/';
		} else {
			while(true) {
				char c;
				fin.get(c);
				fout << c;
				if(c == '/') break;
			}
		}
	}

	fin.close();
	fout.close();

	remove("temp");

	//�����L���O�̏��ʂ�������
	rank_pos = -1;
}

/**
*	@brief		�����L���O���[�h�̕`��̃��C���֐�
*	@return		�Ȃ�
*/
void Tetris::Ranking_Display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(viewpoint.x + center.x, viewpoint.y + center.y, viewpoint.z + center.z,
		center.x, center.y, center.z,
		0.0, angle_of_top, 0.0);

	//�^�C�g���̕`��
	draw_str title;
	//�ǂ̃����L���O���̔���
	if(page == TETRIS) {
		title.set_str("TETRIS");
	} else if(page == TETRISRAND) {
		title.set_str("RANDOM TETRIS");
	} else if(page == TETRIS3D) {
		title.set_str("3D TETRIS");
	}
	glPushMatrix();
	glTranslated((BOARD_WIDTH + MENU_SIZE) * BLOCK_SIZE / 2, (BOARD_HEIGHT + 1) * BLOCK_SIZE, 0);
	glScaled(3, 3, 3);
	title.draw_block(CENTER);
	glScaled(1, 1, 1);

	//�O�p�`�̕`��(�ǂ̃y�[�W�����邩)
	glColor3d(0.0, 0.0, 0.0);
	//�ǂ̃����L���O���̔���
	if(page == TETRIS) {
		//�E�O�p�̕`��
		glTranslated(BLOCK_SIZE * 4, 0, 0);
		glBegin(GL_TRIANGLES);
		glVertex3d(0.0, 0.0, 0.0);
		glVertex3d(0.0, BLOCK_SIZE / 2, 0.0);
		glVertex3d(BLOCK_SIZE / 2, BLOCK_SIZE / 4, 0.0);
		glEnd();
	} else if(page == TETRISRAND) {
		//�E�O�p�̕`��
		glPushMatrix();
		glTranslated(BLOCK_SIZE * 8, 0, 0);
		glBegin(GL_TRIANGLES);
		glVertex3d(0.0, 0.0, 0.0);
		glVertex3d(0.0, BLOCK_SIZE / 2, 0.0);
		glVertex3d(BLOCK_SIZE / 2, BLOCK_SIZE / 4, 0.0);
		glEnd();
		glPopMatrix();
		//���O�p�̕`��
		glPushMatrix();
		glTranslated(-BLOCK_SIZE, 0, 0);
		glBegin(GL_TRIANGLES);
		glVertex3d(BLOCK_SIZE / 2, 0.0, 0.0);
		glVertex3d(BLOCK_SIZE / 2, BLOCK_SIZE / 2, 0.0);
		glVertex3d(0.0 , BLOCK_SIZE / 4, 0.0);
		glEnd();
		glPopMatrix();
	} else if(page == TETRIS3D) {
		//���O�p�̕`��
		glTranslated(-BLOCK_SIZE, 0, 0);
		glBegin(GL_TRIANGLES);
		glVertex3d(BLOCK_SIZE / 2, 0.0, 0.0);
		glVertex3d(BLOCK_SIZE / 2, BLOCK_SIZE / 2, 0.0);
		glVertex3d(0.0 , BLOCK_SIZE / 4, 0.0);
		glEnd();
	}
	glPopMatrix();

	//rank, score,line(plane)�̕`��
	draw_str rank("rank");
	draw_str score("score");
	draw_str line;
	//�ǂ̃����L���O���̔���
	if(page == TETRIS || page == TETRISRAND) {
		line.set_str("line");
	} else if(page == TETRIS3D) {
		line.set_str("plane");
	}
	draw_str name("name");
	glPushMatrix();
	glTranslated((BOARD_WIDTH - 14) * BLOCK_SIZE, (BOARD_HEIGHT - 2) * BLOCK_SIZE, 0);
	glScaled(1.5, 1.5, 1.5);
	rank.draw_block();
	glTranslated(4 * BLOCK_SIZE , 0, 0);
	score.draw_block();
	glTranslated(6 * BLOCK_SIZE , 0, 0);
	line.draw_block();
	glTranslated(4 * BLOCK_SIZE, 0, 0);
	name.draw_block();
	glPopMatrix();

	//�����L���O�̖��O�̕`��
	draw_str ranking_str[10][4];
	for(int i = 0; i < 10; i++) {
		Point3 color = {0, 0, 0};
		if(rank_pos == i) color.x = 1;
		glPushMatrix();
		glTranslated((BOARD_WIDTH - 14) * BLOCK_SIZE, (BOARD_HEIGHT - i * 2 - 4) * BLOCK_SIZE, 0);
		glScaled(1.5, 1.5, 1.5);
		ranking_str[i][0].set_str(i + 1, color.x, color.y, color.z);
		ranking_str[i][0].draw_block();

		glTranslated(4 * BLOCK_SIZE, 0, 0);
		ranking_str[i][1].set_str((int)ranking[i].x, color.x, color.y, color.z);
		ranking_str[i][1].draw_block();

		glTranslated(6 * BLOCK_SIZE, 0, 0);
		ranking_str[i][2].set_str((int)ranking[i].y, color.x, color.y, color.z);
		ranking_str[i][2].draw_block();

		glTranslated(4 * BLOCK_SIZE, 0, 0);
		//�����L���O�ɓ����Ă���Ƃ�
		if(rank_pos == i) {
			//�ǂ��ɓ��͂��Ă��邩��"_"�̕`��
			glPushMatrix();
			glTranslated(name_pos * (STR_BLOCK_SIZE + 1), -STR_BLOCK_SIZE, 0);
			glBegin(GL_QUADS);
			glVertex2d(0, 0);
			glVertex2d(0, 2);
			glVertex2d(STR_BLOCK_SIZE, 2);
			glVertex2d(STR_BLOCK_SIZE, 0);
			glEnd();
			glPopMatrix();
		}
		char temp[RANKNAME];
		for(int j = 0; j < RANKNAME; j++) temp[j] = rank_name[i][j];
		ranking_str[i][3].set_str(temp, color.x, color.y, color.z);
		ranking_str[i][3].draw_block();
		glPopMatrix();
	}

	//please push enter key�̕`��
	glPushMatrix();
	glTranslated((BOARD_WIDTH + MENU_SIZE - 2) / 2 * BLOCK_SIZE, -3 * BLOCK_SIZE, 0);
	draw_str please("please push enter key", 1, 0, 0);
	glScaled(1.5, 1.5, 1.5);
	please.draw_block(CENTER);
	glPopMatrix();

	//�_�C�A���O�̔���
	if(dialog_check == true) {
		//�_�C�A���O�̕`��
		glPushMatrix();
		//�w�i�ɔ��̎l�p�`��`��
		glTranslated((BOARD_WIDTH + MENU_SIZE - 2) / 2 * BLOCK_SIZE, (BOARD_HEIGHT + 2) * BLOCK_SIZE / 2, BLOCK_SIZE);
		glBegin(GL_QUADS);
		glColor3d(1, 1, 1);
		glVertex3d(-BLOCK_SIZE * 10, -BLOCK_SIZE * 4, 0);
		glVertex3d(-BLOCK_SIZE * 10, BLOCK_SIZE * 2, 0);
		glVertex3d(BLOCK_SIZE * 10, BLOCK_SIZE * 2, 0);
		glVertex3d(BLOCK_SIZE * 10, -BLOCK_SIZE * 4, 0);
		glEnd();

		//decide,yes,/,no�̕`��
		Point3 color = { 0.0, 0.5, 0.5 };
		draw_str decide("decide", color.x, color.y, color.z);
		draw_str slash("/", color.x, color.y, color.z);
		if(dialog_pos == 0) color.x = 1;
		draw_str yes("yes", color.x, color.y, color.z);
		if(dialog_pos == 1) color.x = 1;
		else color.x = 0;
		draw_str no("no", color.x, color.y, color.z);
		glScaled(3.0, 3.0, 3.0);
		decide.draw_block(CENTER);
		glTranslated(0, -BLOCK_SIZE, 0);
		yes.draw_block(CENTER);
		glTranslated(BLOCK_SIZE * 3, 0, 0);
		slash.draw_block(CENTER);
		glTranslated(BLOCK_SIZE * 2, 0, 0);
		no.draw_block(CENTER);
		glPopMatrix();
	}

	glutSwapBuffers();
}

/**
*	@brief		�����L���O���[�h�̃L�[����֐�
*	@param [in]	k	�L�[
*	@param [in]	x	�}�E�Xx���W
*	@param [in]	y	�}�E�Xy���W
*	@return		�Ȃ�
*/
void Tetris::Ranking_Keyboard(unsigned char k, int x, int y) {
	switch(k) {
	case GLUT_KEY_ENTER:	//Enter�L�[
		//�ǂ̌���Ƃ̔���
		if(rank_pos == -1) {
			//�����L���O�O�̎�
			Tetris_Init();
			mode = TITLE;
		} else if(rank_pos != -1 && dialog_check == true && dialog_pos == 0) {
			//�_�C�A���O���o�Ă���Ƃ���yes���������Ƃ�
			dialog_check = false;
			//�ǂ̃����L���O���̔���
			Save_Ranking_Name();
		} else if(rank_pos != -1 && dialog_check == true && dialog_pos == 1) {
			//�_�C�A���O���o�Ă��鎞��no���������Ƃ�
			dialog_pos = 0;
			dialog_check = false;
		} else if(rank_pos != -1 && dialog_check == false) dialog_check = true;	//���O�����߂�Enter���������Ƃ�
		break;
	case 'v':	//���_�̃��Z�b�g
		View_Reset();
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
*	@brief		�����L���O���[�h�̓���L�[����֐�
*	@param [in]	k	�L�[
*	@param [in]	x	�}�E�Xx���W
*	@param [in]	y	�}�E�Xy���W
*	@return		�Ȃ�
*/
void Tetris::Ranking_Specialkeyboard(int k, int x, int y) {
	switch(k) {
	case GLUT_KEY_RIGHT:	//�E���L�[���������Ƃ�
		if(dialog_check == true && dialog_pos < 1) dialog_pos++;	//�_�C�A���O���o�Ă���Ƃ�
		else if(dialog_check == false && name_pos < RANKNAME - 2 && rank_pos != -1) name_pos++;	//���O�����߂Ă���Ƃ�
		else if(page == TETRIS && rank_pos == -1){
			//�����L���O�O�̎��ɒʏ�e�g���X���[�h�̃����L���O�����Ă���Ƃ�
			page = TETRISRAND;
			Set_Get_Ranking();
		} else if(page == TETRISRAND && rank_pos == -1) {
			//�����L���O�O�̎������_���e�g���X���[�h�̃����L���O�����Ă���Ƃ�
			page = TETRIS3D;
			Set_Get_Ranking();
		}
		break;
	case GLUT_KEY_LEFT:	//�����L�[���������Ƃ�
		if(dialog_check == true && dialog_pos > 0) dialog_pos--;		//�_�C�A���O���o�Ă���Ƃ�
		else if(dialog_check == false && name_pos > 0 && rank_pos != -1) name_pos--;	//���O�����߂Ă���Ƃ�
		else if(page == TETRIS3D && rank_pos == -1){
			//�����L���O�O�̎���3D�e�g���X���[�h�̃����L���O�����Ă���Ƃ�
			page = TETRISRAND;
			Set_Get_Ranking();
		} else if(page == TETRISRAND && rank_pos == -1) {
			//�����L���O�O�̎��Ƀ����_���e�g���X���[�h�̃����L���O�����Ă���Ƃ�
			page = TETRIS;
			Set_Get_Ranking();
		}
		break;
	case GLUT_KEY_UP:	//����L�[���������Ƃ�
		if(rank_pos != -1 && dialog_check == false) {
			if(rank_name[rank_pos][name_pos] == ' ') rank_name[rank_pos][name_pos] = 'A';	//���O���͎�" "����"A"�ɐ؂�ւ��鏈��
			else if(rank_name[rank_pos][name_pos] == 'Z') rank_name[rank_pos][name_pos] = ' ';	//���O���͎�"Z"����" "�ɐ؂�ւ��鏈��
			else rank_name[rank_pos][name_pos]++;
		}
		break;
	case GLUT_KEY_DOWN:	//�����L�[���������Ƃ�
		if(rank_pos != -1 && dialog_check == false) {
			if(rank_name[rank_pos][name_pos] == ' ') rank_name[rank_pos][name_pos] = 'Z';	//���O���͎�" "����"Z"�ɐ؂�ւ��鏈��
			else if(rank_name[rank_pos][name_pos] == 'A') rank_name[rank_pos][name_pos] = ' ';	//���O���͎�"A"����" "�ɐ؂�ւ��鏈��
			else rank_name[rank_pos][name_pos]--;
		}
		break;
	default:
		break;
	}
}
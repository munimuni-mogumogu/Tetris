#include "tetris.h"
#include <fstream>
#include <iostream>
#include <string>

void Tetris::Ranking() {
	glutDisplayFunc(Ranking_Display);
	glutKeyboardFunc(Ranking_Keyboard);
	glutSpecialFunc(Ranking_Specialkeyboard);
}

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

void Tetris::Set_Get_Ranking(char text_name[]) {
	rank_pos = -1;
	std::ifstream fin(text_name);
	if(fin.fail()) {
		std::cerr << "Error : Cannot open file" << std::endl;
	}

	std::string str;
	int i = 0;
	while (std::getline(fin, str)) {
		std::string s = "";
		std::string l = "";
		std::string n = "";
		int tmp = str.find(' ');
		for (int j = 0; j < tmp; j++)
			s += str[j];
		str = str.substr(tmp + 1);
		tmp = str.find(' ');
		for (int j = 0; j < tmp; j++)
			l += str[j];
		str = str.substr(tmp + 1);
		ranking[i].x = stoi(s);
		ranking[i].y = stoi(l);
		while (str.size() != RANKNAME) str += " ";
		for (int j = 0; j < RANKNAME; j++)
			rank_name[i][j] = str[j];
		i++;
	}

	for(int i = 0; i < 10; i++) {
		rank_name[i][RANKNAME - 1] = '\0';
	}

	Point2 temp1 = {score.getScore(), score.getLine()};
	Point2 temp2;
	char tempname1[RANKNAME] = {' ', ' ', ' ', ' ', ' ', '\0'};
	for(int i = 0; i < 10; i++) {
		if(ranking[i].x < temp1.x) {
			if(rank_pos == -1) {
				rank_pos = i;
			}
			temp2.x = ranking[i].x; temp2.y = ranking[i].y;
			ranking[i].x = temp1.x; ranking[i].y = temp1.y;
			temp1.x = temp2.x; temp1.y = temp2.y;
			Change_Name(rank_name[i], tempname1, RANKNAME);
		}else if(ranking[i].x == temp1.x) {
			if(ranking[i].y < temp1.y) {
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
	score.clear();
	fin.close();
}

void Tetris::Save_Ranking_Name(char text_name[]) {

	std::ofstream fout(text_name);
	if(fout.fail()) {
		std::cerr << "Error : Cannot open file" << std::endl;
	}

	for(int i = 0; i < 10; i++) {
		fout << ranking[i].x << " " << ranking[i].y << " ";
		for(int j = 0; j < RANKNAME; j++) {
			fout << rank_name[i][j];
		}
		fout << std::endl;
	}

	fout.close();

	rank_pos = -1;
}

void Tetris::Ranking_Display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(viewpoint.x + center.x, viewpoint.y + center.y, viewpoint.z + center.z,
		center.x, center.y, center.z,
		0.0, angle_of_top, 0.0);

	draw_str title;
	if(page == 0) {
		title.set_str("TETRIS");
	} else if(page == 1) {
		title.set_str("3D TETRIS");
	}
	glPushMatrix();
	glTranslated((BOARD_WIDTH + MENU_SIZE) * BLOCK_SIZE / 2, (BOARD_HEIGHT + 2) * BLOCK_SIZE, 0);
	glScaled(4, 4, 4);
	title.draw_block(CENTER);
	glScaled(1, 1, 1);
	glColor3d(0.0, 0.0, 0.0);
	if(page == 0) {
		glTranslated(BLOCK_SIZE * 4, 0, 0);
		glBegin(GL_TRIANGLES);
		glVertex3d(0.0, 0.0, 0.0);
		glVertex3d(0.0, BLOCK_SIZE / 2, 0.0);
		glVertex3d(BLOCK_SIZE / 2, BLOCK_SIZE / 4, 0.0);
		glEnd();
	}else if(page == 1) {
		glTranslated(-BLOCK_SIZE, 0, 0);
		glBegin(GL_TRIANGLES);
		glVertex3d(BLOCK_SIZE / 2, 0.0, 0.0);
		glVertex3d(BLOCK_SIZE / 2, BLOCK_SIZE / 2, 0.0);
		glVertex3d(0.0 , BLOCK_SIZE / 4, 0.0);
		glEnd();
	}
	glPopMatrix();
	draw_str rank("rank");
	draw_str score("score");
	draw_str line;
	if(page == 0) {
		line.set_str("line");
	} else if(page == 1) {
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
		if(rank_pos == i) {
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

	glPushMatrix();
	glTranslated((BOARD_WIDTH + MENU_SIZE - 2) / 2 * BLOCK_SIZE, -3 * BLOCK_SIZE, 0);
	draw_str please("please push enter key", 1, 0, 0);
	glScaled(2.0, 2.0, 2.0);
	please.draw_block(CENTER);
	glPopMatrix();

	if(dialog_check == true) {
		glPushMatrix();
		glTranslated((BOARD_WIDTH + MENU_SIZE - 2) / 2 * BLOCK_SIZE, (BOARD_HEIGHT + 2) * BLOCK_SIZE / 2, BLOCK_SIZE);
		glBegin(GL_QUADS);
		glColor3d(1, 1, 1);
		glVertex3d(-BLOCK_SIZE * 10, -BLOCK_SIZE * 4, 0);
		glVertex3d(-BLOCK_SIZE * 10, BLOCK_SIZE * 2, 0);
		glVertex3d(BLOCK_SIZE * 10, BLOCK_SIZE * 2, 0);
		glVertex3d(BLOCK_SIZE * 10, -BLOCK_SIZE * 4, 0);
		glEnd();
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

void Tetris::Ranking_Keyboard(unsigned char k, int x, int y) {
	switch(k) {
	case GLUT_KEY_ENTER:
		if(rank_pos == -1) {
			Tetris_Init();
			mode = TITLE;
		} else if(rank_pos != -1 && dialog_check == true && dialog_pos == 0) {
			dialog_check = false;
			if(page == 0) Save_Ranking_Name(RANKINGTXT);
			if(page == 1) Save_Ranking_Name(RANKING3DTXT);
		} else if(rank_pos != -1 && dialog_check == true && dialog_pos == 1) {
			dialog_pos = 0;
			dialog_check = false;
		} else if(rank_pos != -1 && dialog_check == false)
			dialog_check = true;
		break;
	case 'v':
		View_Reset();
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


void Tetris::Ranking_Specialkeyboard(int k, int x, int y) {
	switch(k) {
	case GLUT_KEY_RIGHT:
		if(dialog_check == true && dialog_pos < 1) dialog_pos++;
		else if(dialog_check == false && name_pos < RANKNAME - 2 && rank_pos != -1) name_pos++;
		else if(page == 0 && rank_pos == -1){
			Set_Get_Ranking(RANKING3DTXT);
			page = 1;
		}
		break;
	case GLUT_KEY_LEFT:
		if(dialog_check == true && dialog_pos > 0) dialog_pos--;
		else if(dialog_check == false && name_pos > 0 && rank_pos != -1) name_pos--;
		else if(page == 1 && rank_pos == -1){
			Set_Get_Ranking(RANKINGTXT);
			page = 0;
		}
		break;
	case GLUT_KEY_UP:
		if(rank_pos != -1 && dialog_check == false) {
			if(rank_name[rank_pos][name_pos] == ' ') rank_name[rank_pos][name_pos] = 'A';
			else if(rank_name[rank_pos][name_pos] == 'Z') rank_name[rank_pos][name_pos] = ' ';
			else rank_name[rank_pos][name_pos]++;
		}
		break;
	case GLUT_KEY_DOWN:
		if(rank_pos != -1 && dialog_check == false) {
			if(rank_name[rank_pos][name_pos] == ' ') rank_name[rank_pos][name_pos] = 'Z';
			else if(rank_name[rank_pos][name_pos] == 'A') rank_name[rank_pos][name_pos] = ' ';
			else rank_name[rank_pos][name_pos]--;
		}
		break;
	default:
		break;
	}
}
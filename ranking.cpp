#include "tetris.h"
#include <fstream>
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

void Tetris::Set_Get_Ranking() {
	rank_pos = -1;
	std::ifstream fin("ranking.txt");
	if(fin.fail()) {
		std::cerr << "Error : Cannot open file" << std::endl;
	}
	/*
	for(int i = 0; i < 10; i++) {
	fin >> ranking[i].x >> ranking[i].y;
	for(int j = 0; j < RANKNAME; j++) {
	fin >> rank_name[i][j];
	}
	}
	*/

	/***/
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

	Point2 temp1 = {score.getScore(), score.getLine()};
	Point2 temp2;
	char tempname1[RANKNAME] = {' ', ' ', ' ', ' ', ' ', ' '};
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

void Tetris::Save_Ranking_Name() {

	std::ofstream fout("ranking.txt");
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

	draw_str rank("rank");
	draw_str score("score");
	draw_str line("line");
	draw_str name("name");
	glPushMatrix();
	glTranslated((BOARD_WIDTH - 14) * BLOCK_SIZE, (BOARD_HEIGHT + 2) * BLOCK_SIZE, 0);
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
		glTranslated((BOARD_WIDTH - 14) * BLOCK_SIZE, (BOARD_HEIGHT - i * 2) * BLOCK_SIZE, 0);
		glScaled(1.5, 1.5, 1.5);
		ranking_str[i][0].set_str(i + 1, color.x, color.y, color.z);
		ranking_str[i][0].draw_block();

		glTranslated(4 * BLOCK_SIZE, 0, 0);
		ranking_str[i][1].set_str(ranking[i].x, color.x, color.y, color.z);
		ranking_str[i][1].draw_block();

		glTranslated(6 * BLOCK_SIZE, 0, 0);
		ranking_str[i][2].set_str(ranking[i].y, color.x, color.y, color.z);
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
	glTranslated((BOARD_WIDTH + MENU_SIZE - 2) / 2 * BLOCK_SIZE, 0, 0);
	draw_str please("please push enter key", 1, 0, 0);
	glScaled(2.0, 2.0, 2.0);
	please.draw_block(CENTER);
	glPopMatrix();

	glutSwapBuffers();
}

void Tetris::Ranking_Keyboard(unsigned char k, int x, int y) {
	switch(k) {
	case GLUT_KEY_ENTER:
		Save_Ranking_Name();
		Tetris_Init();
		mode = TITLE;
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
		if(name_pos < 5) name_pos++;
		break;
	case GLUT_KEY_LEFT:
		if(name_pos > 0) name_pos--;
		break;
	case GLUT_KEY_UP:
		if(rank_pos != -1) {
			if(rank_name[rank_pos][name_pos] == ' ') rank_name[rank_pos][name_pos] = 'A';
			else if(rank_name[rank_pos][name_pos] == 'Z') rank_name[rank_pos][name_pos] = ' ';
			else rank_name[rank_pos][name_pos]++;
		}
		break;
	case GLUT_KEY_DOWN:
		if(rank_pos != -1) {
			if(rank_name[rank_pos][name_pos] == ' ') rank_name[rank_pos][name_pos] = 'Z';
			else if(rank_name[rank_pos][name_pos] == 'A') rank_name[rank_pos][name_pos] = ' ';
			else rank_name[rank_pos][name_pos]--;
		}
		break;
	default:
		break;
	}
}
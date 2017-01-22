#include "tetris.h"

bool Tetris::Run(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("TETRIS");
	Gl_Init();
	Tetris_Init();
	Funcgroup();
	glutMainLoop();
	return run;
}

void Tetris::Funcgroup() {
	glutReshapeFunc(Reshape);
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	glutMouseWheelFunc(Mousewheel);
	glutTimerFunc(16, Timer, 0);
}

void Tetris::Reshape(int w, int h) {
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(Tetris::angle, WINDOW_WIDTH / WINDOW_HEIGHT, 0.1, 1000.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Tetris::Mouse(int b, int s, int x, int y) {
	switch(b) {
	case GLUT_LEFT_BUTTON:
		mousepoint.x = x;
		mousepoint.y = y;
		break;
	case GLUT_RIGHT_BUTTON:
		mousepoint.x = x;
		mousepoint.y = y;
		if(view_check) view_check = false;
		else view_check = true;
		break;
	}
}

void Tetris::Motion(int x, int y) {
	//std::cout << elevation << ", " << azimuth << std::endl;
	if(view_check) {
		azimuth += (double)(x - mousepoint.x) / WINDOW_WIDTH * M_PI * 2;
		elevation += (double)(y - mousepoint.y) / WINDOW_HEIGHT * M_PI * 2;
		if(elevation > M_PI / 3 ) elevation = M_PI / 3;
		else if(elevation < -M_PI / 3) elevation = -M_PI / 3;

		viewpoint.x = -view_distance * cos(elevation) * sin(azimuth);
		viewpoint.y = view_distance * sin(elevation);
		viewpoint.z = view_distance * cos(elevation) * cos(azimuth);
		//std::cout << viewpoint.x << ", " << viewpoint.y << ", " << viewpoint.z << std::endl;
		mousepoint.x = x;
		mousepoint.y = y;
	} else {
		double dx = (x - mousepoint.x) / 2;
		double dy = (y - mousepoint.y) / 2;
		center.x -= dx * cos(azimuth) - dy * sin(elevation) * sin(azimuth);
		center.y += dy * cos(elevation);
		center.z += -dx * sin(azimuth) - dy * sin(elevation) * cos(azimuth);
		//std::cout << center.x << ", " << center.y << ", " << center.z << std::endl;
		mousepoint.x = x;
		mousepoint.y = y;
	}
}

void Tetris::Mousewheel(int wheel_number, int direction, int x, int y)
{
	view_distance -= direction * 2;
	viewpoint.x = -view_distance * cos(elevation) * sin(azimuth);
	viewpoint.y = view_distance * sin(elevation);
	viewpoint.z = view_distance * cos(elevation) * cos(azimuth);
	//std::cout << view_distance << std::endl;
}

void Tetris::Timer(int value) {
	switch(mode) {
	case TITLE:
		Title();
		break;
	case TETRIS:
		Tetris_Main();
		break;
	case GAMEOVER:
		Gameover();
		break;
	case RANKING:
		Ranking();
		break;
	case TETRIS3D:
		Tetris3D();
		break;
	}
	if(!run) glutLeaveMainLoop();
	glutPostRedisplay();
	glutTimerFunc(value, Timer, 16);
}
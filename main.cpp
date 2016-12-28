#include <iostream>
#include <GL/freeglut.h>

#define TETRIS_WIDTH 10
#define TETRIS_HEIGHT 20

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600

int angle = 80;	//���_

void cube() {
	glPushMatrix();
	glColor3d(0.0, 1.0, 0.0);//�F�̐ݒ�
	glutSolidCube(100.0);//�����F(��ӂ̒���)
	glPopMatrix();
}

void display() {
	cube();
}

void reshape(int w, int h) {
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(angle, WINDOW_WIDTH / WINDOW_HEIGHT, 0.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void keyboard(unsigned char k, int x, int y) {
	switch(k) {
	case 'z':
		break;
	default:
		break;
	}
}

void specialkeyboard(int k, int x, int y) {
	switch(k) {
	case GLUT_KEY_UP:
		break;
	default:
		break;
	}
}

void initgl() {
	// �w�i�F
	glClearColor(1.0, 1.0, 1.0, 0.0);
	// �f�v�X�o�b�t�@�L��
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);


}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("TETRIS");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialkeyboard);
	initgl();
	glutMainLoop();

	return 0;
}
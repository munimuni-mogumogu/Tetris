#include <conio.h>
#include <list>
#include "Client.h"
#include "../Packet.h"

#define IP "127.0.0.1"		// サーバーIPアドレス
#define PORT 10000			// ポート番号、クライアントプログラムと合わせる

#include <GL/freeglut.h>

CClient client;
int recvsize;
char data[MAX_PACKET];

std::list<Player>	playerlist;
std::list<Player>::iterator it;
Player				*pMe = NULL;

double r = 0.0;

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(0, 0, -100,
		0, 0, 0,
		0, 1, 0);
	glPushMatrix();
	glRotated(r, 0, 1, 0);
	glColor3d(1, 0, 0);
	glutSolidCube(50);
	glPopMatrix();
	glFlush();
	// 受信処理
	RECVSTATUS status = client.Recv(data, sizeof(data), &recvsize);
	if (status == RECV_SUCCESSED) {
		Player player;
		memcpy(&player, data, sizeof(Player));
		r = player.r;
		switch (player.cmd)
		{
		case CMD_LOGIN:
			// ログインしたのは自分
			if (pMe == NULL) {
				playerlist.push_back(player);
				printf("サーバーにログインしました Socket = %d "
					"x = %d y = %d HP = %d R = %d\n",
					player.sock, player.x, player.y, player.HP, player.r);
				std::list<Player>::iterator it = playerlist.end();
				it--;
				pMe = &(*it);
			}
			// ログインしたのは自分以外
			else
			{
				playerlist.push_back(player);
				printf("Socket = %d がログインしてきました "
					"x = %d y = %d HP = %d\n",
					player.sock, player.x, player.y, player.HP);
			}
			break;
		case CMD_LOGOUT:
			printf("Socket = %d がログアウトしました \n", player.sock);
			for (it = playerlist.begin(); it != playerlist.end();) {
				if (it->sock == player.sock) {
					it = playerlist.erase(it);
					continue;
				}
				++it;
			}
			break;
		case CMD_MOVE:

			printf("Socket = %d x = %d y = %d HP = %d R = %f\n",
				player.sock, player.x, player.y, player.HP, player.r);
			r = player.r;
			for (it = playerlist.begin(); it != playerlist.end(); ++it) {
				if (it->sock == player.sock) {
					*it = player;
				}
			}

			break;
		}
	}
	// サーバから切断された
	else if (status == RECV_FAILED) {
		printf("サーバから切断されました\n");
		exit;
	}

	// 入力時
	if (_kbhit())
	{
		if (pMe != NULL)
		{
			int c = _getch();
			bool isMove = false;
			// 移動
			switch (c)
			{
			case 'w':
				pMe->cmd = CMD_MOVEUP;
				isMove = true;
				break;
			case 's':
				pMe->cmd = CMD_MOVEDOWN;
				isMove = true;
				break;
			case 'a':
				pMe->cmd = CMD_MOVELEFT;
				isMove = true;
				break;
			case 'd':
				pMe->cmd = CMD_MOVERIGHT;
				isMove = true;
				break;
			}

			if (isMove) {
				memcpy(data, pMe, sizeof(Player));
				client.Send(data, sizeof(data));
			}
		}
	}
	glutSwapBuffers();
	glutPostRedisplay();
}

void resize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0, (double)w / (double)h, 0.0, 1000.0);
	glMatrixMode(GL_MODELVIEW);
}

void init(void) {
	glClearColor(1.0, 1.0, 1.0, 1.0);
}

int main(int argc, char* argv[]) {
	
	if (!client.Connect(IP, PORT)) {
		printf("サーバへの接続に失敗しました\n");
		return -1;
	}

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(400, 400);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	init();
	glutMainLoop();
	return 0;
}
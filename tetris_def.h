#ifndef TETRIS_DEF_H
#define TETRIS_DEF_H

#define BOARD_WIDTH 12		//ボードの幅
#define BOARD_HEIGHT 22		//ボードの高さ
#define BOARD_DEPTH 12		//ボードの奥行き

#define MINO_WIDTH 3		//ミノの幅
#define MINO_HEIGHT 3		//ミノの高さ
#define MINO_DEPTH 3		//ミノの奥行き

#define BLOCK_SIZE 10		//1つのブロックの大きさ

#define MENU_SIZE 8			//メニューの大きさ

#define WINDOW_WIDTH 1600	//ウィンドウの幅
#define WINDOW_HEIGHT 800	//ウィンドウの高さ

#define GLUT_KEY_ENTER 0x000d	//エンターキー

//モード
#define TITLE 0
#define TETRIS 1
#define TETRIS3D 2
#define GAMEOVER 3
#define RANKING 4

//ランキングの名前の文字数制限(5文字)
#define RANKNAME 6

//ランキングの読み込み/保存先
#define RANKINGTXT "ranking.txt"
#define RANKING3DTXT "ranking3d.txt"

/* テンプレートパターン数 */
#define TEMPLATE_PATTERN	7

#endif
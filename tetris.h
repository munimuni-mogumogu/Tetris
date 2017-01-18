#ifndef TETRIS_H
#define TETRIS_H

/*** 定数定義 ***/
/* ボードサイズ */
#define BOARD_WIDTH		12
#define BOARD_HEIGHT	22

/* テトリミノサイズ */
#define MINO_WIDTH		3
#define MINO_HEIGHT		3

/* テンプレートパターン数 */
#define TEMPLATE_PATTERN	7

#include "tetrimino.h"
#include "board.h"
#include "score.h"
#include "tmp_struct.h"
#include "tetrimino_template.h"

#endif
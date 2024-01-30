#include "ttt.h"
class Uttt
{
public:
	ttt* ultra_board[3][3];

	Uttt();
	void DrawBoard();
	bool UpdateBoard(int Xpos, int Ypos, bool turn);
	int winState();
};


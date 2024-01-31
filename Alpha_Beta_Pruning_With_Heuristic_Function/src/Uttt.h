#include "ttt.h"
class Uttt
{
public:
	ttt ultra_board[3][3] = { {ttt(0,0),ttt(0,1),ttt(0,2)},
							  {ttt(1,0),ttt(1,1),ttt(1,2)},
							  {ttt(2,0),ttt(2,1),ttt(2,2)}};

	Uttt();
	Uttt(const Uttt& other);
	void DrawBoard();
	void UpdateBoard(int row, int col, int r, int c, bool turn);
	int winState();
	bool isFull();
	~Uttt();
};


#include "color_size.h"
class ttt{
public:
    int board[3][3] = {};
    int width;
    int height;
    bool isEnable;
    bool full;
    int win;

    ttt(int row, int col);
    void DrawBoard();
    bool isFull();
    int winState();
};

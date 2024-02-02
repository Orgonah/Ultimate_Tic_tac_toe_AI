#include "color_size.h"
class ttt{
public:
    int board[3][3] = {};
    int width;
    int height;
    bool enable;
    bool full;
    int win;

    ttt(int row, int col);
    ttt& operator=(const ttt& other);
    void DrawBoard();
    bool isFull();
    int winState();
    bool isValid(int r, int c);
    ~ttt();
};

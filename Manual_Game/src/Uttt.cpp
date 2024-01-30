#include "Uttt.h"

Uttt::Uttt() {
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            ultra_board[row][col] = new ttt(row, col);
        }
    }
}

bool Uttt::UpdateBoard(int Xpos, int Ypos, bool turn) {
    if ((Xpos >= (screenWidth / 3) && Xpos <= ((screenWidth / 3) + borderWidth / 3)) ||
        (Xpos >= 2 * (screenWidth / 3) && Xpos <= 2 * ((screenWidth / 3) + borderWidth)) ||
        (Ypos >= (screenHeight / 3) && Ypos <= ((screenHeight / 3) + borderWidth)) ||
        (Ypos >= 2 * (screenHeight / 3) && Ypos <= 2 * ((screenHeight / 3) + borderWidth))) {
        return false;

    }
    else {
        int row, col, r, c;
        row = Xpos / ((screenWidth / 3) + borderWidth);
        col = Ypos / ((screenHeight / 3) + borderWidth);
        Xpos -= row * ((screenWidth / 3) + borderWidth);
        Ypos -= col * ((screenHeight / 3) + borderWidth);
        r = Xpos / (screenWidth / 9);
        c = Ypos / (screenHeight / 9);

        if (this->ultra_board[row][col]->isEnable == false)
            return false;
        else {
            if(this->ultra_board[row][col]->board[r][c])
                return false;
                
            if (turn)
                this->ultra_board[row][col]->board[r][c] = 1;
            else
                this->ultra_board[row][col]->board[r][c] = 2;


            if (this->ultra_board[row][col]->isFull())
                this->ultra_board[row][col]->full = true;

            int win = this->ultra_board[row][col]->winState();
            if (win)
                this->ultra_board[row][col]->win = win;


            if (this->ultra_board[r][c]->full || this->ultra_board[r][c]->win)
                for (int i = 0; i < 3; i++)
                    for (int j = 0; j < 3; j++) {
                        if (this->ultra_board[i][j]->full || this->ultra_board[i][j]->win)
                            this->ultra_board[i][j]->isEnable = false;
                        else
                            this->ultra_board[i][j]->isEnable = true;
                    }

            else {
                for (int i = 0; i < 3; i++)
                    for (int j = 0; j < 3; j++)
                        this->ultra_board[i][j]->isEnable = false;
                this->ultra_board[r][c]->isEnable = true;
            }
            return true;
        }
    }
}

void Uttt::DrawBoard() {
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            this->ultra_board[row][col]->DrawBoard();
        }
    }

    DrawRectangle((screenWidth/3), 0, borderWidth, screenHeight + 2*borderWidth, purple);
    DrawRectangle((screenWidth/3) * 2 + borderWidth, 0, borderWidth, screenHeight + 2*borderWidth, purple);
    DrawRectangle(0, (screenHeight / 3), screenWidth + 2*borderWidth, borderWidth, purple);
    DrawRectangle(0, (screenHeight / 3) * 2 + borderWidth, screenWidth + 2*borderWidth, borderWidth, purple);



}

int Uttt::winState() {
    for (int row = 0; row < 3; row++) {
        if ((this->ultra_board[row][0]->winState() == 1) && (this->ultra_board[row][1]->winState() == 1) && (this->ultra_board[row][2]->winState() == 1))
            return 1;
        if ((this->ultra_board[row][0]->winState() == 2) && (this->ultra_board[row][1]->winState() == 2) && (this->ultra_board[row][2]->winState() == 2))
            return 2;
    }

    for (int col = 0; col < 3; col++) {
        if ((this->ultra_board[0][col]->winState() == 1) && (this->ultra_board[1][col]->winState() == 1) && (this->ultra_board[2][col]->winState() == 1))
            return 1;
        if ((this->ultra_board[0][col]->winState() == 2) && (this->ultra_board[1][col]->winState() == 2) && (this->ultra_board[2][col]->winState() == 2))
            return 2;
    }


    if( (this->ultra_board[0][0]->winState() == 1) && (this->ultra_board[1][1]->winState() == 1) && (this->ultra_board[2][2]->winState() == 1))
        return 1;
    if( (this->ultra_board[0][0]->winState() == 2) && (this->ultra_board[1][1]->winState() == 2) && (this->ultra_board[2][2]->winState() == 2))
        return 2;
    if( (this->ultra_board[0][2]->winState() == 1) && (this->ultra_board[1][1]->winState() == 1) && (this->ultra_board[2][0]->winState() == 1))
        return 1;
    if( (this->ultra_board[0][2]->winState() == 2) && (this->ultra_board[1][1]->winState() == 2) && (this->ultra_board[2][0]->winState() == 2))
        return 2;

    return 0;
}

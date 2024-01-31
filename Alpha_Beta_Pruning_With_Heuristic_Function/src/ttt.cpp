#include "ttt.h"

ttt::ttt(int row, int col) {
    this->width = col * ((screenWidth / 3) + borderWidth);
    this->height = row * ((screenHeight / 3) + borderWidth);
    this->win = 0;
    this->full = false;
    this->enable = true;
}

ttt& ttt::operator=(const ttt& other) {
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            this->board[row][col] = other.board[row][col];
        }
    }

    this->win = other.win;
    this->full = other.full;
    this->enable = other.enable;
    return *this;
}

void ttt::DrawBoard() {
    DrawRectangle(width, height, screenWidth / 3, screenHeight/3, darkPurple);
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            DrawLine(width + (screenWidth / 9) * col, height, width + (screenWidth / 9) * col, height + screenWidth / 3, lightPurple);
            DrawLine(width, height + (screenHeight / 9) * row, width + screenWidth/3, height + (screenHeight / 9) * row, lightPurple);

            if (board[row][col] == 1) DrawText("X", width + (screenWidth / 9)*col + screenWidth / 36, height + (screenHeight / 9) * row + screenHeight / 50, screenHeight / 12, darkGreen);
            else if (board[row][col] == 2) DrawText("O", width + (screenWidth / 9) * col + screenWidth / 36, height + (screenHeight / 9) * row + screenHeight / 50, screenHeight / 12, darkYellow);
        }

    }

    if(this->enable==false)
        DrawRectangle(width, height, screenWidth / 3, screenHeight / 3, white);

    if (this->winState() == 1) {
        DrawText("X", width + screenWidth / 15, height + screenHeight / 50, screenHeight / 3, darkerGreen);
    }
    else if (this->winState() == 2) {
        DrawText("O", width + screenWidth / 15, height + screenHeight / 50, screenHeight / 3, darkerYellow);
    }
 
}

bool ttt::isFull(){
    for (int row = 0; row < 3; row++)
        for (int col = 0; col < 3; col++)
            if (this->board[row][col] == 0)
                return false;
    return true;
}

int ttt::winState() {
    for (int row = 0; row < 3; row++) {
        if (this->board[row][0] == 1 && this->board[row][1] == 1 && this->board[row][2] == 1)
            return 1;
        if (this->board[row][0] == 2 && this->board[row][1] == 2 && this->board[row][2] == 2)
            return 2;
    }

    for (int col = 0; col < 3; col++) {
        if (this->board[0][col] == 1 && this->board[1][col] == 1 && this->board[2][col] == 1)
            return 1;
        if (this->board[0][col] == 2 && this->board[1][col] == 2 && this->board[2][col] == 2)
            return 2;
    }


    if (this->board[0][0] == 1 && this->board[1][1] == 1 && this->board[2][2] == 1)
        return 1;
    if (this->board[0][0] == 2 && this->board[1][1] == 2 && this->board[2][2] == 2)
        return 2;
    if (this->board[0][2] == 1 && this->board[1][1] == 1 && this->board[2][0] == 1)
        return 1;
    if (this->board[0][2] == 2 && this->board[1][1] == 2 && this->board[2][0] == 2)
        return 2;

    return 0;
}

int ttt::evalTwo() {
    int score = 0;
    int count1, count2;
    for (int row = 0; row < 3; row++) {
        count1 = 0;
        count2 = 0;
        for (int col = 0; col < 3; col++) {
            count1 += (this->board[row][col] == 2);
            count2 += (this->board[row][col] == 1);
        }      
        if (count1 == 2) {
            score ++;
        }
        if (count2 == 2) {
            score --;
        }
    }

    for (int col = 0; col < 3; col++) {
        count1 = 0;
        count2 = 0;
        for (int row = 0; row < 3; row++) {
            count1 += (this->board[row][col] == 2);
            count2 += (this->board[row][col] == 1);
        }
        if (count1 == 2) {
            score++;
        }
        if (count2 == 2) {
            score --;
        }
    }

    count1 = 0;
    count2 = 0;
    for (int i = 0; i < 3; i++) {
        count1 += (this->board[i][i] == 2);
        count2 += (this->board[i][i] == 1);
    }
    if (count1 == 2) {
        score ++;
    }
    if (count2 == 2) {
        score --;
    }

    count1 = 0;
    count2 = 0;
    for (int i = 0; i < 3; i++) {
        count1 += (this->board[i][2-i] == 2);
        count2 += (this->board[i][2-i] == 1);
    }
    if (count1 == 2) {
        score ++;
    }
    if (count2 == 2) {
        score --;
    }

    return score;
}

bool ttt::isValid(int r, int c) {

    if (this->enable == false)
        return false;
    if (this->board[r][c])
        return false;
    return true;
}

ttt::~ttt() {

}

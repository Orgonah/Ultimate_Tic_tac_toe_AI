#include <iostream>
#include <algorithm>
#include <chrono>
#include <thread>
#include "Uttt.h"

using namespace std;

const int MAX = 1000;
const int MIN = -1000;

long long int counter = 0;
int minimax(Uttt board,
	bool maximizingPlayer,
	int alpha, int beta,
	int Row, int Col,
	int R, int C, int depth)
{

	if (Row != -1) {
		board.UpdateBoard(Row, Col, R, C, maximizingPlayer);
		
	}

	int win = board.winState();
	if (win == 1) {
		return -1;
	}
	else if (win == 2) {
		return 1;
	}

	bool full = true;
	int best;
	if (maximizingPlayer) {
		best = MIN;
		for (int row = 0; row < 3; row++) {
			for (int col = 0; col < 3; col++) {
				if (board.ultra_board[row][col].enable) {
					full = false;
					for (int r = 0; r < 3; r++) {
						for (int c = 0; c < 3; c++) {
							if (board.ultra_board[row][col].isValid(r, c)) {

								int val = minimax(board, false, alpha, beta, row, col, r, c, depth+1);
								if (R == -1) {
									return row + col * 10 + r * 100 + c * 1000;
								}
								if (val == 1) {
									return 1;
								}

								best = max(best, val);
								alpha = max(alpha, best);
								board.ultra_board[row][col].board[r][c] = 0;
								if (beta <= alpha)
									break;
							}
						}
					}
				}
			}	
		}
	}

	else {
		best = MAX;
		for (int row = 0; row < 3; row++) {
			for (int col = 0; col < 3; col++) {
				if (board.ultra_board[row][col].enable) {
					full = false;
					for (int r = 0; r < 3; r++) {
						for (int c = 0; c < 3; c++) {
							if (board.ultra_board[row][col].isValid(r, c)) {

								int val = minimax(board, true, alpha, beta, row, col, r, c, depth + 1);
								if (R == -1) {
									return row + col * 10 + r * 100 + c *1000;
								}
								if (val == 1) {
									return 1;
								}
								best = min(best, val);
								beta = min(beta, best);
								board.ultra_board[row][col].board[r][c] = 0;
								if (beta <= alpha)
									break;
							}
						}
					}
				}
			}
		}
	}
	if (full) {
		return 0;
	}
	return best;
}

//r width x
//c height y

//true 1 X user
//false 2 O bot
int main() {
    Uttt board;

    InitWindow((screenWidth + 2 * borderWidth), (screenHeight + 2 * borderWidth) + 50, "ULTIMATE TIC-TAC-TOE!");
    SetTargetFPS(60);
    int Xpos, Ypos, row, col, r, c;
    bool turn = true, success;
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
		if (turn) {
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
				Xpos = GetMouseX();
				Ypos = GetMouseY();
				if ((Xpos >= (screenWidth / 3) && Xpos <= ((screenWidth / 3) + borderWidth / 3)) ||
					(Xpos >= 2 * (screenWidth / 3) && Xpos <= 2 * ((screenWidth / 3) + borderWidth)) ||
					(Ypos >= (screenHeight / 3) && Ypos <= ((screenHeight / 3) + borderWidth)) ||
					(Ypos >= 2 * (screenHeight / 3) && Ypos <= 2 * ((screenHeight / 3) + borderWidth))) {

				}
				else {
					col = Xpos / ((screenWidth / 3) + borderWidth);
					row = Ypos / ((screenHeight / 3) + borderWidth);
					Xpos -= col * ((screenWidth / 3) + borderWidth);
					Ypos -= row * ((screenHeight / 3) + borderWidth);
					c = Xpos / (screenWidth / 9);
					r = Ypos / (screenHeight / 9);
					success = board.ultra_board[row][col].isValid(r, c);
					if (success) {
						board.UpdateBoard(row, col, r, c, turn);
						turn ^= 1;
					}
				}
			}
		}
		else {
			int val = minimax(board, true, MIN, MAX, -1, -1, -1, -1, 0);
			row = val % 10;
			val /= 10;
			col = val % 10;
			val /= 10;
			r = val % 10;
			val /= 10;
			c = val % 10;
			val /= 10;
			board.UpdateBoard(row, col, r, c, turn);
			turn ^= 1;
		}
        if (board.winState() == 1) {
            DrawText("Player X won", (screenWidth + 2 * borderWidth) / 2 - 130, (screenHeight + 2 * borderWidth), 40, darkGreen);
        }
        if (board.winState() == 2) {
            DrawText("Player O won", (screenWidth + 2 * borderWidth) / 2 - 130, (screenHeight + 2 * borderWidth), 40, darkYellow);
        }
        board.DrawBoard();
        EndDrawing();
    }

    CloseWindow();
    return 0;


}
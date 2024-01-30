#include "Uttt.h"

//r width x
//c height y
int main()
{
    Uttt board;

    InitWindow((screenWidth + 2 * borderWidth), (screenHeight + 2 * borderWidth) + 50, "ULTIMATE TIC-TAC-TOE!");
    SetTargetFPS(60);
    int Xpos, Ypos;
    bool turn = true, success;
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Xpos = GetMouseX();
            Ypos = GetMouseY();
            success = board.UpdateBoard(Xpos, Ypos, turn);
            if (success)
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
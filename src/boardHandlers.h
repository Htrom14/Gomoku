#include <string>
#include <stdlib.h>
#include <iostream>
#include <deque>
void makeMoveOnBoard(int board[15][15], int x, int y, int playerTurn);
void translateMoveToCoords(std::string myStr,  int* outRow, int* outCol);
void translateCoordsIntoMove(int moveRow, int moveCol, char* strOut);
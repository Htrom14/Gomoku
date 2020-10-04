#include <string>
#include <stdlib.h>
#include <iostream>
#include <deque>
#include <array>

void makeMoveOnBoard(int board[15][15], int x, int y, int playerTurn);
void translateMoveToCoords(std::string myStr,  int* outRow, int* outCol);
void translateCoordsIntoMove(int moveRow, int moveCol, char* strOut);
void getListOfMoves(std::array<std::array<int, 15>, 15> board, int turn, std::deque<std::array<std::array<int, 15>, 15>> *boardList);
#include <string>
#include <stdlib.h>
#include <iostream>
#include <deque>
#include <array>
#include <vector>

void makeMoveOnBoard(std::array<std::array<int, 15>, 15> board, int x, int y, int playerTurn);
void translateMoveToCoords(std::string myStr,  int* outRow, int* outCol);
void translateCoordsIntoMove(int moveRow, int moveCol, char* strOut);
std::vector<std::array<int, 2>> getListOfMoves(std::array<std::array<int, 15>, 15> board, int turn, std::deque<std::array<std::array<int, 15>, 15>> *boardList, std::vector<std::array<int, 2>> previousMoves);
std::vector<std::array<int, 2>> getNeighborsOf8(int x, int y);

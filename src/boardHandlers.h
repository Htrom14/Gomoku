#include <string>
#include <stdlib.h>
#include <iostream>
#include <deque>
#include <array>
#include <vector>
#include <algorithm>

void makeMoveOnBoard(std::array<std::array<int, 15>, 15> &board, int x, int y, int playerTurn);
void translateMoveToCoords(std::string myStr,  int* outRow, int* outCol);
void translateCoordsIntoMove(int moveRow, int moveCol, char* strOut);
bool checkInPrevMoves(const std::vector<std::array<int, 2>> &previousMoves, const  std::array<int, 2> &move);
std::vector<std::array<int, 2>> getListOfMoves(std::array<std::array<int, 15>, 15> board, int turn, std::deque<std::array<std::array<int, 15>, 15>> *boardList, std::vector<std::array<int, 2>> previousMoves);
std::vector<std::array<int, 2>> getNeighborsOf8(int x, int y);

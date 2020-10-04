#ifndef Node_H
#define Node_H
#include<iostream> 
#include <deque>
#include "boardHandlers.h"


class Node
{
public:
    Node(int turn, std::array<std::array<int, 15>, 15> board, int depth, int previousX, int previousY);
    int depth;
    int turn;
    int previousX, previousY;
    bool terminal;
    int evaluation;
    std::array<std::array<int, 15>, 15> board;
    int minmax;
    std::deque<Node> children;
    int updateMinMax(int depthLevel, bool maximizingPlayer);
    int evaluate();
    void printBoard();
    int getMinMax();
    std::deque<Node> getChildren();
};

#endif
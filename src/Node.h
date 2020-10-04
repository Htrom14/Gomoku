#ifndef Node_H
#define Node_H
#include<iostream> 
#include <deque>
#include "boardHandlers.h"


class Node
{
public:
    Node(int turn, int board[15][15], int depth);
    int depth;
    int turn;
    bool terminal;
    int board[15][15];
    int evaluation;
    int minmax;
    std::deque<Node> children;
    int updateMinMax(Node node, int depthLevel, bool maximizingPlayer);
    int evaluate();
    void printBoard();
    int getMinMax();
    std::deque<Node> getChildren();
};

#endif
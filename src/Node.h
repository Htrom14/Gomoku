#ifndef Node_H
#define Node_H
#include<iostream> 
#include <deque>
#include "boardHandlers.h"


class Node
{
public:
    Node(int turn, std::array<std::array<int, 15>, 15> board, int depth);
    int depth;
    int turn;
    std::array<std::array<int, 15>, 15> board;
    int heuristic;
    int minmax;
    std::deque<Node> children;
    int updateMinMax();
    void updateHeuristic();
    void printBoard();
    int getMinMax();
    int getHeuristic();
    std::deque<Node> getChildren();
};

#endif
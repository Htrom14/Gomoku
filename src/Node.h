#ifndef Node_H
#define Node_H
#include<iostream> 
#include <deque>


class Node
{
public:
    Node(int turn, int board[15][15], int depth);
    int depth;
    int turn;
    int board[15][15];
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
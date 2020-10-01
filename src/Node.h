#ifndef Node_H
#define Node_H
#include<iostream> 

class Node
{
public:
    Node(int turn, int board[15][15]);
    int turn;
    int board[15][15];
    int heuristic;
    int minmax;
    void updateMinMax();
    void updateHeuristic();
    void printBoard();
    int getMinMax();
    int getHeuristic();
};

#endif
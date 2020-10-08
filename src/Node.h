#ifndef Node_H
#define Node_H
#include<iostream> 
#include <deque>
#include "boardHandlers.h"


class Node
{
public:
    Node(int turn1, std::array<std::array<int, 15>, 15> board1, int depth1, int previousX1, int previousY1, std::vector<std::array<int, 2>> previousMoves);
    int depth;
    int turn;
    int previousX, previousY;
    bool terminal;
    int evaluation;
    std::array<std::array<int, 15>, 15> board;
    int minmax;
    std::vector<std::array<int, 2>> previousMoves;
    std::deque<Node> children;
    int evaluate(Node& node);
    void evaluateHelper(bool isEmptyBackwards, bool isEmptyForwards, int numInRow, bool isAi, std::vector<int>* aiScores, std::vector<int> * enemyScores);
    void printBoard();
    int getMinMax();
    void getChildren();
    void printMoveOrder(int eval, int numMove);
    void alphaBetaSearch(std::array<int, 2> *myMove);
    int getMaxValue(Node *node, int depthLevel, int alpha, int beta);
    int getMinValue(Node *node, int depthLevel, int alpha, int beta);
    std::deque<Node> getBestChildren();
    int forwardPrune(int depthLevel);
};

#endif
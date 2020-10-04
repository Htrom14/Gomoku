#include "Node.h"

using namespace std; 

/***
*  Constructor for a node
*  @param turn The turn of the player
*  @param board The current state of the board
*  @return the newly created node object
*/
Node::Node(int turn1, int board1[15][15], int depth1)
{ 
    depth = depth1;
    turn = turn1;
    for(int i = 0; i < 15; i++){
        for(int j = 0; j < 15; j++){
            board[j][i] = board1[j][i];
        }
    }
}

void Node::updateHeuristic(){
    //TODO
    
}

void Node::updateMinMax(){
    //TODO
    // Lookup their heuristic
}

void Node::printBoard(){
    for(int i = 0; i < 15; i++){
        for(int j = 0; j < 15; j++){
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

int Node::getHeuristic(){
    return heuristic;
}

int Node::getMinMax(){
    return minmax;
}

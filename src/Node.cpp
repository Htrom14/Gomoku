#include "Node.h"

using namespace std; 

const int TERMINAL_DEPTH = 5;

/***
*  Constructor for a node
*  @param turn The turn of the player
*  @param board The current state of the board
*  @return the newly created node object
*/
Node::Node(int turn1, std::array<std::array<int, 15>, 15> board1, int depth1)
{ 
    depth = depth1;
    turn = turn1;
    for(int i = 0; i < 15; i++){
        for(int j = 0; j < 15; j++){
            board[i][j] = board1[i][j];
        }
    }
}

/**
 *  Evaluates the current status of the board
 *  @return the evaluation value
 *  */
int Node::evaluate(){
    evaluation = 1;
    return evaluation;
}

/**
 * Updates the min max value of this node
 * @return the min max value of this node 
 * */

int Node::updateMinMax(int depthLevel, bool maximizingPlayer){
    int eval, maxEval, minEval;
    if(depthLevel == TERMINAL_DEPTH || terminal == true){ 
        return evaluate(); //Evaluation of node
    }

    if(maximizingPlayer){
        maxEval = -1000000;
        for(Node child : children){
            eval = child.updateMinMax(depthLevel + 1, false);
            if(eval > maxEval){
                maxEval = eval;
            }
        }
        return maxEval;
    }
    else{
        minEval = 1000000;
        for(Node child : children){
            eval = child.updateMinMax(depthLevel + 1, true);
            if(eval < minEval){
                eval = minEval;
            }
        }
        return minEval;
    }
}

/**
 * getChildren: creates node objects corresponding to the current node
 * @return deque of Node objects  
 * */
std::deque<Node> Node::getChildren() {
    std::deque<std::array<std::array<int, 15>, 15>> childBoards;
    std::deque<Node> childNodes;
    getListOfMoves(board, 3-turn, &childBoards);
    for (int i = 0; i < childBoards.size(); i++) {
        childNodes.emplace_front(Node(3-turn, childBoards[i], depth+1));
    }
    children = childNodes;
    return childNodes;
}

void Node::printBoard(){
    for(int i = 0; i < 15; i++){
        for(int j = 0; j < 15; j++){
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

int Node::getMinMax(){
    return minmax;
}

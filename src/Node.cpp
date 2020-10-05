#include "Node.h"

using namespace std; 

const int TERMINAL_DEPTH = 10;

/***
*  Constructor for a node
*  @param turn The turn of the player
*  @param board The current state of the board
*  @return the newly created node object
*/
Node::Node(int turn1, std::array<std::array<int, 15>, 15> board1, int depth1, int previousX1, int previousY1)
{ 
    previousX = previousX1;
    previousY = previousY1;
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
    //loop through board
    int score = 0;

    for(int i = 0; i < 15; i++){
        for(int j = 0; j < 15; j ++){
            if(board[i][j] != 0){
                for(std::array<int, 2> neighbor : getNeighborsOf8(i, j)){
                    if(board[i][j] == 1){
                        if(board[neighbor[0]][neighbor[1]] == 1){
                            score++;
                        }
                    }
                    else{
                        if(board[neighbor[0]][neighbor[1]] == 2){
                            score--;
                        }
                    }
                }
            }
        }
    }
    // grab neighbors at each point
    // checkneighbors for matching turn as the given point
    return score;
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




int Node::getMaxValue(Node *node, int depthLevel, int alpha, int beta) {
    int eval = -10000000;
    if(depthLevel == TERMINAL_DEPTH || terminal == true){ 
        return evaluate(); //Evaluation of node
    }
    node->getChildren();
    for (Node &child : node->children) {
        child.minmax = child.getMinValue(&child, depthLevel+1, alpha, beta);
        //cout << child.minmax << endl;
        eval = max(eval, child.minmax);
        if (eval >= beta) {
            minmax = eval;
            return eval;
        }
        alpha = max(alpha, eval);
        //child.evaluation = 100;
        //child.minmax = eval;
    } 
    return eval;
}

int Node::getMinValue(Node *node, int depthLevel, int alpha, int beta) {
    int eval = 10000000;
    if(depthLevel == TERMINAL_DEPTH || terminal == true){ 
        return evaluate(); //Evaluation of node
    }
    node->getChildren();
    for (Node &child : node->children) {
        eval = min(eval, child.getMaxValue(&child, depthLevel+1, alpha, beta));
        if (eval <= alpha) {
            //minmax = eval;
            return eval;
        }
        beta = min(beta, eval);
        
    }
    //minmax = beta;
    return eval;
}

void Node::alphaBetaSearch(std::array<int, 2> *myMove) {
    int v = getMaxValue(this, 0, -10000000, 10000000);
    cout << v << endl;
    int eval;
    for (Node child : children) {
        //cout << child.evaluation << endl;
        if (child.minmax == v) {
            (*myMove)[0] = child.previousX;
            (*myMove)[1] = child.previousY;
            //cout << child.previousX << " " << child.previousY << endl;
            return;
        }
    }
}


/**
 * getChildren: creates node objects corresponding to the current node
 * @return deque of Node objects  
 * */
std::deque<Node> Node::getChildren() {
    std::deque<std::array<std::array<int, 15>, 15>> childBoards;
    std::deque<Node> childNodes;
    std::vector<std::array<int, 2>> correspondingMoves = getListOfMoves(board, 3-turn, &childBoards);
    for (int i = 0; i < childBoards.size(); i++) {
        childNodes.emplace_front(Node(3-turn, childBoards[i], depth+1, correspondingMoves.at(i)[0], correspondingMoves.at(i)[1]));
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

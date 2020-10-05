#include "Node.h"

using namespace std; 

const int TERMINAL_DEPTH = 4;

/***
*  Constructor for a node
*  @param turn The turn of the player
*  @param board The current state of the board
*  @return the newly created node object
*/
Node::Node(int turn1, std::array<std::array<int, 15>, 15> board1, int depth1, int previousX1, int previousY1, std::vector<std::array<int, 2>> previousMoves1)
{ 
    terminal = false;
    previousX = previousX1;
    previousY = previousY1;
    previousMoves = previousMoves1;
    depth = depth1;
    turn = turn1;
    std::array<int, 2> previousMove = {previousX, previousY};
    previousMoves.push_back(previousMove);

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

    for(std::array<int, 2> move : previousMoves){
        for(std::array<int, 2> neighbor : getNeighborsOf8(move[0], move[1])){
            if(board[move[0]][move[1]] == 1){
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
            child.getChildren();
            eval = child.updateMinMax(depthLevel + 1, false);
            if(eval > maxEval){
                maxEval = eval;
            }
        }
        //  if(maxEval < -100000){
            // cout << "PreviousX: " << previousX << " PreviousY: " << previousY << " Score: " << minEval << endl;
            // printBoard();
        // }
        return maxEval;
    }
    else{
        minEval = 1000000;
        // if(children.size() == 0){
        //     cout << "Problem" << endl;
        // }
        int size = children.size();
        for(Node child : children){
            child.getChildren();            
            eval = child.updateMinMax(depthLevel + 1, true);
            if(eval < minEval){
                minEval = eval;
            }
        }
        // if(minEval > 100000){
            // cout << size << endl;
            // cout << "Depth: " << depthLevel << endl;
            // cout << "PreviousX: " << previousX << " PreviousY: " << previousY << " Score: " << minEval << endl;
            // printBoard();
        // }
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
    std::vector<std::array<int, 2>> correspondingMoves = getListOfMoves(board, 3-turn, &childBoards, previousMoves);
    for (int i = 0; i < childBoards.size(); i++) {
        childNodes.emplace_front(Node(3-turn, childBoards[i], depth+1, correspondingMoves.at(i)[0], correspondingMoves.at(i)[1], previousMoves));
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

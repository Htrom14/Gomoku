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
 *  Helper function for evaluation. Modifies aiScores and enemyScores
 *  */
void Node::evaluateHelper(bool isEmptyBackwards, bool isEmptyForwards, int numInRow, bool isAi, vector<int> * aiScores, vector<int> * enemyScores){
    if (numInRow >= 5){
        if (isAi) (*aiScores)[5]++;
        else (*enemyScores)[5]++;
    }else if (numInRow == 4 && (isEmptyBackwards || isEmptyForwards)){ 				
        if (isAi) (*aiScores)[4]++;
        else (*enemyScores)[4]++;
    }else if (numInRow == 3 && (isEmptyBackwards || isEmptyForwards)){
        if (isAi) (*aiScores)[3]++;
        else (*enemyScores)[3]++;
    }else if (numInRow == 3 && (isEmptyBackwards && isEmptyForwards)){
        if (isAi) (*aiScores)[2]++;
        else (*enemyScores)[2]++;
    }else if (numInRow == 2 && (isEmptyBackwards && isEmptyForwards)){
        if (isAi) (*aiScores)[1]++;
        else (*enemyScores)[1]++;
    }
}


/**
 *  Evaluates the current status of the board. Checks to see number of pieces in a row for a played move. If that move is not cut off in the front, add it to a score vector
 *  Apply increasing score modifiers to score vectors that have a more piecies in a row. Add these values to total score.
 *  @return the evaluation value
 *  */
int Node::evaluate(){
    int score = 0;
    vector<int> * aiScores = new vector<int>(6,0);
	vector<int> * enemyScores = new vector<int>(6,0);

    for(std::array<int, 2> move : previousMoves){
				int turn = board[move[0]][move[1]];
				bool isAi = turn == 1;		
				
				int numInRow = 1;
				int overShootBackwards = 1;
				while (move[0]- overShootBackwards >= 0 && board[move[0]-overShootBackwards][move[1]]  == turn){
					numInRow++;
					overShootBackwards++;
				}
				
				int overShootForwards = 1;
				while (move[0] + overShootForwards <= 14 && board[move[0] + overShootForwards][move[1]] == turn){
					numInRow++;
					overShootForwards++;
				}

                bool isEmptyBackwards = board[move[0]-overShootBackwards][move[1]] == 0;
                bool isEmptyForwards = board[move[0]+overShootForwards][move[1]] == 0;
				evaluateHelper(isEmptyBackwards, isEmptyForwards, numInRow, isAi, aiScores, enemyScores);


				numInRow = 1;
				overShootBackwards = 1;
                while (move[1]- overShootBackwards >= 0 && board[move[0]][move[1]-overShootBackwards]  == turn){
					numInRow++;
					overShootBackwards++;
				}

				overShootForwards = 1;
				while (move[1] + overShootForwards  <= 14 && board[move[0]][move[1]+overShootForwards] == turn){
					numInRow++;
					overShootForwards++;
				}

                isEmptyBackwards = board[move[0]][move[1]-overShootBackwards] == 0;
                isEmptyForwards = board[move[0]][move[1]+overShootForwards] == 0;
                evaluateHelper(isEmptyBackwards, isEmptyForwards, numInRow, isAi, aiScores, enemyScores);

				numInRow = 1;
				overShootBackwards = 1;
                while (move[1]- overShootBackwards >= 0 && board[move[0]-overShootBackwards][move[1]-overShootBackwards]  == turn){
					numInRow++;
					overShootBackwards++;
				}
				overShootForwards = 1;
				while (move[1] + overShootForwards <= 14 && board[move[0]+overShootForwards][move[1]+overShootForwards] == turn){
					numInRow++;
					overShootForwards++;
				}

                isEmptyBackwards = board[move[0]-overShootBackwards][move[1]-overShootBackwards] == 0;
                isEmptyForwards = board[move[0]+overShootForwards][move[1]+overShootForwards] == 0;
                evaluateHelper(isEmptyBackwards, isEmptyForwards, numInRow, isAi, aiScores, enemyScores);


				numInRow = 1;
				overShootBackwards = 1;
                while (move[1]- overShootBackwards >= 0 && board[move[0]-overShootBackwards][move[1]+overShootBackwards]  == turn){
					numInRow++;
					overShootBackwards++;
				}
				
				overShootForwards = 1;
				while (move[1] + overShootForwards <= 14 && board[move[0]+overShootForwards][move[1]-overShootForwards] == turn){
					numInRow++;
					overShootForwards++;
				}

                isEmptyBackwards = board[move[0]-overShootBackwards][move[1]+overShootBackwards] == 0;
                isEmptyForwards = board[move[0]+overShootForwards][move[1]-overShootForwards] == 0;
                evaluateHelper(isEmptyBackwards, isEmptyForwards, numInRow, isAi, aiScores, enemyScores);
    }

    if ((*aiScores)[5] > 0) {
        terminal = true;
        return 1000000000;
    }
	if ((*enemyScores)[5] > 0) {
        terminal = true;
        return -1000000000;
    } 
	int scoreModifier = 1;
	score += (*aiScores)[1];
	score -= (*enemyScores)[1]*2;

	for (int i = 2 ; i < 5 ; i++){
		scoreModifier *= 100;
		score += (*aiScores)[i] * scoreModifier;
		score -= (*enemyScores)[i] * scoreModifier * 10;
	}
    return score;
}


int Node::getMaxValue(Node *node, int depthLevel, int alpha, int beta) {
    int eval = -1000000000;
    if(depthLevel == TERMINAL_DEPTH || terminal == true){ 
        minmax = evaluate();
        return minmax; //Evaluation of node
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
    int eval = 1000000000;
    if(depthLevel == TERMINAL_DEPTH || terminal == true){ 
        minmax = evaluate();
        return minmax; //Evaluation of node
    }
    node->getChildren();
    for (Node &child : node->children) {
        child.minmax = child.getMaxValue(&child, depthLevel+1, alpha, beta);
        eval = min(eval, child.minmax);
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
    int v = getMaxValue(this, 0, -1000000000, 1000000000);
    cout << "BEST MINIMAX FOR MY TURN: " << v << endl;
    int eval;
    for (Node child : children) { 
        if (v == 1000000000) {
            if (child.minmax == v && child.terminal) {
                (*myMove)[0] = child.previousX;
                (*myMove)[1] = child.previousY;
                return;    
            }
        }
        else if (child.minmax == v) {
            //child.printMoveOrder(v, 1);
            (*myMove)[0] = child.previousX;
            (*myMove)[1] = child.previousY;
            //cout << child.previousX << " " << child.previousY << endl;
            return;
        }
    }
}

void Node::printMoveOrder(int eval, int numMove) {
    cout << endl << "Move " << numMove << ":" << endl;
    cout << previousX << " " << previousY << " Minmax: " << minmax << endl;
    printBoard();
    if (children.size() > 0) {
        for (Node child: children) {
            if (child.minmax == eval) {
                child.printMoveOrder(eval, numMove+1);
                return;
            }
        }
        cout << "no minmax" << endl;
    }
    
}


/**
 * getChildren: creates node objects corresponding to the current node
 * @return deque of Node objects  
 * */
void Node::getChildren() {
    std::deque<std::array<std::array<int, 15>, 15>> childBoards;
    std::deque<Node> childNodes;
    std::vector<std::array<int, 2>> correspondingMoves = getListOfMoves(board, 3-turn, &childBoards, previousMoves);
    for (int i = 0; i < childBoards.size(); i++) {
        childNodes.emplace_front(Node(3-turn, childBoards[i], depth+1, correspondingMoves.at(i)[0], correspondingMoves.at(i)[1], previousMoves));
    }
    children = childNodes;
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

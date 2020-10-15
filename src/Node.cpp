#include "Node.h"

using namespace std; 

const int TERMINAL_DEPTH = 3;

/***
*  Constructor for a node
*  @param turn The turn of the player
*  @param board The current state of the board
*  @return the newly created node object
*/
Node::Node(int turn1, std::array<std::array<int, 15>, 15> board1, int depth1, int previousX1, int previousY1, std::vector<std::array<int, 2>> &previousMoves1)
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
int Node::evaluate(Node& node){
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

	if ((*enemyScores)[5] > 0) {
        node.terminal = true;
        return -1000000000;
    } 
    if ((*aiScores)[5] > 0) {
        node.terminal = true;
        return 1000000000;
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

/**
 * The max node of Minimax, with alpha beta pruning
 * @param node the current node, where max is making the decision
 * @param depthLevel the depth level of this expansion in search tree
 * @param alpha the minimum possible value up to this point so far (this node)
 * @param beta the maximum possible value up to this point so far (this node)
 * @return maximum possible value at this node
 * */
int Node::getMaxValue(Node &node, int depthLevel, int alpha, const int beta) {
    int alpha2 = alpha;
    int eval = -1000000000;
    int thisNode = evaluate(node);
    if(depthLevel == TERMINAL_DEPTH || node.terminal){ 
        //we've won
        minmax = thisNode;
        return minmax; //Evaluation of node
    }
    node.getChildren();
    for (Node &child : node.children) {
        //update the childs minmax so we know which one to pick later, and print
        child.minmax = child.getMinValue(child, depthLevel+1, alpha2, beta);
        eval = max(eval, child.minmax);
        if (eval >= beta) {
            //minmax = eval;
            return eval;
        }
        alpha2 = max(alpha2, eval);
    } 
    return eval;
}

/**
 * The min node of Minimax, with alpha beta pruning
 * @param node the current node, where min is making the decision
 * @param depthLevel the depth level of this expansion in search tree
 * @param alpha the minimum possible value up to this point so far (this node)
 * @param beta the maximum possible value up to this point so far (this node)
 * @return minimum possible value at this node
 * */
int Node::getMinValue(Node &node, int depthLevel, const int alpha, int beta) {
    int eval = 1000000000;
    int beta2 = beta;
    int thisNode = evaluate(node);
    if(depthLevel == TERMINAL_DEPTH || node.terminal){ 
        //this is either the end, we've lost/won, or its a bad node
        minmax = thisNode;
        return minmax; //Evaluation of node
    }
    node.getChildren();
    for (Node &child : node.children) {
        
        //update the childs minmax so we know which one to pick later, and print
        child.minmax = child.getMaxValue(child, depthLevel+1, alpha, beta2);
        eval = min(eval, child.minmax);
        if (eval <= alpha) {
            return eval;
        }
        beta2 = min(beta2, eval); 
    }
    return eval;
}

/**
 * alphaBetaSearch: constructs a search tree from the node this is called on
 * prunes put nodes that won't change the actual result to save time (see alpha, beta)
 * prints out the best minimax value 
 * @param myMove array to place the decided upon move
 * */
void Node::alphaBetaSearch(std::array<int, 2> *myMove) {
    int v = getMaxValue(*this, 0, -1000000000, 1000000001);
    cout << "BEST MINIMAX FOR MY TURN: " << v << endl;
    int eval;
    cout << "CHILDREN SIZE:" << children.size() << endl;
    //v = this->forwardPrune(0);
    int i = 0;
    for (Node &child : children) { 
        if (v == 1000000000) {
            //this is to make sure we make the winning move if we have it
            //cout << "Max value" << endl;
            int test = child.evaluate(child);
            if (child.minmax == v && child.terminal) {
                (*myMove)[0] = child.previousX;
                (*myMove)[1] = child.previousY;
                return;    
            }
            else if (child.minmax == v) {
                (*myMove)[0] = child.previousX;
                (*myMove)[1] = child.previousY;
            }
        }
        else if (child.minmax == v) {
            (*myMove)[0] = child.previousX;
            (*myMove)[1] = child.previousY;
            return;
        }
        i++;
    }
    return;
}

std::deque<Node> Node::getBestChildren(){
    // Select best  3 children
    std::deque<std::array<int, 2>> goodChildrenIndexMinMax;
    std::deque<Node> goodChildren;
    for(int i = 0; i < 3; i++){
        goodChildrenIndexMinMax.emplace_front(std::array<int,2>{-1,-1000000000});
    }
    int currentMinMax;
    for(int i = 0; i < children.size(); i++){
        currentMinMax = children.at(i).minmax;
        for(int j = 0; j < 3; j++){
            if(currentMinMax > goodChildrenIndexMinMax.at(j)[1]){
                goodChildrenIndexMinMax.at(j) = {i, currentMinMax};
                break;
            }
        }
    }

    for(int i = 0; i < 3; i++){
        goodChildren.push_back(children.at(goodChildrenIndexMinMax.at(i)[0]));
    }

    return  goodChildren;
}

int Node::forwardPrune(int depthLevel){
    if(depthLevel == 3){ 
        return minmax; //Evaluation of node
    }
    // get best children
    // alphaBetaSearch on them again
    // I want to then figure out who is the best child
    children = getBestChildren();

    // for(Node child : children){
    //     cout << child.minmax << endl;
    //     child.printBoard();
    //     cout << endl << endl;
    // }
    int childMax = -100000000;
    for(Node &child : children){
        if(depthLevel % 2 == 1){
            getMinValue(child, 0, -1000000000, 1000000001);
        } else if(depthLevel > 0){
            getMaxValue(child, 0, -1000000000, 1000000001);
        }
        child.minmax = child.forwardPrune(depthLevel+1);
        if(child.minmax > childMax){
            childMax = child.minmax;
        }
    }
    return childMax;
}


/**
 * printMoveOrder is for showing the tree that node follows to its chosen minimax val
 * @param eval the minimax value to be matching
 * @param numMove number for "how far down the tree are we right now"
 * */
void Node::printMoveOrder(int eval, int numMove) {
    //print out this moves statistics
    cout << endl << "Move " << numMove << ":" << endl;
    cout << previousX << " " << previousY << " Minmax: " << minmax << endl;
    printBoard();
    if (children.size() > 0) {
        for (Node child: children) {
            //find the child that gave this node its minmax value, print it next
            if (child.minmax == eval) {
                child.printMoveOrder(eval, numMove+1);
                return;
            }
        }
        //this shouldn't ever be reached, but it would let us know a node isn't setting 
        //it's minimax val properly
        cout << "no minmax" << endl;
    }
    
}


/**
 * getChildren: creates node objects corresponding to the current node
 * No return, but sets the children of the node it is called on  
 * */
void Node::getChildren() {
    std::deque<std::array<std::array<int, 15>, 15>> childBoards;
    std::deque<Node> childNodes;
    std::vector<std::array<int, 2>> correspondingMoves = getListOfMoves(board, 3-turn, &childBoards, previousMoves);
    if (childBoards.size() != correspondingMoves.size()) {
        cout << "HOUSTON: WE HAVE A PROBLEM" << endl;
    }
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

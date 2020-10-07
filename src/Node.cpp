#include "Node.h"

using namespace std; 

const int TERMINAL_DEPTH = 5;

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
// int Node::evaluate(){
//     //loop through board
//     int score = 0;

//     for(std::array<int, 2> move : previousMoves){
//         for(std::array<int, 2> neighbor : getNeighborsOf8(move[0], move[1])){
//             if(board[move[0]][move[1]] == 1){
//                 if(board[neighbor[0]][neighbor[1]] == 1){
//                     score++;
//                 }
//             }
//             else{
//                 if(board[neighbor[0]][neighbor[1]] == 2){
//                     score--;
//                 }
//             }
//         }
//     }
//     return score;
// }
int Node::evaluate(){
    //loop through board
    int score = 0;
    vector<int> computerPattern(6,0);
	vector<int> playerPattern(6,0);
    for(std::array<int, 2> move : previousMoves){
        	    //count patterns in columns
				int c = board[move[0]][move[1]];

                //cout << "C: " << c << endl;
				bool needMax = c == 1;
				
				
				
				int sameSymbol = 1; // count same symbols in columns 
				int k = 1;
				while (move[0]- k >= 0 && board[move[0]-k][move[1]]  == c){
					sameSymbol++;
					k++;
				}
				
				
				//consider value at i - k later to see if it's blocked or not
				int l = 1;
				while (move[0] + l <= 14 && board[move[0] + l][move[1]] == c){
					sameSymbol++;
					l++;
				}

                //cout << "SameSymbol: " << sameSymbol << endl;
				if (sameSymbol >= 5){
					if (needMax) computerPattern[5]++;
					else playerPattern[5]++;
				}else if (sameSymbol == 4 && (board[move[0]-k][move[1]] == 0 || board[move[0]+l][move[1]] == 0)){ 				
					//cout << "here" << endl;
                    if (needMax) computerPattern[4]++;
					else playerPattern[4]++;
				}else if (sameSymbol == 3 && (board[move[0]-k][move[1]] == 0 || board[move[0]+l][move[1]] == 0)){
					if (needMax) computerPattern[3]++;
					else playerPattern[3]++;
				}else if (sameSymbol == 3 && (board[move[0]-k][move[1]] == 0 && board[move[0]+l][move[1]] == 0)){
					if (needMax) computerPattern[2]++;
					else playerPattern[2]++;
				}else if (sameSymbol == 2 && (board[move[0]-k][move[1]] == 0 && board[move[0]+l][move[1]] == 0)){
					if (needMax) computerPattern[1]++;
					else playerPattern[1]++;
				}

				//-------------------------------------------------------------------------------
				sameSymbol = 1; // count same symbols in rows
				k = 1;
                while (move[1]- k >= 0 && board[move[0]][move[1]-k]  == c){
					sameSymbol++;
					k++;
				}
				
				
				//consider value at i - k later to see if it's blocked or not
				 l = 1;
				while (move[1] + l <= 14 && board[move[0]][move[1]+l] == c){
					sameSymbol++;
					l++;
				}
                if (sameSymbol >= 5){
					if (needMax) computerPattern[5]++;
					else playerPattern[5]++;
				}else if (sameSymbol == 4 && (board[move[0]][move[1]-k] == 0 || board[move[0]][move[1]+l] == 0)){ 				
					//cout << "here" << endl;
                    if (needMax) computerPattern[4]++;
					else playerPattern[4]++;
				}else if (sameSymbol == 3 && (board[move[0]][move[1]-k] == 0 || board[move[0]][move[1]+l] == 0)){
					if (needMax) computerPattern[3]++;
					else playerPattern[3]++;
				}else if (sameSymbol == 3 && (board[move[0]][move[1]-k] == 0 || board[move[0]][move[1]+l] == 0)){
					if (needMax) computerPattern[2]++;
					else playerPattern[2]++;
				}else if (sameSymbol == 2 && (board[move[0]][move[1]-k] == 0 || board[move[0]][move[1]+l] == 0)){
					if (needMax) computerPattern[1]++;
					else playerPattern[1]++;
				}


                //-------------------------------------------------------------------------------
				sameSymbol = 1; // count same symbols in diagonals 1
				k = 1;
                while (move[1]- k >= 0 && board[move[0]-k][move[1]-k]  == c){
					sameSymbol++;
					k++;
				}
				
				
				//consider value at i - k later to see if it's blocked or not
				 l = 1;
				while (move[1] + l <= 14 && board[move[0]+l][move[1]+l] == c){
					sameSymbol++;
					l++;
				}
                if (sameSymbol >= 5){
					if (needMax) computerPattern[5]++;
					else playerPattern[5]++;
				}else if (sameSymbol == 4 && (board[move[0]-k][move[1]-k] == 0 || board[move[0]+l][move[1]+l] == 0)){ 				
					//cout << "here" << endl;
                    if (needMax) computerPattern[4]++;
					else playerPattern[4]++;
				}else if (sameSymbol == 3 && (board[move[0]-k][move[1]-k] == 0 || board[move[0]+l][move[1]+l] == 0)){
					if (needMax) computerPattern[3]++;
					else playerPattern[3]++;
				}else if (sameSymbol == 3 && (board[move[0]-k][move[1]-k] == 0 || board[move[0]+l][move[1]+l] == 0)){
					if (needMax) computerPattern[2]++;
					else playerPattern[2]++;
				}else if (sameSymbol == 2 && (board[move[0]-k][move[1]-k] == 0 || board[move[0]+l][move[1]+l] == 0)){
					if (needMax) computerPattern[1]++;
					else playerPattern[1]++;
				}

                                //-------------------------------------------------------------------------------
				sameSymbol = 1; // count same symbols in diagonals 2
				k = 1;
                while (move[1]- k >= 0 && board[move[0]-k][move[1]+k]  == c){
					sameSymbol++;
					k++;
				}
				
				
				//consider value at i - k later to see if it's blocked or not
				 l = 1;
				while (move[1] + l <= 14 && board[move[0]+l][move[1]-l] == c){
					sameSymbol++;
					l++;
				}
                if (sameSymbol >= 5){
					if (needMax) computerPattern[5]++;
					else playerPattern[5]++;
				}else if (sameSymbol == 4 && (board[move[0]-k][move[1]+k] == 0 || board[move[0]+l][move[1]-l] == 0)){ 				
					//cout << "here" << endl;
                    if (needMax) computerPattern[4]++;
					else playerPattern[4]++;
				}else if (sameSymbol == 3 && (board[move[0]-k][move[1]+k] == 0 || board[move[0]+l][move[1]-l] == 0)){
					if (needMax) computerPattern[3]++;
					else playerPattern[3]++;
				}else if (sameSymbol == 3 && (board[move[0]-k][move[1]+k] == 0 || board[move[0]+l][move[1]-l] == 0)){
					if (needMax) computerPattern[2]++;
					else playerPattern[2]++;
				}else if (sameSymbol == 2 && (board[move[0]-k][move[1]+k] == 0 || board[move[0]+l][move[1]-l] == 0)){
					if (needMax) computerPattern[1]++;
					else playerPattern[1]++;
				}

    }

    if (computerPattern[5] > 0) {
        terminal = true;
        return 1000000000;
    }
	if (playerPattern[5] > 0) {
        terminal = true;
        return -1000000000;
    } 
	int x = 1;
	score += computerPattern[1];
	score -= playerPattern[1]*5;
	for (int i = 2 ; i < 5 ; i++){
		//cout <<computerPattern[i] << " : "<<playerPattern[i]<<endl;
		x *= 100;
        //cout << "i: " << i << endl;
        //cout << "Computer Pattern[i]: " << computerPattern[i] << endl;
        //cout << "Player Pattern[i]: " << playerPattern[i] << endl;

		score += computerPattern[i] * x;
		score -= playerPattern[i] * x * 10;
	}
    //cout << "Score: " << score << endl << endl;
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

#include "boardHandlers.h"
//handles the boards by getting and making the moves

/**
 * Makes a move on the x-y coords of a board
 * @param board board to edit
 * @param x x coordinate of move (origin in bottom left)
 * @param y y coordinate of move (origin in bottom left)
 * @param playerTurn if this is our move, playerTurn = 1. Incoming move playerTurn = 2
 * */
void makeMoveOnBoard(std::array<std::array<int, 15>, 15> &board, int x, int y, int playerTurn){
    board[x][y] = playerTurn;
}

/**
 * Translator function in between game coordinates (e.g. A1) into ours (14, 0)
 * @param inRow the row number coming in
 * @param inCol the character (A-O) of the incoming col
 * @param outRow pointer to an int to be used as x val later
 * @param outCol pointer to an int to be used as y cal later
 * */
void translateMoveToCoords(std::string myStr,  int* outRow, int* outCol) {
    //moveRow maps '1'-'15' -> 0-14
    //moveCol maps 'A'->'O' or 'a'->'o' -> 0-14 
    char c = myStr[0];
    //check if it is a lowercase letter. if so, convert to upper
    if ((int) c > 80) {
        c = (char) ((int)c - 32);
    }
    if (myStr.length() == 3) {
        //one character row #
        *outRow = ((int)myStr[2]-48) - 1;
        std::cout << myStr[2] << std::endl;
    }
    else if (myStr.length() == 4) {
        //two character row #. Adding 9 because we are 0 indexed
        //(myStr[2-3] = '10'-'15', we only need last char, then add 9)
        *outRow = (int)(myStr[3]-48) + 9;
    }
    else {
        std::cout << "ERROR. Move String incorrecly parsed" << std::endl;
    }
    *outCol = ((int) c) - 65; //A is Ascii 65
}

/**
 * Translator function for spitting out a string of characters into the file 
 * (Given out chosen move)
 * @param moveRow
 * @param moveCol
 * @param strOut pointer to character array (at least 5 from the end) to put the move into
 * */
void translateCoordsIntoMove(int moveRow, int moveCol, char* strOut) {
    //moveRow maps 0-14 -> '1'-'15'
    //moveCol maps 0-14 -> 'A'->'O'
    int tempOutRow = moveRow;
    char* p;
    p = strOut;
    //first char
    *p= (char) (moveCol+65);
    *p++;
    *p = ' ';
    p++;
    //now the tougher part
    if (tempOutRow < 9) {
        //output = 1-9 (< 9 because 9 maps to 10 with zero indexing)
        *p = (char) tempOutRow+49;
        *(p+1) = '\0';
    }
    else {
        //output 10-15
        *p = '1';
        *(p+1) = (char)((tempOutRow-9)+48);
        *(p+2) = '\0'; 
    }
}

/**
 *  Gets a list of board states given the current board, and turn
 *  @param board
 *  @param turn who's turn it's about to be
 *  @return arrayOfBoards a deque of length 0 - 255 with each being a 15 by 15 array
 *  */
std::vector<std::array<int, 2>>  getListOfMoves(std::array<std::array<int, 15>, 15> board, int turn, std::deque<std::array<std::array<int, 15>, 15>> *boardList, std::vector<std::array<int, 2>> previousMoves){
    std::vector<std::array<int, 2>> correspondingMoves;
    for(std::array<int, 2> prevMove : previousMoves){
        //one possible fix- board stores possible moves, we only add new ones
        for(std::array<int, 2> neighbor : getNeighborsOf8(prevMove[0], prevMove[1])){
            if (board[neighbor[0]][neighbor[1]] == 0) {
                std::array<int, 2> move = {neighbor[0],neighbor[1]};
                if (!checkInPrevMoves(correspondingMoves, move)) {
                    correspondingMoves.push_back(move);
                    std::array<std::array<int, 15>, 15> newBoard {};
                    std::copy(&board[0][0], &board[0][0]+15*15, &newBoard[0][0]);
                    newBoard[move[0]][move[1]] = turn;
                    boardList->push_back(newBoard);
                }
                
            }
        }
    }
    return correspondingMoves;
}

bool checkInPrevMoves(const std::vector<std::array<int, 2>> &previousMoves, const  std::array<int, 2> &move) {
    for (int i = 0; i < previousMoves.size(); i ++) {
        if (move[0] == previousMoves[i][0] && move[1] == previousMoves[i][1]) {
            return true;
        }
    }
    return false;
}

/**
 *  Gets the indexes of the neighbors
 *  @return the indexes of neighbors
 *  */
std::vector<std::array<int, 2>> getNeighborsOf8(int x, int y){
    std::vector<std::array<int, 2>> neighbors;
    std::array<int, 2> index;

    for(int i = -1; i <= 1; i++){
        if(x + i == 15 || x + i == -1){
            continue;
        }
        for(int j = -1; j <= 1; j++){
            if(y + j == 15 || y + j == -1){
                continue;
            }
            if(!(i == 0 && j == 0)){
                index = { x + i, y + j};
                neighbors.push_back(index);
            }
        }
    }

    return neighbors;
}
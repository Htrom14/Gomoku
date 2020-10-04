#include "boardHandlers.h"
//handles the boards by getting and making the moves

/**
 * Makes a move on the x-y coords of a board
 * @param board board to edit
 * @param x x coordinate of move (origin in bottom left)
 * @param y y coordinate of move (origin in bottom left)
 * @param playerTurn if this is our move, playerTurn = 1. Incoming move playerTurn = 2
 * */
void makeMoveOnBoard(int board[15][15], int x, int y, int playerTurn) {
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
    char c = myStr[0];
    if (myStr.length() == 3) {
        //one character row #
        *outRow = ((int)myStr[2]-48) - 1;
        std::cout << myStr[2] << std::endl;
    }
    else if (myStr.length() == 4) {
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
    int tempOutRow = moveRow;
    char* p;
    p = strOut;
    //first char
    *p= (char) (moveCol+65);
    *p++;
    *p = ' ';
    p++;
    //now the tougher part
    if (tempOutRow < 10) {
        *p = (char) tempOutRow+48;
        *(p+1) = '\0';
    }
    else {
        *p = '1';
        *(p+1) = (char)((tempOutRow-10)+48);
        *(p+2) = '\0'; 
    }
}

/**
 *  Gets a list of board states given the current board, and turn
 *  @param board
 *  @param turn who's turn it's about to be
 *  @return arrayOfBoards a deque of length 0 - 255 with each being a 15 by 15 array
 *  */
void getListOfMoves(std::array<std::array<int, 15>, 15> board, int turn, std::deque<std::array<std::array<int, 15>, 15>> *boardList){
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            if (board[i][j] == 0) {
                std::array<std::array<int, 15>, 15> newBoard {};
                std::copy(&board[0][0], &board[0][0]+15*15, &newBoard[0][0]);
                newBoard[i][j] = turn;
                boardList->push_front(newBoard);
            }
        }
    }
}
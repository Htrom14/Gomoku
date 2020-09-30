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
        *outRow = 15 - ((int)myStr[2]-48);
        std::cout << myStr[2] << std::endl;
    }
    else if (myStr.length() == 4) {
        *outRow = 15 - (int)(myStr[3]-48);
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
    int tempOutRow = 15 - moveRow;
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
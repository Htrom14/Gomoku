#include "boardHandlers.h"
//handles the boards by getting and making the moves

/**
 * Makes a move on the x-y coords of a board
 * @param board board to edit
 * @param x x coordinate of move (origin in bottom left)
 * @param y y coordinate of move (origin in bottom left)
 * @param playerTurn if this is our move, playerTurn = 1. Incoming move playerTurn = 2
 * */
void makeMoveOnBoard(int** board, int x, int y, int playerTurn) {
    *((*(board+x))+y) = playerTurn;
}

/**
 * Translator function in between game coordinates (e.g. A1) into ours (14, 0)
 * @param inRow the row number coming in
 * @param inCol the character (A-O) of the incoming col
 * @param outRow pointer to an int to be used as x val later
 * @param outCol pointer to an int to be used as y cal later
 * */
void translateMoveToCoords(int inRow, char inCol, int* outRow, int* outCol) {
    *outRow = 15 - inRow;
    *outCol = ((int) inCol) - 65; //A is Ascii 65
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
        *p = (char) tempOutRow+30;
        *(p+1) = '\0';
    }
    else {
        *p = '1';
        *(p+1) = (char)((tempOutRow-10)+30);
        *(p+2) = '\0'; 
    }
}
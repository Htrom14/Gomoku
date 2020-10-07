#include<iostream> 
#include <stdlib.h>
#include <FileHandler.h>
#include <chrono>
#include <thread>
#include <string>
#include <iostream>
#include <fstream>
#include <string.h>
#include "boardHandlers.h"
#include "Main.h"
#include "Node.h"


using namespace std;


FileHandler * fileHandler;
std::array<std::array<int, 15>, 15> board{};
std::vector<std::array<int, 2>> previousMoves;
char writeOut[10] = {'I', 'r', 'o', 'h', ' ', '\0'};

int madeMoveRow;
int madeMoveCol;

int main(int argc, char *argv[])
{
    madeMoveRow = 0;
    madeMoveCol = 0;
    bool firstPass = true;
    while(true){
	if(fileHandler->listenForTurn()){
        cout << "My turn" << endl;
        //TODO: Start timer for iterative deepening search
        if(fileHandler->checkGameOver()){
            break;
        }
        std::string lastMove = fileHandler->getLastMove();
        if (firstPass) {
            //special code for first time through, initializing the board
            if (lastMove.length() < 2) {
                makeMoveOnBoard(board, 7, 7, 1);
                std::array<int, 2> previousMove = {7,7};
                previousMoves.push_back(previousMove);
                translateCoordsIntoMove(7, 7, &writeOut[5]);
                ofstream myfile;
                myfile.open("move_file");
                myfile << writeOut;
                myfile.close();
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                continue;
            }
            else {
                //decide if we want to flip the other persons stone, if so do it
            }
        }
        
        cout << lastMove << endl;
        translateMoveToCoords(lastMove, &madeMoveRow,&madeMoveCol);
        cout << "Opponent MADE MOVE: " << madeMoveRow << " " << madeMoveCol << endl;
        makeMoveOnBoard(board, madeMoveRow, madeMoveCol, 2);
        Node node = Node(2, board, 0, madeMoveRow, madeMoveCol, previousMoves);
        
        //calculate where we should go
        std::array<int, 2> myInts;
        myInts[0] = 1;
        myInts[1] = 2;
        node.alphaBetaSearch(&myInts);
        
        //update game state and write move to reflect our move
        std::array<int, 2> previousMove = {myInts[0], myInts[1]};
        cout << "IROH MAKES MOVE: " << myInts[0] << " " << myInts[1] << endl;
        makeMoveOnBoard(board, myInts[0], myInts[1], 1);
        previousMoves.push_back(previousMove);
        translateCoordsIntoMove(myInts[0], myInts[1], &writeOut[5]);
        
        //make the move
        ofstream myfile;
        myfile.open("move_file");
        myfile << writeOut;
        myfile.close();
        //node.printBoard();
        
        for(int i = 0; i < 15; i++){
            for(int j = 0; j < 15; j++){
                cout << board[i][j] << " ";
        }
            cout << endl;
        }

        //sleep so the referee actually deletes the .go file
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		}else{
			std::this_thread::sleep_for(std::chrono::milliseconds(50));
		}
       
	}

    return 0;
}
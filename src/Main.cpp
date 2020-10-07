#include<iostream> 
#include <stdlib.h>
#include <FileHandler.h>
#include <chrono>
#include <thread>
#include <string>
#include <iostream>
#include <fstream>
#include <string.h>
#include <thread>
#include "boardHandlers.h"
#include "Main.h"
#include "Node.h"


using namespace std;


FileHandler * fileHandler;
std::array<std::array<int, 15>, 15> board{};
std::vector<std::array<int, 2>> previousMoves;
char writeOut[10] = {'I', 'r', 'o', 'h', ' ', '\0'};
int maxTime = 9000;
int currentTime;

int madeMoveRow;
int madeMoveCol;

int main(int argc, char *argv[])
{
    
    madeMoveRow = 0;
    madeMoveCol = 0;
    bool firstPass = true;
    bool secondPass = false;
    while(true){
	if(fileHandler->listenForTurn()){
        cout << "My turn" << endl;
        currentTime = 0;
        //TODO: Start timer for iterative deepening search
        if(fileHandler->checkGameOver()){
            break;
        }
        std::string lastMove = fileHandler->getLastMove();
        if (firstPass) {
            secondPass = true;
            firstPass = false;
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
                translateMoveToCoords(lastMove, &madeMoveRow,&madeMoveCol);
                if (madeMoveRow > 0 && madeMoveRow < 15 && madeMoveCol > 0 && madeMoveCol < 15) {
                    //flip the piece to ours
                    std::array<int, 2> previousMove = {madeMoveRow,madeMoveCol};
                    previousMoves.push_back(previousMove);
                    translateCoordsIntoMove(madeMoveRow, madeMoveCol, &writeOut[5]);
                    makeMoveOnBoard(board, madeMoveRow, madeMoveCol, 1);
                    ofstream myfile;
                    myfile.open("move_file");
                    myfile << writeOut;
                    myfile.close();
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                    continue;
                }

            }
        }
        cout << lastMove << endl;
        translateMoveToCoords(lastMove, &madeMoveRow,&madeMoveCol);
        if (secondPass) {
            secondPass = false;
            if (madeMoveRow == 7 && madeMoveCol == 7) {
                previousMoves.clear();
            }
        }

        
        cout << "Opponent MADE MOVE: " << madeMoveRow << " " << madeMoveCol << endl;
        makeMoveOnBoard(board, madeMoveRow, madeMoveCol, 2);
        Node node = Node(2, board, 0, madeMoveRow, madeMoveCol, previousMoves);
        
        //calculate where we should go
        std::array<int, 2> myInts;
        myInts[0] = 1;
        myInts[1] = 2;
        
        //perform the search and place result in myInts
        node.alphaBetaSearch(&myInts);
        
        //update game state and write move to reflect our move
        std::array<int, 2> previousMove = {myInts[0], myInts[1]};
        cout << "IROH MAKES MOVE: " << myInts[0] << " " << myInts[1] << endl;
        makeMoveOnBoard(board, myInts[0], myInts[1], 1);
        previousMoves.push_back(previousMove);
        translateCoordsIntoMove(myInts[0], myInts[1], &writeOut[5]);
        
        //make the move into the text file
        ofstream myfile;
        myfile.open("move_file");
        myfile << writeOut;
        myfile.close();
        
        for(int i = 0; i < 15; i++){
            for(int j = 0; j < 15; j++){
                cout << board[i][j] << " ";
        }
            cout << endl;
        }

        //sleep so the referee actually deletes the .go file in time
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		}else{
			std::this_thread::sleep_for(std::chrono::milliseconds(50));
		}
       
	}

    return 0;
}
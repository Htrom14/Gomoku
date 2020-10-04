#include<iostream> 
#include <stdlib.h>
#include <FileHandler.h>
#include <chrono>
#include <thread>
#include <string>
#include "boardHandlers.h"
#include "Main.h"
#include "Node.h"


using namespace std;


FileHandler * fileHandler;
std::array<std::array<int, 15>, 15> board{};
int madeMoveRow;
int madeMoveCol;

int main(int argc, char *argv[])
{
    // madeMoveRow = 0;
    // madeMoveCol = 0;
    // while(true){
	// 	if(fileHandler->listenForTurn()){
    //         // cout << "My turn" << endl;
    //         if(fileHandler->checkGameOver()){
    //             break;
    //         }
    //         // getMove()
    //         std::string lastMove = fileHandler->getLastMove();
    //         cout << lastMove << endl;
    //         translateMoveToCoords(lastMove, &madeMoveRow,& madeMoveCol);
    //         cout << board[14][0] << endl;
    //         cout<< "MoveRow: " << madeMoveRow << endl;
    //         cout << "MoveCol: " << madeMoveCol << endl;
    //         makeMoveOnBoard(board, madeMoveRow, madeMoveCol, 2);
    //         cout << board[14][0] << endl;
    //         Node node = Node(2, board, 0);
    //         node.printBoard();

    //         break;
    //         // writeMove()
	// 	}else{
	// 		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	// 	}
       
	// }
    board[0][0] = 1;
    Node node = Node(1, board, 0);

    node.getChildren();

    int counter = 0;
    for(Node child : node.children){
        counter++;
    }

    cout << node.updateMinMax(0, true) << endl;

    cout << counter << endl;
    return 0;
}
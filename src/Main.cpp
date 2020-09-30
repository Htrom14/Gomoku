#include<iostream> 
#include <stdlib.h>
#include <FileHandler.h>
#include <chrono>
#include <thread>
#include <string>
#include "boardHandlers.h"
#include "Main.h"


using namespace std;


FileHandler * fileHandler;
int board[15][15] = {};

int main(int argc, char *argv[])
{
    while(true){
		if(fileHandler->listenForTurn()){
            cout << "My turn" << endl;
            if(fileHandler->checkGameOver()){
                break;
            }
            // getMove()
            std::string lastMove = fileHandler->getLastMove();
            cout << lastMove << endl;
            break;
            // writeMove()
		}else{
			std::this_thread::sleep_for(std::chrono::milliseconds(50));
		}
        
       
	}
    return 0;
}
#include<iostream> 
#include <stdlib.h>
#include <FileHandler.h>
#include <chrono>
#include <thread>
#include <string>


using namespace std;


FileHandler * fileHandler;

bool foundFile;
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
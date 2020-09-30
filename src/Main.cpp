#include<iostream> 
#include <stdlib.h>
#include <FileHandler.h>

using namespace std;

FileHandler * fileHandler;

bool foundFile;
int main(int argc, char *argv[])
{
    while(true){
        // listenForTurn()
		foundFile = fileHandler->listenForTurn();

		if(foundFile){
			cout << "We found it" << endl;
		}else{
			cout << "We didn't find it" << endl;
		}
        // getMove()
        // writeMove()
        // checkGameOver()
	}
    return 0;
}
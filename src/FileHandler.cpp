#include <sys/stat.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <fstream>
#include <FileHandler.h>

using namespace std; 

const std::string TEAM_NAME = "Iroh";
const std::string GAME_OVER_PATH = "end_game";
const std::string MOVE_PATH = "move_file";


/***
 *  Checks to see if team name.go file exists.
 *  @return true if file exists, else returns false
*/
bool FileHandler::listenForTurn() 
{ 
    std::ifstream infile(TEAM_NAME + ".go");
    return infile.good();
}

/***
 *  Checks to see if end_game file exists.
 *  @return true if file exists, else returns false
*/
bool FileHandler::checkGameOver() 
{ 
    std::ifstream infile(GAME_OVER_PATH);
    return infile.good();
}

/***
 *  Observers move list and gets the last played move
 *  @return the last move played by the other player
*/
std::string FileHandler::getLastMove() 
{ 
    std::string line;
    std::ifstream infile(MOVE_PATH);

    if(infile.good()){
        getline(infile, line);
        bool record = false;
        string move = "";
        for (auto x : line) 
        { 
            if(record){
                move += x;
            }
            if (x == ' ') 
            { 
                record = true;
            } 
        }  
        return move;
    }
}


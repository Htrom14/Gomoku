#include <sys/stat.h>
#include <unistd.h>
#include <string>
#include <fstream>
#include <FileHandler.h>

using namespace std; 

const std::string TEAM_NAME = "Iroh";

/***
 *  Checks to see if team name file exists.
 *  @return true if file exists, else returns false
*/
bool FileHandler::listenForTurn() 
{ 
    std::ifstream infile(TEAM_NAME + ".go");
    return infile.good();
}

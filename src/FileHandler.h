// FileHandler.h
#ifndef FileHandler_H
#define FileHandler_H

class FileHandler
{
public:
    FileHandler();
    bool listenForTurn();
    bool checkGameOver();
    std::string getLastMove();
};

#endif
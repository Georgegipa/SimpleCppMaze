#pragma once
#include "definitions.h"
#include <vector>
#include <string>

class Board{
private:
    std::vector<std::string> boardVector;
    int boardRows;
    int boardCols;
    std::vector<std::string> fileToBoard(const char *fileName);
    bool isValid(int row, int col);
public:
    Board(Board &other);
    Board(const char *fileName);
    void setBoard(int row, int col, char value);
    char getBoardChar(int row, int col);
    int getBoardRows();
    int getBoardCols();
    void positionToBoard(Position pos, char value);
    void updateOldPosition(Position &oldPos,Position &newPos, char value);
    bool posIsChar(int row, int col, char c);
    bool posIsChar(Position p, char c);
    bool isWall(int row, int col);
    bool isPath(int row, int col);
    bool isPath(Position p);
};

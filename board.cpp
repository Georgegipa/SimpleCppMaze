#include "board.h"
#include <cstring>
#include <fstream>
#include <iostream>
#include <exception>

Board::Board(const char *fileName)
{
    boardVector = fileToBoard(fileName);
    boardRows = boardVector.size();
    boardCols = boardVector[0].size();
}

Board::Board(Board &other)
{
    boardRows = other.boardRows;
    boardCols = other.boardCols;
    boardVector = other.boardVector;
}

//convert the file to a vector
std::vector<std::string> Board::fileToBoard(const char *fileName)
{
    std::string line = fileName; 
    std::ifstream file(line, std::ios::in);
    //check if the file is open
    if (!file.is_open())
    {
        throw std::runtime_error("Unable to open file!");
    }
    std::vector<std::string> lines;
    while (std::getline(file, line))
    {
        lines.push_back(line);
    }
    file.close();
    return lines;
}

char Board::getBoardChar(int row, int col)
{
    return boardVector[row][col];
}

int Board::getBoardRows()
{
    return boardRows;
}

int Board::getBoardCols()
{
    return boardCols;
}

void Board::setBoard(int row, int col, char value)
{
    boardVector[row][col] = value;
}

void Board::positionToBoard(Position pos, char value)
{
    setBoard(pos.first, pos.second, value);
}

//update the board with the new position of an entity
void Board::updateOldPosition(Position &oldPos, Position &newPos, char value)
{
    positionToBoard(oldPos, '.');
    positionToBoard(newPos, value);
}

bool Board::posIsChar(int row, int col, char c)
{
    return (boardVector[row][col] == c);
}

bool Board::posIsChar(Position p, char c)
{
    return posIsChar(p.first, p.second, c);
}

bool Board::isValid(int row, int col)
{
    return (row >= 0 && row < boardRows && col >= 0 && col < boardCols);
}

bool Board::isWall(int row, int col)
{
    return (isValid(row,col) && posIsChar(row, col, '*'));
}

bool Board::isPath(int row, int col)
{
    return (isValid(row,col) && posIsChar(row, col, '.'));
}

bool Board::isPath(Position p)
{
    return isPath(p.first, p.second);
}
#include "entity.h"
#include <vector>
#include "utils.h"

Entity::Entity(char symbol, Color c)
{
    this->symbol = symbol;
    this->color = c;
    entityPos.first = -1;
    entityPos.second = -1;
}

//function that tries to place the entity in a position of the board, as efficiently as possible.
bool Entity::randomizePos(Board &board)
{
    //recreate the map in binary form
    int pathCels = 0;
    std::vector< std::vector<bool> > binaryMap(board.getBoardRows(), std::vector<bool>(board.getBoardCols(), false));
    //true if the position is a path and false if it is
    for (int i = 0; i < board.getBoardRows(); i++)
    {
        for (int j = 0; j < board.getBoardCols(); j++)
        {
            if (board.posIsChar(i, j, '.'))
            {
                //if the position is a path increase the counter
                binaryMap[i][j] = true;
                pathCels++;
            }
        }
    }
    //if there are no path cells return false
    if (pathCels == 0)
        return false;

    //convert the positions to 1d array
    Position *pos = new Position[pathCels];
    int index = 0;
    for (int i = 0; i < board.getBoardRows(); i++)
    {
        for (int j = 0; j < board.getBoardCols(); j++)
        {
            if (binaryMap[i][j])
            {
                pos[index].first = i;
                pos[index].second = j;
                index++;
            }
        }
    }

    //find a random position from the free previous positions array
    entityPos = pos[utils::randNum(0, pathCels - 1)];
    delete[] pos;
    return true;
}

void Entity::setPos(Position p)
{
    this->entityPos = p;
}

Position Entity::getPos()
{
    return this->entityPos;
}

char Entity::getSymbol()
{
    return this->symbol;
}

Color Entity::getColor()
{
    return this->color;
}
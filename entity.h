#pragma once
#include "definitions.h"
#include "board.h"

class Entity
{
private:
    Position entityPos;
    Color color;
    char symbol;
public:
    Entity(char symbol, Color c);
    bool randomizePos(Board &board);
    void setPos(Position p);
    Position getPos();
    char getSymbol();
    Color getColor();
};
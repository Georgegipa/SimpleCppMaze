#pragma once
#include <cstring>
#include "definitions.h"
#include "board.h"
#include "entity.h"

class Player : public Entity
{
private:
    char *name;

public:
    Player(const char *name, char symbol, Color c);
    virtual ~Player();
    char *getName();
    virtual bool updatePath(Board &board, Position dest);
    virtual bool isComputerControlled();
    virtual bool nextMove(Board &board, char symbol, Control c = NONE) = 0;
};
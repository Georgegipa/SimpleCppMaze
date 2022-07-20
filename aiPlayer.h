#pragma once
#include <vector>
#include "definitions.h"
#include "board.h"
#include "player.h"

class AiPlayer : public Player
{
private:
    typedef struct PosBFS_t
    {
        Position pos;
        int index;
    } PosBFS;
    int pathI;
    std::vector<Position> path;
public:
    AiPlayer(const char *name, char symbol, Color c);
    ~AiPlayer();
    bool isComputerControlled();
    bool updatePath(Board &board, Position dest);
    bool nextMove(Board &board, char symbol, Control c = NONE) ;
};
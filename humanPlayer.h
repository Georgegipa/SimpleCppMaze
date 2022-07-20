#pragma once
#include "definitions.h"
#include "player.h"

class HumanPlayer : public Player
{
private:
    bool validMove(Board &board, Position &pos, char goal);
public:
    HumanPlayer(const char *name, char symbol, Color c);
    ~HumanPlayer();
    bool nextMove(Board &board, char symbol, Control c = NONE);
};
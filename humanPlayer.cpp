#include "humanPlayer.h"

HumanPlayer::HumanPlayer(const char *name, char symbol, Color c) : Player(name, symbol, c) {}

HumanPlayer::~HumanPlayer() {}

bool HumanPlayer::validMove(Board &board, Position &pos, char goal)
{
    //check if the move is valid
    if (board.isPath(pos) || board.posIsChar(pos, goal))
    {
        //change the player position in the board
        Position temp = getPos();
        board.updateOldPosition(temp, pos,getSymbol());
        setPos(pos);
        return true;
    }
    else
    {
        return false;
    }
}

//1 successfull move or 0 if the move was not successful
bool HumanPlayer::nextMove(Board &board, char symbol, Control c)
{
    Position pos = getPos();
    switch (c)
    {
    case UP:
        pos.first--;
        break;
    case DOWN:
        pos.first++;
        break;
    case LEFT:
        pos.second--;
        break;
    case RIGHT:
        pos.second++;
        break;
    case SPACE:
        return 1;
    default:
        return 0;
    }

    //ελεγχος για επιτυχή κίνηση
    if (validMove(board, pos, symbol))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
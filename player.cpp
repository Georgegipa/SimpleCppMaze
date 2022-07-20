#include "player.h"

Player::Player(const char *name, char symbol, Color c) : Entity(symbol, c)
{
    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);

}

Player::~Player()
{
    delete[] name;
}

char *Player::getName()
{
    return name;
}
//only the pc player does override the following functions
bool Player::updatePath(Board &board, Position dest)
{
    return false;
}

bool Player::isComputerControlled()
{
    return false;
}
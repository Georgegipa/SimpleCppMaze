#pragma once
#include <iostream>
#include <curses.h>
#include <locale.h>
#include "definitions.h"
#include "player.h"
#include "entity.h"
#include "board.h"

class Game
{
private:
    WINDOW *mainwin;
    Board *gameBoard;
    Entity *magicCrystal;
    Player **players;

    void printVictoryMessage(int playerID);
    void printLab();
    void startTerminal();
    void randomizeCrystal();
    Control inputToControl(int ch);
public:
    Game(Board board,Player **&players);
    ~Game();
    void gameLoop();
    void generateRandomPositions();
    
};
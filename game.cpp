#include "game.h"
#include "customtext.h"
#include "utils.h"

// pass the board and players by reference
Game::Game(Board board, Player **&players)
{
    gameBoard = new Board(board);
    this->players = players;
    magicCrystal = new Entity('x', CYAN);
    startTerminal();
}

Game::~Game()
{
    delete magicCrystal;
    delete gameBoard;
    delwin(mainwin);
    endwin();
}

void Game::startTerminal()
{
    // start ncurses
    setlocale(LC_ALL, ""); // unicode support
    if ((mainwin = initscr()) == NULL)
        throw std::runtime_error("Unable to start ncurses!");

    curs_set(0); // turn off cursor
    start_color();
    keypad(mainwin, TRUE);
}

void Game::generateRandomPositions()
{
    // place the magic crystal in a random position
    if (magicCrystal->randomizePos(*gameBoard))
    {
        gameBoard->positionToBoard(magicCrystal->getPos(), magicCrystal->getSymbol());
    }
    // place the players in random positions
    for (int i = 0; i < PLAYERS; i++)
    {
        if (players[i]->randomizePos(*gameBoard))
        {
            gameBoard->positionToBoard(players[i]->getPos(), players[i]->getSymbol());
        }
    }
}

void Game::printLab()
{
    init_pair(1, magicCrystal->getColor(), COLOR_BLACK);
    for (int i = 0; i < PLAYERS; i++)
    {
        init_pair(i + 2, players[i]->getColor(), COLOR_BLACK);
    }
    for (int i = 0; i < gameBoard->getBoardRows(); i++)
    {
        for (int j = 0; j < gameBoard->getBoardCols(); j++)
        {
            if (gameBoard->isWall(i, j) || gameBoard->isPath(i, j))
            {
                wattron(mainwin, COLOR_PAIR(0)); // 0 is white
                mvwprintw(mainwin, i + 1, j, "%c", gameBoard->getBoardChar(i, j));
                wattroff(mainwin, COLOR_PAIR(0));
            }
            // change color of the crystal
            else if (magicCrystal->getSymbol() == gameBoard->getBoardChar(i, j))
            {
                wattron(mainwin, COLOR_PAIR(1));
                mvwprintw(mainwin, i + 1, j, "%c", gameBoard->getBoardChar(i, j));
                wattroff(mainwin, COLOR_PAIR(1));
            }
            else // change color for every player based on their selected color
            {
                for (int z = 0; z < PLAYERS; z++)
                {
                    if (players[z]->getSymbol() == gameBoard->getBoardChar(i, j))
                    {
                        wattron(mainwin, COLOR_PAIR(z + 2));
                        mvwprintw(mainwin, i + 1, j, "%c", gameBoard->getBoardChar(i, j));
                        wattroff(mainwin, COLOR_PAIR(z + 2));
                    }
                }
            }
        }
    }
    printw("\n");
    refresh();
}

void Game::randomizeCrystal()
{
    // change the old position of the crystal to a path
    Position old = magicCrystal->getPos();
    gameBoard->positionToBoard(old, '.');
    // place the crystal in a random position
    if (magicCrystal->randomizePos(*gameBoard))
    {
        gameBoard->positionToBoard(magicCrystal->getPos(), magicCrystal->getSymbol());
    }
    // update the players' paths
    for (int i = 0; i < PLAYERS; i++)
    {
        if (players[i]->isComputerControlled())
        {
            players[i]->updatePath(*gameBoard, magicCrystal->getPos());
        }
    }
    mvwprintw(mainwin, 0, 0, "The evil wizard has changed the position of the crystal!");
    refresh();
}

Control Game::inputToControl(int ch)
{
    switch (ch)
    {
    case KEY_UP:
        return UP;
    case KEY_DOWN:
        return DOWN;
    case KEY_LEFT:
        return LEFT;
    case KEY_RIGHT:
        return RIGHT;
    case ' ':
        return SPACE;
    default:
        return NONE;
    }
}

void Game::gameLoop()
{
    bool gameOver = false;
    int winner;

    for (int i = 0; i < PLAYERS; i++)
    {
        if (players[i]->isComputerControlled())
        {
            players[i]->updatePath(*gameBoard, magicCrystal->getPos());
        }
    }
    while (!gameOver)
    {
        int rand = utils::randNum(1, 100);
        if (rand <= PROPABILITY)
            randomizeCrystal();
        printLab();
        for (int i = 0; i < PLAYERS; i++)
        {
            if (!players[i]->isComputerControlled())
            { // if the player is human, wait for input
                while (1)
                {
                    bool playerMoved;
                    int ch = wgetch(mainwin);
                    // the player pressed the ESC key -> exit the game
                    if (ch == 27)
                        return;

                    playerMoved = players[i]->nextMove(*gameBoard, magicCrystal->getSymbol(), inputToControl(ch));

                    if (playerMoved == 0)
                    {
                        mvwprintw(mainwin, 0, 0, "Invalid move!");
                    }
                    else if (playerMoved == 1)
                    { // successful move
                        move(0, 0);
                        clrtoeol();
                        break;
                    }
                    refresh();
                }
            }
            else
            {
                // if the player is computer, move the player to the next position of the path
                players[i]->nextMove(*gameBoard, magicCrystal->getSymbol());
            }
        }

        //check if any player is in the position of the magic crystal
        for (int i = 0; i < PLAYERS; i++)
        {
            // if the player is in the position of the magic crystal, he wins
            if (magicCrystal->getPos() == players[i]->getPos())
            {
                gameOver = true;
                winner = i;
                break;
            }
        }
    }
    printVictoryMessage(winner);
}

void Game::printVictoryMessage(int playerID)
{
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, players[playerID]->getColor(), COLOR_BLACK);
    clear();
    wattron(mainwin, COLOR_PAIR(3));
    mvwprintw(mainwin, 0, 0, "Winner:%s", players[playerID]->getName());
    wattroff(mainwin, COLOR_PAIR(3));

    if (players[playerID]->isComputerControlled() == false)
    { //winner player is human
        wattron(mainwin, COLOR_PAIR(1));
        mvwprintw(mainwin, 1, 0, "%s", winMessage);
        wattroff(mainwin, COLOR_PAIR(1));
    }
    else
    { //winner player is computer
        wattron(mainwin, COLOR_PAIR(2));
        mvwprintw(mainwin, 1, 0, "%s", loseMessage);
        wattroff(mainwin, COLOR_PAIR(2));
    }

    refresh();
    getchar(); //wait for the player to press a key to exit the game
}
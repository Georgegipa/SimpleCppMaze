#include <iostream>
#include "definitions.h"
#include "board.h"
#include "player.h"
#include "aiPlayer.h"
#include "humanPlayer.h"
#include "game.h"

int main(int argc, char const *argv[])
{
    if (argc == 2)
    {
        try
        {
            // create the board from the file given as argument
            Board board(argv[1]);
            //an array of pointers to players
            Player **players = new Player *[PLAYERS];
            players[0] = new HumanPlayer("Harry Potter", 'H', YELLOW);
            players[1] = new AiPlayer("Lucius Malfoy", 'L', GREEN);
            players[2] = new AiPlayer("Draco Malfoy", 'D', RED);
            players[3] = new AiPlayer("Severus Snape", 'S', BLUE);
            players[4] = new AiPlayer("Voldemort", 'V', MAGENTA);

            Game game(board, players);
            game.generateRandomPositions();
            game.gameLoop();
            for (int i = 0; i < PLAYERS; i++)
            {
                delete players[i];
            }
            delete[] players;
        }
        catch (std::runtime_error &e)
        {
            std::cerr << e.what() << std::endl;
        }
    }
    else if (argc == 1)
    {
        std::cerr << "A file is required to start the game!" << std::endl;
        return 1;
    }
    else
    {
        std::cerr << "Only one file can be given to generate the board!" << std::endl;
        return 1;
    }
    return 0;
}
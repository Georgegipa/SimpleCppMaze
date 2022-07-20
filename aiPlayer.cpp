#include "aiPlayer.h"
#include <queue>

AiPlayer::AiPlayer(const char *name, char symbol, Color c) : Player(name, symbol, c) {}

AiPlayer::~AiPlayer(){};

bool AiPlayer::isComputerControlled()
{
    return true;
}

bool AiPlayer::updatePath(Board &board, Position dest)
{
    path.clear();//clear path vector
    Position src = getPos();//save players current position

    std::vector< std::vector<bool> > binaryMap;//recreate the map in binary form

    //load the map in binary form , with true if the position is not a wall and false if it is
    for (int i = 0; i < board.getBoardRows(); i++)
    {
        std::vector<bool> cell;
        for (int j = 0; j < board.getBoardCols(); j++)
        {
            if (!(board.posIsChar(i, j, '*')))
            {
                cell.push_back(true);
            }
            else
            {
                cell.push_back(false);
            }
        }
        binaryMap.push_back(cell);
    }

    std::vector<PosBFS> k;
    std::queue<PosBFS> q;

    int firstNum[] = {-1, 0, 0, 1};
    int secondNum[] = {0, -1, 1, 0};
    if (!binaryMap[src.first][src.second] || !binaryMap[dest.first][dest.second])
        return false;

    //the cells of the array visited will be true if the algorithm has already visited them
    //create the array visited of size mapfirsts x mapseconds with all values false
    std::vector< std::vector<bool> > visited(board.getBoardRows(), std::vector<bool>(board.getBoardCols(), false));

    //the source cell that the player is already visited
    visited[src.first][src.second] = true;
    PosBFS s;
    s.pos = src;
    s.index = -1;
    q.push(s); //put the source cell in the queue

    //find the path using BFS
    while (!q.empty())
    {
        PosBFS pt = q.front();
        Position curr = pt.pos;
        //we arrived to the destination cell
        if (curr.first == dest.first && curr.second == dest.second)
        {
            while (pt.index != -1)
            {
                path.push_back(pt.pos);
                pt = k[pt.index]; //take the parent of the current cell
            }
            pathI = path.size() - 1;
            return true;
        }

        //remove the cell you already visited and passed the neighbors in the queue
        k.push_back(pt);
        q.pop();
        //move to all the neighbors of the current cell
        for (int i = 0; i < 4; i++)
        {
            int row = curr.first + firstNum[i];
            int col = curr.second + secondNum[i];
            //add the cell to the queue if it is not visited and it is not a wall
            if (((row >= 0) && (row < board.getBoardRows()) && (col >= 0) && (col < board.getBoardCols())) && binaryMap[row][col] && !visited[row][col])
            {
                //
                visited[row][col] = true;
                PosBFS newPt = {{row, col}, (int)(k.size() - 1)};
                q.push(newPt);
            }
        }
    }
    return false;
}

bool AiPlayer::nextMove(Board &board, char symbol, Control c)
{
    Position pos = path[pathI];
    //move only if the position is a path or the crystal
    if (board.isPath(pos) || board.posIsChar(pos, symbol))
    {
        //change the position of the player in the board
        Position temp = this->getPos();
        board.updateOldPosition(temp, pos,getSymbol());
        setPos(pos);
        pathI--;
    }
    return true;
}

#include "game.h"

namespace game
{

    bool is_valid(const std::vector<std::vector<int>>& board, int x, int y)
    {
        return (x >= 0 && x < board.size() && y >= 0 && y < board[0].size() && board[x][y] == -1);
    }

    bool solve_knights_tour(std::vector<std::vector<int>>& board, int x, int y, const std::vector<int>& move_x, const std::vector<int>& move_y, int pos)
    {
        if (pos == board.size() * board[0].size())
        {
            return true;
        }

        for (int i = 0; i < 8; i++)
        {
            int next_x = x + move_x[i];
            int next_y = y + move_y[i];

            if (is_valid(board, next_x, next_y))
            {
                board[next_x][next_y] = pos;

                if (solve_knights_tour(board, next_x, next_y, move_x, move_y, pos + 1))
                {
                    return true;
                }

                board[next_x][next_y] = -1; 
            }
        }
        return false;
    }
}
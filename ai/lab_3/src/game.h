#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
                    
namespace game
{
    bool is_valid(const std::vector<std::vector<int>>& board, int x, int y);
    bool solve_knights_tour(std::vector<std::vector<int>>& board, int x, int y, const std::vector<int>& move_x, const std::vector<int>& move_y, int pos);
};

#endif // GAME_H
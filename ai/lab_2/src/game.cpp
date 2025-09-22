#include "game.h"

#include <iostream>
#include <algorithm>

void Game::generate_map(vector<vector<int>>& maze, int size) 
{
    for (int i = 0; i < size; i++) 
    {
        for (int j = 0; j < size; j++) 
        {
            maze[i][j] = rand() % 2;
        }
    }

    maze[0][0] = 7;

    int num_end_positions = (size >= 1 && size <= 3) ? 1 :
                            (size > 3 && size <= 5) ? 2 : 3;

    int positions_placed = 0;

    while (positions_placed < num_end_positions) 
    {
        int x = rand() % size;
        int y = rand() % size;

        if ((x == 0 || x == size - 1 || y == 0 || y == size - 1) && maze[x][y] == 0) 
        {
            maze[x][y] = 9;
            positions_placed++;
        }
    }
}

void Game::print_map(const vector<vector<int>>& maze) 
{
    for (const auto& row : maze) 
    {
        for (int cell : row) 
        {
            cout << cell << " ";
        }
        cout << endl;
    }
}

void Game::dfs(const vector<vector<int>>& maze, int x, int y, vector<pair<int, int>>& currentPath, 
         vector<vector<pair<int, int>>>& allPaths, const pair<int, int>& start, int size, vector<vector<bool>>& visited) 
{
    if (maze[x][y] == 9) 
    {
        allPaths.push_back(currentPath);
        return;
    }

    vector<pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    for (const auto& dir : directions) 
    {
        int new_x = x + dir.first;
        int new_y = y + dir.second;

        if (new_x >= 0 && new_x < size && new_y >= 0 && new_y < size &&
            !visited[new_x][new_y] && (maze[new_x][new_y] == 1 || maze[new_x][new_y] == 9)) 
            {
            visited[new_x][new_y] = true;
            currentPath.push_back({new_x, new_y});

            dfs(maze, new_x, new_y, currentPath, allPaths, start, size, visited);

            currentPath.pop_back();
            visited[new_x][new_y] = false;
        }
    }
}


vector<vector<pair<int, int>>> Game::find_all_paths(const vector<vector<int>>& maze, int size)
{
    vector<vector<pair<int, int>>> allPaths;
    vector<vector<bool>> visited(size, vector<bool>(size, false));
    vector<pair<int, int>> currentPath;

    pair<int, int> start = {0, 0};
    currentPath.push_back(start);
    visited[0][0] = true;

    dfs(maze, 0, 0, currentPath, allPaths, start, size, visited);

    return allPaths;
}

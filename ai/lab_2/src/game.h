#pragma once

#ifndef GAME_H
#define GAME_H

#include <vector>
#include <utility>

using namespace std;

struct Game
{
    static void generate_map(vector<vector<int>>& maze, int size);
    
    static void print_map(const vector<vector<int>>& maze);
    
    static void dfs(const vector<vector<int>>& maze, int x, int y, vector<pair<int, int>>& currentPath, 
             vector<vector<pair<int, int>>>& allPaths, const pair<int, int>& start, int size, vector<vector<bool>>& visited);
    
    static vector<vector<pair<int, int>>> find_all_paths(const vector<vector<int>>& maze, int size);  
};

#endif // GAME_H
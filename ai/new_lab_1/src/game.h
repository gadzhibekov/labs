#pragma once

#define BLACK_KING_PATH "../res/black_king.png"
#define WHITE_KING_PATH "../res/white_king.png"
#define WHITE_ROOK_PATH "../res/white_rook.png"

#include "main_window.h"
#include "ui/field_button.h"

#include <vector>
#include <iostream>
#include <unordered_set>

using namespace std;



// Структура для хранения позиции шахматной фигуры
struct Position 
{
    int x, y;

    bool operator==(const Position& other) const 
    {
        return x == other.x && y == other.y;
    }

    bool operator!=(const Position& other) const 
    {
        return !(*this == other);
    }
};

// Хеш-функция для позиции, чтобы использовать её в unordered_set
namespace std 
{
    template<>
    struct hash<Position> 
    {
        size_t operator()(const Position& pos) const 
        {
            return hash<int>()(pos.x) ^ hash<int>()(pos.y);
        }
    };
}

bool is_valid_position(int x, int y);
void draw_on_map(Pair coords, FBVector map, QString symbol);
void clear();
vector<int> check_check_and_stalemate(int blackKingPosition, int whiteKingPosition, int rook1Position, int rook2Position);




void generate_players(int bk_pos, int wk_pos, int wr1_pos, int wr2_pos);
void generate_players(std::vector<int> positions);
void delete_bk_from_field();
std::vector<int> random_numbers();

#include "game.h"

#include "main_window.h"
#include "player.h"
#include "ui/icon.h"

#include <random>
#include <algorithm>
#include <iostream>

#include <QString>

struct MainWindow;
struct Player;

void generate_players(int bk_pos, int wk_pos, int wr1_pos, int wr2_pos)
{
    Player::players.push_back(Player(PlayerType::BLACK_KING, Icon(BLACK_KING_PATH)));
    Player::players.push_back(Player(PlayerType::WHITE_KING, Icon(WHITE_KING_PATH)));
    Player::players.push_back(Player(PlayerType::WHITE_ROOK, Icon(WHITE_ROOK_PATH)));
    Player::players.push_back(Player(PlayerType::WHITE_ROOK, Icon(WHITE_ROOK_PATH)));

    MainWindow::chess_field_items[bk_pos  - 1]->set_player(Player::players[0]);
    MainWindow::chess_field_items[wk_pos  - 1]->set_player(Player::players[1]);
    MainWindow::chess_field_items[wr1_pos - 1]->set_player(Player::players[2]);
    MainWindow::chess_field_items[wr2_pos - 1]->set_player(Player::players[3]);
}

void generate_players(std::vector<int> positions)
{
    generate_players(positions[0], positions[1], positions[2], positions[3]);
}

void delete_bk_from_field()
{
    for (int i = 0; i < FIELD_SIZE; ++i)
    {
        if (MainWindow::chess_field_items[i]->get_player().get_type() == PlayerType::BLACK_KING)
        {
            MainWindow::chess_field_items[i]->delete_player();
        }
    }
}

std::vector<int> random_numbers()
{
    std::vector<int> numbers(FIELD_SIZE);

    for (int i = 0; i < FIELD_SIZE; ++i)
    {
        numbers[i] = i + 1;
    }

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(numbers.begin(), numbers.end(), g);

    std::vector<int> result(numbers.begin(), numbers.begin() + 4);

    return result;
}


bool is_valid_position(int x, int y) 
{
    return x >= 1 && x <= 8 && y >= 1 && y <= 8;
}

vector<int> check_check_and_stalemate(int blackKingPosition, int whiteKingPosition, int rook1Position, int rook2Position) 
{
    vector<int> results;

    Position blackKing = { (blackKingPosition - 1) % 8 + 1, (blackKingPosition - 1) / 8 + 1 };
    Position whiteKing = { (whiteKingPosition - 1) % 8 + 1, (whiteKingPosition - 1) / 8 + 1 };
    Position rook1 = { (rook1Position - 1) % 8 + 1, (rook1Position - 1) / 8 + 1 };
    Position rook2 = { (rook2Position - 1) % 8 + 1, (rook2Position - 1) / 8 + 1 };
    
    for (int dx = -1; dx <= 1; ++dx) 
    {
        for (int dy = -1; dy <= 1; ++dy) 
        {
            if (dx == 0 && dy == 0) continue;

            Position newPos = { blackKing.x + dx, blackKing.y + dy };

            if (is_valid_position(newPos.x, newPos.y) && newPos != whiteKing) 
            {
                bool underCheck = false;

                if ((rook1.x == newPos.x || rook1.y == newPos.y) && (rook1.x != blackKing.x || rook1.y != blackKing.y)) 
                {
                    underCheck = true;
                }

                if ((rook2.x == newPos.x || rook2.y == newPos.y) && (rook2.x != blackKing.x || rook2.y != blackKing.y)) 
                {
                    underCheck = true;
                }

                if ((abs(whiteKing.x - newPos.x) <= 1 && abs(whiteKing.y - newPos.y) <= 1)) 
                {
                    underCheck = true;
                }

                if (underCheck) 
                {
                    results.push_back(newPos.x * 10 + newPos.y);
                } 
                else 
                {
                    bool isStalemate = true;

                    for (int st_dx = -1; st_dx <= 1; ++st_dx) {
                        for (int st_dy = -1; st_dy <= 1; ++st_dy) 
                        {
                            if (st_dx == 0 && st_dy == 0) continue;

                            Position potentialMove = { newPos.x + st_dx, newPos.y + st_dy };

                            if (is_valid_position(potentialMove.x, potentialMove.y) && potentialMove != whiteKing) 
                            {
                                bool canMove = true;
                                if ((rook1.x == potentialMove.x || rook1.y == potentialMove.y) ||
                                    (rook2.x == potentialMove.x || rook2.y == potentialMove.y) ||
                                    (abs(whiteKing.x - potentialMove.x) <= 1 && abs(whiteKing.y - potentialMove.y) <= 1)) 
                                {
                                    canMove = false;
                                }

                                if (canMove) 
                                {
                                    isStalemate = false;
                                    break;
                                }
                            }
                        }

                        if (!isStalemate)
                        {
                            break;
                        }
                    }

                    if (isStalemate) 
                    {
                        results.push_back(newPos.x * 10 + newPos.y + 100);
                    }
                }
            }
        }
    }
    
    return results;
}


void draw_on_map(Pair coords, FBVector map, QString symbol)
{
    for (int i = 0; i < map.size(); ++i)
    {
        if (coords == map[i]->get_coords() && (!(map[i]->is_active())))
        {
            map[i]->set_text(symbol);
        }
    }
}

void clear()
{
    for (int i = 0; i < MainWindow::chess_field_items.size(); ++i)
    {
        if (!(MainWindow::chess_field_items[i]->is_active()))
        {
            MainWindow::chess_field_items[i]->set_text("");
        }
    }
}
#pragma once

#include "ui/icon.h"

#include <vector>

struct Player;
struct Icon;

typedef std::vector<Player>                 PVector;

enum PlayerType : int
{
    BLACK_KING,
    WHITE_KING,
    WHITE_ROOK  // Ладья
};

struct Player
{
    Player() {};
    Player(int type, Icon icon);
    ~Player() {};

    void            set_location(int        location);
    void            set_type(int            type);
    void            set_icon(Icon           icon);

    int             get_location();
    int             get_type();
    Icon            get_icon();
    
    static PVector  players;

private:
    int             location;
    int             type;
    Icon            icon;
};
#include "player.h"

PVector Player::players;

Player::Player(int type, Icon icon) 
: type(type), icon(icon) {}

int         Player::get_location()                { return this->location; }
int         Player::get_type()                    { return this->type; }
Icon        Player::get_icon()                    { return this->icon; }


void        Player::set_location(int location)     { this->location    = location; }
void        Player::set_type(int type)             { this->type        = type; }
void        Player::set_icon(Icon  icon)           { this->icon        = icon; }
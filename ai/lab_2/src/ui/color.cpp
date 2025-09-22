#include "color.h"

Color::Color(int red, int green, int blue) : red(red), green(green), blue(blue)
{
    ;
}

Color::~Color()
{
    ;
}

std::vector<int> Color::get_rgb()
{
    return std::vector<int>({red, green, blue});
}
#include "color.h"

Color::Color(int red, int green, int blue) : red(red), blue(blue), green(green) {}

bool Color::operator == (const Color& other_color) const
{
    return (this->red == other_color.red && this->blue == other_color.blue && this->green == other_color.green) ? true : false;
}

bool Color::operator != (const Color& other_color) const
{
    return !(*this == other_color);
}
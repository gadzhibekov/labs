#pragma ocne

#ifndef COLOR_H
#define COLOR_H

#include <vector>

struct Color
{
    Color(int red, int green, int blue);
    ~Color();

    std::vector<int>    get_rgb();

private:
    int                 red;
    int                 green;
    int                 blue;
};

#endif // COLOR_H
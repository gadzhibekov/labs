#ifndef COLOR_H
#define COLOR_H

struct Color
{
    Color(int red, int green, int blue);
    ~Color() = default;

    bool operator == (const Color& other_color) const;
    bool operator != (const Color& other_color) const;

    int red;
    int green; 
    int blue;
};

#endif // COLOR_H
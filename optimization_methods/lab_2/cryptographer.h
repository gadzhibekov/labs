#ifndef CRYPTOGRAPHER_H
#define CRYPTOGRAPHER_H

#include <string>
#include <vector>

struct Cryptographer
{
    static std::vector<double> encrypt(const std::string& text);
    static std::string decrypt(const std::vector<double>& encrypted);
    static int key;
};

#endif // CRYPTOGRAPHER_H
#ifndef CRYPTOGRAPHER_H
#define CRYPTOGRAPHER_H

#include <string>

struct Cryptographer
{
    static std::string encrypt(const std::string& data);
    static std::string decrypt(const std::string& data);
    static std::string key;
};

#endif // CRYPTOGRAPHER_H
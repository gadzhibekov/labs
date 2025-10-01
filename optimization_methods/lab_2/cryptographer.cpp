#include "cryptographer.h"

#include <cmath>

int Cryptographer::key = 0;

double math_function(double x, double k) 
{
    return sin(x * k) + cos(x / (k + 1)) + tan(x * 0.1);
}

std::vector<double> Cryptographer::encrypt(const std::string& text) 
{
    std::vector<double> encrypted;
    
    for (size_t i = 0; i < text.length(); ++i) 
    {
        char ch = text[i];
        double position = static_cast<double>(i);
        
        double encryptedValue = static_cast<double>(ch);
        encryptedValue += math_function(position, key) * 10;
        encryptedValue *= (1 + sin(key + position) * 0.5);
        encryptedValue += log(abs(key * position + 1)) * 5;
        
        encrypted.push_back(encryptedValue);
    }
    
    return encrypted;
}

std::string Cryptographer::decrypt(const std::vector<double>& encrypted) 
{
    std::string decrypted;
    
    for (size_t i = 0; i < encrypted.size(); ++i) 
    {
        double encryptedValue = encrypted[i];
        double position = static_cast<double>(i);
        
        encryptedValue -= log(abs(key * position + 1)) * 5;
        encryptedValue /= (1 + sin(key + position) * 0.5);
        encryptedValue -= math_function(position, key) * 10;
        
        char ch = static_cast<char>(round(encryptedValue));
        decrypted += ch;
    }
    
    return decrypted;
}
#include "cryptographer.h"

#include <cmath>
#include <array>
#include <cstdint>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cctype>

std::string Cryptographer::key = "12345678";

static inline uint64_t bytes_to_u64_be(const uint8_t b[8]) 
{
    uint64_t v = 0;

    for (int i = 0; i < 8; ++i) v = (v << 8) | b[i];

    return v;
}

static inline void u64_to_bytes_be(uint64_t v, uint8_t b[8]) 
{
    for (int i = 7; i >= 0; --i) 
    {
        b[i] = static_cast<uint8_t>(v & 0xFF);
        v >>= 8;
    }
}

static inline uint64_t permute(uint64_t input, const int* table, int outBits, int inBits) 
{
    uint64_t out = 0;
    
    for (int i = 0; i < outBits; ++i) 
    {
        int from = table[i];
        int idx = inBits - from;
        uint64_t bit = (input >> idx) & 1ULL;
        out = (out << 1) | bit;
    }
    
    return out;
}

static inline uint32_t rotl28(uint32_t v, int s) 
{
    v &= 0x0FFFFFFF;
    return static_cast<uint32_t>(((v << s) | (v >> (28 - s))) & 0x0FFFFFFF);
}

static inline std::vector<uint8_t> pkcs7_pad(const std::vector<uint8_t>& data, size_t blockSize = 8) 
{
    size_t padLen = blockSize - (data.size() % blockSize);

    if (padLen == 0) padLen = blockSize;
    
    std::vector<uint8_t> out = data;
    out.resize(out.size() + padLen, static_cast<uint8_t>(padLen));
    
    return out;
}

static inline std::vector<uint8_t> pkcs7_unpad(const std::vector<uint8_t>& data, size_t blockSize = 8) 
{
    if (data.empty() || data.size() % blockSize != 0) 
    {
        throw std::runtime_error("Неверный размер данных для PKCS#7 unpad");
    }
    
    uint8_t padLen = data.back();
    
    if (padLen == 0 || padLen > blockSize || padLen > data.size()) 
    {
        throw std::runtime_error("Неверный паддинг");
    }
    
    for (size_t i = 0; i < padLen; ++i) 
    {
        if (data[data.size() - 1 - i] != padLen) 
        {
            throw std::runtime_error("Неверный паддинг");
        }
    }

    return std::vector<uint8_t>(data.begin(), data.end() - padLen);
}

static inline std::string to_hex(const std::vector<uint8_t>& bytes) 
{
    std::ostringstream oss;
    oss << std::hex << std::setfill('0');

    for (uint8_t b : bytes) 
    {
        oss << std::setw(2) << static_cast<int>(b);
    }

    return oss.str();
}

static inline uint8_t from_hex_digit(char c) 
{
    if (c >= '0' && c <= '9') return static_cast<uint8_t>(c - '0');
    if (c >= 'a' && c <= 'f') return static_cast<uint8_t>(c - 'a' + 10);
    if (c >= 'A' && c <= 'F') return static_cast<uint8_t>(c - 'A' + 10);

    throw std::runtime_error("Неверный символ hex");
}

static inline std::vector<uint8_t> from_hex(const std::string& hex) 
{
    if (hex.size() % 2 != 0) throw std::runtime_error("Длина hex должна быть четной");

    std::vector<uint8_t> out;
    out.reserve(hex.size() / 2);
    
    for (size_t i = 0; i < hex.size(); i += 2) 
    {
        uint8_t hi = from_hex_digit(hex[i]);
        uint8_t lo = from_hex_digit(hex[i + 1]);
        
        out.push_back(static_cast<uint8_t>((hi << 4) | lo));
    }
    
    return out;
}

static inline std::array<uint8_t, 8> key_from_string(const std::string& key)
{
    std::array<uint8_t, 8> k{};

    for (size_t i = 0; i < 8 && i < key.size(); ++i) k[i] = static_cast<uint8_t>(key[i]);

    return k;
}

static const int IP[64] = 
{
    58,50,42,34,26,18,10, 2,
    60,52,44,36,28,20,12, 4,
    62,54,46,38,30,22,14, 6,
    64,56,48,40,32,24,16, 8,
    57,49,41,33,25,17, 9, 1,
    59,51,43,35,27,19,11, 3,
    61,53,45,37,29,21,13, 5,
    63,55,47,39,31,23,15, 7
};

static const int FP[64] = 
{
    40, 8,48,16,56,24,64,32,
    39, 7,47,15,55,23,63,31,
    38, 6,46,14,54,22,62,30,
    37, 5,45,13,53,21,61,29,
    36, 4,44,12,52,20,60,28,
    35, 3,43,11,51,19,59,27,
    34, 2,42,10,50,18,58,26,
    33, 1,41, 9,49,17,57,25
};

static const int E[48] = 
{
    32, 1, 2, 3, 4, 5,
     4, 5, 6, 7, 8, 9,
     8, 9,10,11,12,13,
    12,13,14,15,16,17,
    16,17,18,19,20,21,
    20,21,22,23,24,25,
    24,25,26,27,28,29,
    28,29,30,31,32, 1
};

static const int P[32] = 
{
    16, 7,20,21,29,12,28,17,
     1,15,23,26, 5,18,31,10,
     2, 8,24,14,32,27, 3, 9,
    19,13,30, 6,22,11, 4,25
};

static const int PC1[56] = 
{
    57,49,41,33,25,17, 9,
     1,58,50,42,34,26,18,
    10, 2,59,51,43,35,27,
    19,11, 3,60,52,44,36,
    63,55,47,39,31,23,15,
     7,62,54,46,38,30,22,
    14, 6,61,53,45,37,29,
    21,13, 5,28,20,12, 4
};

static const int PC2[48] = 
{
    14,17,11,24, 1, 5,
     3,28,15, 6,21,10,
    23,19,12, 4,26, 8,
    16, 7,27,20,13, 2,
    41,52,31,37,47,55,
    30,40,51,45,33,48,
    44,49,39,56,34,53,
    46,42,50,36,29,32
};

static const int SHIFTS[16] = { 1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1 };

static const uint8_t SBOX[8][4][16] = 
{
    // S1
    {
        {14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
        {0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
        {4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
        {15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}
    },
    // S2
    {
        {15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},
        {3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},
        {0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},
        {13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}
    },
    // S3
    {
        {10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},
        {13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},
        {13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},
        {1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}
    },
    // S4
    {
        {7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},
        {13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},
        {10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},
        {3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}
    },
    // S5
    {
        {2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},
        {14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},
        {4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},
        {11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}
    },
    // S6
    {
        {12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},
        {10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},
        {9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},
        {4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}
    },
    // S7
    {
        {4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},
        {13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},
        {1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},
        {6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}
    },
    // S8
    {
        {13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},
        {1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},
        {7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},
        {2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}
    }
};


struct Subkeys { uint64_t k[16]; };

static Subkeys make_subkeys(const std::array<uint8_t, 8>& key) 
{
    uint64_t key64 = bytes_to_u64_be(key.data());
    uint64_t k56 = permute(key64, PC1, 56, 64);
    uint32_t C = static_cast<uint32_t>((k56 >> 28) & 0x0FFFFFFF);
    uint32_t D = static_cast<uint32_t>( k56        & 0x0FFFFFFF);

    Subkeys sk{};

    for (int round = 0; round < 16; ++round) 
    {
        C = rotl28(C, SHIFTS[round]);
        D = rotl28(D, SHIFTS[round]);
        uint64_t CD = (static_cast<uint64_t>(C) << 28) | D;
        uint64_t k48 = permute(CD, PC2, 48, 56);
        sk.k[round] = k48;
    }

    return sk;
}

static inline uint32_t feistel(uint32_t R, uint64_t k48) 
{
    uint64_t ER = permute(static_cast<uint64_t>(R), E, 48, 32);
    uint64_t X = ER ^ k48;
    uint32_t sOut = 0;

    for (int i = 0; i < 8; ++i) 
    {
        int shift = (7 - i) * 6;
        uint8_t six = static_cast<uint8_t>((X >> shift) & 0x3F);
        int row = ((six & 0x20) >> 4) | (six & 0x01);
        int col = (six >> 1) & 0x0F;
        uint8_t val = SBOX[i][row][col];
        sOut = (sOut << 4) | val;
    }
    
    uint32_t f = static_cast<uint32_t>(permute(static_cast<uint64_t>(sOut), P, 32, 32));
    
    return f;
}

static uint64_t des_block_encrypt(uint64_t block, const Subkeys& sk) 
{
    uint64_t ip = permute(block, IP, 64, 64);
    uint32_t L = static_cast<uint32_t>(ip >> 32);
    uint32_t R = static_cast<uint32_t>(ip & 0xFFFFFFFFu);

    for (int i = 0; i < 16; ++i) 
    {
        uint32_t L_next = R;
        uint32_t R_next = L ^ feistel(R, sk.k[i]);
        L = L_next;
        R = R_next;
    }

    uint64_t preout = (static_cast<uint64_t>(R) << 32) | L;
    uint64_t out = permute(preout, FP, 64, 64);
    
    return out;
}

static uint64_t des_block_decrypt(uint64_t block, const Subkeys& sk) 
{
    uint64_t ip = permute(block, IP, 64, 64);
    uint32_t L = static_cast<uint32_t>(ip >> 32);
    uint32_t R = static_cast<uint32_t>(ip & 0xFFFFFFFFu);

    for (int i = 15; i >= 0; --i) 
    {
        uint32_t L_next = R;
        uint32_t R_next = L ^ feistel(R, sk.k[i]);
        L = L_next;
        R = R_next;
    }

    uint64_t preout = (static_cast<uint64_t>(R) << 32) | L;
    uint64_t out = permute(preout, FP, 64, 64);
    
    return out;
}

static std::vector<uint8_t> encrypt_ecb_raw(const std::vector<uint8_t>& plaintext,
                                            const std::array<uint8_t, 8>& key) 
{
    Subkeys sk = make_subkeys(key);
    std::vector<uint8_t> padded = pkcs7_pad(plaintext, 8);
    std::vector<uint8_t> out(padded.size());

    for (size_t i = 0; i < padded.size(); i += 8) 
    {
        uint64_t block = bytes_to_u64_be(&padded[i]);
        uint64_t enc = des_block_encrypt(block, sk);
        u64_to_bytes_be(enc, &out[i]);
    }

    return out;
}

static std::vector<uint8_t> decrypt_ecb_raw(const std::vector<uint8_t>& ciphertext,
                                            const std::array<uint8_t, 8>& key) 
{
    if (ciphertext.size() % 8 != 0) 
    {
        throw std::runtime_error("Длина шифртекста должна быть кратна 8 байтам (DES)");
    }

    Subkeys sk = make_subkeys(key);
    std::vector<uint8_t> tmp(ciphertext.size());
    
    for (size_t i = 0; i < ciphertext.size(); i += 8) 
    {
        uint64_t block = bytes_to_u64_be(&ciphertext[i]);
        uint64_t dec = des_block_decrypt(block, sk);
        u64_to_bytes_be(dec, &tmp[i]);
    }

    return pkcs7_unpad(tmp, 8);
}

std::string encrypt_to_hex_ecb(const std::string& plaintext, const std::string& keyStr) 
{
    auto key = key_from_string(keyStr);
    std::vector<uint8_t> data(plaintext.begin(), plaintext.end());
    auto enc = encrypt_ecb_raw(data, key);

    return to_hex(enc);
}

std::string decrypt_from_hex_ecb(const std::string& hexCipher, const std::string& keyStr) 
{
    auto key = key_from_string(keyStr);
    auto bytes = from_hex(hexCipher);
    auto dec = decrypt_ecb_raw(bytes, key);

    return std::string(dec.begin(), dec.end());
}

std::string Cryptographer::encrypt(const std::string& data) 
{
    return encrypt_to_hex_ecb(data, key);
}

std::string Cryptographer::decrypt(const std::string& data) 
{
    return decrypt_from_hex_ecb(data, key);
}
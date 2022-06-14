#pragma once
using namespace std;

//#pragma comment(lib, "cryptlib")
#pragma comment(lib, "cryptopp")
#include <iostream>

#include "dll.h"        // dll 사용시 가장 앞에 위치해야함
#include "cryptlib.h"
#include "base64.h"
#include "aes.h"
#include "modes.h"
#include "filters.h"

class AES_Module
{
public:
    AES_Module();
    ~AES_Module();
    string Encrypt(CryptoPP::AES &Encryptor, const string &PlainText){};
    string Decrypt(CryptoPP::AES &Decryptor, const string &EncText){};
};


#include "stdafx.h"
#include "AES_Module.h"


AES_Module::AES_Module()
{
}


AES_Module::~AES_Module()
{
}

string Encrypt(CryptoPP::AES &Encryptor, const string &PlainText)
{
    string EncodedText;

    try
    {
        CryptoPP::StringSource(PlainText, true, 
            new CryptoPP::Base64Encoder(new CryptoPP::StringSink(EncodedText), 
                CryptoPP::BlockPaddingSchemeDef::ZEROS_PADDING
            )
        );
    }
    catch (...)
    {

    }
    return EncodedText;
}


string Decrypt(CryptoPP::AES &Decryptor, const string &EncodedText)
{
    string recoveredText;

    try
    {
        CryptoPP::StringSource(EncodedText, true,
            new CryptoPP::Base64Encoder(new CryptoPP::StringSink(recoveredText),
                CryptoPP::BlockPaddingSchemeDef::ZEROS_PADDING
            )
        );
    }
    catch (...)
    {
    }

    return recoveredText;
}

string CBC_Encrypt(byte *KEY, byte *IV, const string &PlainText)
{
    typename CryptoPP::CBC_Mode<CryptoPP::AES>::Encryption Encryptor(KEY, CryptoPP::AES::DEFAULT_KEYLENGTH, IV);
    return Encrypt(Encryptor, PlainText);
}
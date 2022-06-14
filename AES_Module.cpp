#include "stdafx.h"
#include "AES_Module.h"
// #include "AES_Module.hpp"

/*
CAES_Module::CAES_Module()
{
    OutputDebugString(_T("객체생성\n"));
}


CAES_Module::~CAES_Module()
{
}*/

template <class TyMode>
string Encrypt(TyMode &Encryptor, const string &PlainText)
{
    string EncodedText;
    OutputDebugString(_T("암호화\n"));

    try
    {
        /*
        CryptoPP::StringSource(PlainText, true, 
            new CryptoPP::Base64Encoder(new CryptoPP::StringSink(EncodedText), 
                CryptoPP::BlockPaddingSchemeDef::ZEROS_PADDING
            )
        );*/

        CryptoPP::StringSource(PlainText, TRUE,
            new CryptoPP::StreamTransformationFilter(Encryptor, 
                new CryptoPP::Base64Encoder(new CryptoPP::StringSink(EncodedText), false)
            ));
    }
    catch (...)
    {

    }
    return EncodedText;
}

template <class TyMode>
string Decrypt(TyMode &Decryptor, const string &EncodedText)
{
    string recoveredText;
    OutputDebugString(_T("복호화\n"));

    try
    {
        CryptoPP::StringSource(EncodedText, true,
            new CryptoPP::Base64Decoder(
                new CryptoPP::StreamTransformationFilter(Decryptor,
                    new CryptoPP::StringSink(RecoveredText),
                    CryptoPP::BlockPaddingSchemeDef::ZEROS_PADDING
                )
            )
        );
    }
    catch (...)
    {
    }

    return recoveredText;
}

template <class Ty>
string CBC_Encrypt(byte *KEY, byte *IV, const string &PlainText)
{
    OutputDebugString(_T("버튼 동작1\n"));
    typename CryptoPP::CBC_Mode<Ty>::Encryption Encryptor(KEY, Ty::DEFAULT_KEYLENGTH, IV);
    return Encrypt(Encryptor, PlainText);
}

template <class Ty>
std::string CBC_Decrypt(byte *KEY, byte *IV, const std::string &PlainText)
{
    OutputDebugString(_T("버튼 동작2\n"));
    typename CryptoPP::CBC_Mode<Ty>::Decryption Decryptor(KEY, Ty::DEFAULT_KEYLENGTH, IV);
    return Decrypt(Decryptor, PlainText);
}

template <class Ty>
std::string ECB_Encrypt(byte *KEY, const std::string &PlainText)
{
    typename CryptoPP::ECB_Mode<Ty>::Encryption Encryptor(KEY, Ty::DEFAULT_KEYLENGTH);
    return Encrypt(Encryptor, PlainText);
}


template <class Ty>
std::string ECB_Decrypt(byte *KEY, const std::string &PlainText)
{
    typename CryptoPP::ECB_Mode<Ty>::Decryption Decryptor(KEY, Ty::DEFAULT_KEYLENGTH);
    return Decrypt(Decryptor, PlainText);
}

template <class CryptoType>
void Test()
{
    OutputDebugString(_T("테스트실행\n"));
    const string sText = "Plain Text";
    string sEnc, sDec;

    byte KEY[CryptoType::DEFAULT_KEYLENGTH] = { 0, };
    byte IV[CryptoType::BLOCKSIZE] = { 0x01, };

    // CBC 모드
    sEnc = CBC_Encrypt<CryptoType>(KEY, IV, sText);
    sDec = CBC_Decrypt<CryptoType>(KEY, IV, sEnc);

    cout << CryptoType::StaticAlgorithmName() << " : " << "CBC_MODE" << endl;
    cout << sText << "\n -> " << sEnc << "\n -> " << sDec << endl;

    char buff[100];
    sprintf(buff, "%s : CBC_MODE\n%s\n->%s\n->%s\n", CryptoType::StaticAlgorithmName(), sText, sEnc, sDec);
    OutputDebugStringA(buff);


    // ECB 모드
    sEnc = ECB_Encrypt<CryptoType>(KEY, sText);
    sDec = ECB_Decrypt<CryptoType>(KEY, sEnc);

    cout << CryptoType::StaticAlgorithmName() << " : " << "ECB_MODE" << endl;
    cout << sText << "\n -> " << sEnc << "\n -> " << sDec << endl;
    cout << endl;
}

void test2()
{
    OutputDebugString(_T("테스트22\n"));
}
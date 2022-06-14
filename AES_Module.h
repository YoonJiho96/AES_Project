#pragma once
using namespace std;

#pragma warning(disable: 4996)
//#pragma comment(lib, "cryptlib")
#pragma comment(lib, "cryptopp")
#include <iostream>

#include "dll.h"        // dll ���� ���� �տ� ��ġ�ؾ���
#include "cryptlib.h"
#include "base64.h"
#include "aes.h"
#include "modes.h"
#include "filters.h"

// #include "AES_Module.hpp"

// ���ø��� ����� ����
class CAES_Module
{
public:
    /*
    CAES_Module();
    ~CAES_Module();

    template <class TyMode>
    string Encrypt(TyMode &Encryptor, const string &PlainText){};
    template <class TyMode>
    string Decrypt(TyMode &Decryptor, const string &EncodedText){};

    template <class Ty>
    string CBC_Encrypt(byte *KEY, byte *IV, const string &PlainText){};
    template <class Ty>
    std::string CBC_Decrypt(byte *KEY, byte *IV, const std::string &PlainText){};
    template <class Ty>
    std::string ECB_Encrypt(byte *KEY, const std::string &PlainText){};
    template <class Ty>
    std::string ECB_Decrypt(byte *KEY, const std::string &PlainText){};

    template <class CryptoType>
    void Test(){};

    void test2(){ OutputDebugString(_T("�׽�Ʈ2\n")); }
    */

    CAES_Module::CAES_Module()
    {
        OutputDebugString(_T("��ü����\n"));
    }


    CAES_Module::~CAES_Module()
    {
    }

    template <class TyMode>
    string Encrypt(TyMode &Encryptor, const string &PlainText)
    {
        string EncodedText;
        OutputDebugString(_T("��ȣȭ\n"));

        try
        {
            CryptoPP::StringSource(PlainText, TRUE,
                new CryptoPP::StreamTransformationFilter(Encryptor,
                new CryptoPP::Base64Encoder(new CryptoPP::StringSink(EncodedText), false)
                ));
        }
        catch (...)
        {
        }

        char buff1[100];
        sprintf(buff1, "��ȣ ��� : %s\n", EncodedText);
        OutputDebugStringA(buff1);
        return EncodedText;
    }

    template <class TyMode>
    string Decrypt(TyMode &Decryptor, const string &EncodedText)
    {
        string recoveredText;
        OutputDebugString(_T("��ȣȭ\n"));

        try
        {
            CryptoPP::StringSource(EncodedText, true,
                new CryptoPP::Base64Decoder(
                new CryptoPP::StreamTransformationFilter(Decryptor,
                new CryptoPP::StringSink(recoveredText),
                CryptoPP::BlockPaddingSchemeDef::ZEROS_PADDING
                )
                )
                );
        }
        catch (...)
        {
        }

        char buff1[100];
        sprintf(buff1, "��ȣ ��� : %s\n", recoveredText);
        OutputDebugStringA(buff1);
        return recoveredText;
    }

    // �� ��� �� ��ȣ/��ȣ
    template <class Ty>
    string CBC_Encrypt(byte *KEY, byte *IV, const string &PlainText)
    {
        OutputDebugString(_T("CBC_Encrypt Start\n"));
        typename CryptoPP::CBC_Mode<Ty>::Encryption Encryptor(KEY, Ty::DEFAULT_KEYLENGTH, IV);
        return Encrypt(Encryptor, PlainText);
    }

    template <class Ty>
    std::string CBC_Decrypt(byte *KEY, byte *IV, const std::string &PlainText)
    {
        OutputDebugString(_T("CBC_Decrypt Start\n"));
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
        OutputDebugString(_T("�׽�Ʈ����\n"));
        string sText = "Plain Text";
        string sEnc, sDec;

        byte KEY[CryptoType::DEFAULT_KEYLENGTH] = { 0, };
        byte IV[CryptoType::BLOCKSIZE] = { 0x01, };

        // CBC ���
        //sEnc = CBC_Encrypt<CryptoType>(KEY, IV, sText);
        //sDec = CBC_Decrypt<CryptoType>(KEY, IV, sEnc);

        //cout << CryptoType::StaticAlgorithmName() << " : " << "CBC_MODE" << endl;
        //cout << sText << "\n -> " << sEnc << "\n -> " << sDec << endl;

        // ECB ���
        sEnc = ECB_Encrypt<CryptoType>(KEY, sText);
        sDec = ECB_Decrypt<CryptoType>(KEY, sEnc);

        //cout << CryptoType::StaticAlgorithmName() << " : " << "ECB_MODE" << endl;
       // cout << sText << "\n -> " << sEnc << "\n -> " << sDec << endl;
        //cout << endl;
    }
};

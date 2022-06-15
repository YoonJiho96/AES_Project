#pragma once
#pragma warning(disable: 4996)

using namespace std;
#include <iostream>

#include "dll.h"        // dll ���� ���� �տ� ��ġ�ؾ���
#include "cryptlib.h"
#include "base64.h"
#include "aes.h"
#include "modes.h"
#include "filters.h"

//#pragma comment(lib, "cryptlib")
//#pragma comment(lib, "cryptopp")        // dll �Ͻ��� ��ŷ


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
        OutputDebugString(_T("��ȣȭ\n"));

        string EncodedText;

        try
        {
            CryptoPP::StringSource(PlainText, true,
                new CryptoPP::StreamTransformationFilter(Encryptor,
                    new CryptoPP::Base64Encoder(new CryptoPP::StringSink(EncodedText), false), 
                    CryptoPP::BlockPaddingSchemeDef::ZEROS_PADDING
                    )
                    );
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
        OutputDebugString(_T("��ȣȭ\n"));

        string recoveredText;

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

        char buff[100];
        sprintf(buff, "��ȣ ��� : %s\n", recoveredText);
        OutputDebugStringA(buff);
        return recoveredText;
    }

    // �� ��� �� ��ȣ/��ȣ (CBC, ECB)
    template <class Ty>
    string CBC_Encrypt(byte *KEY, byte *IV, const string &PlainText)
    {
        OutputDebugString(_T("CBC_Encrypt Start\n"));
       // typename CryptoPP::CBC_Mode<Ty>::Encryption Encryptor(KEY, Ty::DEFAULT_KEYLENGTH, IV);

        typename CryptoPP::CBC_Mode<Ty>::Encryption Encryptor;
        Encryptor.SetKeyWithIV(KEY, Ty::DEFAULT_KEYLENGTH, IV);
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

    // �׽�Ʈ �Լ�
    template <class CryptoType>
    void Test(CString inputStr)
    {
        OutputDebugString(_T("�׽�Ʈ����\n"));
        string sText;
        if (inputStr != "")
            sText = string(CT2CA(inputStr));
        else
            sText = "Plain Text";

        string sEnc, sDec;

        byte KEY[CryptoType::DEFAULT_KEYLENGTH] = { 0, };
        byte IV[CryptoType::BLOCKSIZE] = { 0x01, };

        // CBC ���
        sEnc = CBC_Encrypt<CryptoType>(KEY, IV, sText);
        sDec = CBC_Decrypt<CryptoType>(KEY, IV, sEnc);

        //cout << CryptoType::StaticAlgorithmName() << " : " << "CBC_MODE" << endl;
        //cout << sText << "\n -> " << sEnc << "\n -> " << sDec << endl;

        // ECB ���
        //sEnc = ECB_Encrypt<CryptoType>(KEY, sText);
        //sDec = ECB_Decrypt<CryptoType>(KEY, sEnc);

        //cout << CryptoType::StaticAlgorithmName() << " : " << "ECB_MODE" << endl;
       // cout << sText << "\n -> " << sEnc << "\n -> " << sDec << endl;
        //cout << endl;
    }

    // �е� ��� ����
    CryptoPP::BlockPaddingSchemeDef::BlockPaddingScheme GetPaddingSch(CString selected)
    {
        if (selected == "NO_PADDING")
            return CryptoPP::BlockPaddingSchemeDef::NO_PADDING;
        else if (selected == "ZEROS_PADDING")
            return CryptoPP::BlockPaddingSchemeDef::ZEROS_PADDING;
        else if (selected == "PKCS_PADDING")
            return CryptoPP::BlockPaddingSchemeDef::PKCS_PADDING;
        else if (selected == "ONE_AND_ZEROS_PADDING")
            return CryptoPP::BlockPaddingSchemeDef::ONE_AND_ZEROS_PADDING;
        else if (selected == "DEFAULT_PADDING")
            return CryptoPP::BlockPaddingSchemeDef::DEFAULT_PADDING;
    }

    // ���, �е� ���� ������ ����
    template <class CryptoType>
    string testEncyp(CString inputStr, CString mod, CryptoPP::BlockPaddingSchemeDef::BlockPaddingScheme pad)
    {
        string sText;
        if (inputStr != "")
            sText = string(CT2CA(inputStr));
        else
            sText = "Plain Text";

        string sEnc, sDec;

        byte KEY[CryptoType::DEFAULT_KEYLENGTH] = { 0, };
        byte IV[CryptoType::BLOCKSIZE] = { 0x01, };

        if (mod == "ECB")
        {
            // ECB ���
            sEnc = ECB_Encrypt<CryptoType>(KEY, sText);
            sDec = ECB_Decrypt<CryptoType>(KEY, sEnc);
        }
        else if (mod == "CBC")
        {
            // CBC ���
            sEnc = CBC_Encrypt<CryptoType>(KEY, IV, sText);
            sDec = CBC_Decrypt<CryptoType>(KEY, IV, sEnc);
        }

        return sEnc;
    }
};

#pragma once
#pragma warning(disable: 4996)

using namespace std;
#include <iostream>

#include "dll.h"        // dll 사용시 가장 앞에 위치해야함
#include "cryptlib.h"
#include "base64.h"
#include "aes.h"
#include "modes.h"
#include "filters.h"

//#pragma comment(lib, "cryptlib")
//#pragma comment(lib, "cryptopp")        // dll 암시적 링킹


// 템플릿은 헤더에 정의
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

    void test2(){ OutputDebugString(_T("테스트2\n")); }
    */

    CAES_Module::CAES_Module()
    {
        OutputDebugString(_T("객체생성\n"));
    }


    CAES_Module::~CAES_Module()
    {
    }

    template <class TyMode>
    string Encrypt(TyMode &Encryptor, const string &PlainText)
    {
        OutputDebugString(_T("암호화\n"));

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
        sprintf(buff1, "암호 결과 : %s\n", EncodedText);
        OutputDebugStringA(buff1);

        return EncodedText;
    }

    template <class TyMode>
    string Decrypt(TyMode &Decryptor, const string &EncodedText)
    {
        OutputDebugString(_T("복호화\n"));

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
        sprintf(buff, "복호 결과 : %s\n", recoveredText);
        OutputDebugStringA(buff);
        return recoveredText;
    }

    // 각 모드 별 암호/복호 (CBC, ECB)
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

    // 테스트 함수
    template <class CryptoType>
    void Test(CString inputStr)
    {
        OutputDebugString(_T("테스트실행\n"));
        string sText;
        if (inputStr != "")
            sText = string(CT2CA(inputStr));
        else
            sText = "Plain Text";

        string sEnc, sDec;

        byte KEY[CryptoType::DEFAULT_KEYLENGTH] = { 0, };
        byte IV[CryptoType::BLOCKSIZE] = { 0x01, };

        // CBC 모드
        sEnc = CBC_Encrypt<CryptoType>(KEY, IV, sText);
        sDec = CBC_Decrypt<CryptoType>(KEY, IV, sEnc);

        //cout << CryptoType::StaticAlgorithmName() << " : " << "CBC_MODE" << endl;
        //cout << sText << "\n -> " << sEnc << "\n -> " << sDec << endl;

        // ECB 모드
        //sEnc = ECB_Encrypt<CryptoType>(KEY, sText);
        //sDec = ECB_Decrypt<CryptoType>(KEY, sEnc);

        //cout << CryptoType::StaticAlgorithmName() << " : " << "ECB_MODE" << endl;
       // cout << sText << "\n -> " << sEnc << "\n -> " << sDec << endl;
        //cout << endl;
    }

    // 패딩 모드 리턴
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

    // 모드, 패딩 정보 포함한 동작
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
            // ECB 모드
            sEnc = ECB_Encrypt<CryptoType>(KEY, sText);
            sDec = ECB_Decrypt<CryptoType>(KEY, sEnc);
        }
        else if (mod == "CBC")
        {
            // CBC 모드
            sEnc = CBC_Encrypt<CryptoType>(KEY, IV, sText);
            sDec = CBC_Decrypt<CryptoType>(KEY, IV, sEnc);
        }

        return sEnc;
    }
};

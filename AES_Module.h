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

#include <cstring>

//#pragma comment(lib, "cryptlib")
//#pragma comment(lib, "cryptopp")        // dll 암시적 링킹


// 템플릿은 헤더에 정의
class CAES_Module
{
public:
    string strResult;

    CAES_Module::CAES_Module()
    {
        OutputDebugString(_T("객체생성\n"));
    }


    CAES_Module::~CAES_Module()
    {
        OutputDebugString(_T("객체제거\n"));
    }

    // ----- 암호화 템플릿 ----- //
    template <class TyMode>
    string Encrypt(TyMode &Encryptor, const string &PlainText)
    {
        OutputDebugString(_T("암호화\n"));

        // DLL 내에서 해제되도록 설정
        string *EncodedText = new string();

        try
        {
            // 일괄 동작
            /*
            CryptoPP::StringSource(PlainText, true,
                new CryptoPP::StreamTransformationFilter(Encryptor,
                    new CryptoPP::Base64Encoder(new CryptoPP::StringSink(EncodedText), false), 
                    CryptoPP::BlockPaddingSchemeDef::ZEROS_PADDING
                    )
                    );
            */
            
            // 모듈 개별 생성으로 변경
            CryptoPP::StringSink *strSnk = new CryptoPP::StringSink(*EncodedText);
            CryptoPP::Base64Encoder *bs = new CryptoPP::Base64Encoder(strSnk, false);

            CryptoPP::BlockPaddingSchemeDef::BlockPaddingScheme paddingType = CryptoPP::BlockPaddingSchemeDef::ZEROS_PADDING;

            CryptoPP::StreamTransformationFilter *stf = new CryptoPP::StreamTransformationFilter(Encryptor, bs, paddingType);
            CryptoPP::StringSource strSrc = new CryptoPP::StringSource(PlainText, true, stf);
        }
        catch (...)
        {
        }

        char buff1[100];
        sprintf(buff1, "암호 결과 : %s\n", *EncodedText);
        OutputDebugStringA(buff1);

        strResult = *EncodedText;
        return *EncodedText;
    }

    // ----- 복호화 템플릿 ------ //
    template <class TyMode>
    string Decrypt(TyMode &Decryptor, const string &EncodedText)
    {
        OutputDebugString(_T("복호화\n"));

        string *recoveredText = new string();

        try
        {
            CryptoPP::StringSource(EncodedText, true,
                new CryptoPP::Base64Decoder(
                new CryptoPP::StreamTransformationFilter(Decryptor,
                new CryptoPP::StringSink(*recoveredText),
                CryptoPP::BlockPaddingSchemeDef::ZEROS_PADDING
                )
                )
                );
        }
        catch (...)
        {
        }

        char buff_dec[100];
        sprintf(buff_dec, "복호 결과 : %s\n", *recoveredText);
        OutputDebugStringA(buff_dec);

        return *recoveredText;
    }

    // ------- CBC 모드 -------- //
    // CBC 모드 암호화
    template <class Ty>
    string CBC_Encrypt(byte *KEY, byte *IV, const string &PlainText)
    {
        OutputDebugString(_T("CBC_Encrypt Start\n"));

        typename CryptoPP::CBC_Mode<Ty>::Encryption Encryptor;
        Encryptor.SetKeyWithIV(KEY, Ty::DEFAULT_KEYLENGTH, IV);
        return Encrypt(Encryptor, PlainText);
    }
    // CBC 모드 복호화
    template <class Ty>
    string CBC_Decrypt(byte *KEY, byte *IV, const std::string &PlainText)
    {
        OutputDebugString(_T("CBC_Decrypt Start\n"));
        
        typename CryptoPP::CBC_Mode<Ty>::Decryption Decryptor(KEY, Ty::DEFAULT_KEYLENGTH, IV);
        return Decrypt(Decryptor, PlainText);
    }


    // ------- ECB 모드 --------- //
    // ECB 모드 암호화
    template <class Ty>
    string ECB_Encrypt(byte *KEY, const std::string &PlainText)
    {
        OutputDebugString(_T("ECB_Encrypt Start\n"));

        typename CryptoPP::ECB_Mode<Ty>::Encryption Encryptor(KEY, Ty::DEFAULT_KEYLENGTH);
        return Encrypt(Encryptor, PlainText);
    }
    // ECB 모드 복호화
    template <class Ty>
    string ECB_Decrypt(byte *KEY, const std::string &PlainText)
    {
        OutputDebugString(_T("ECB_Decrypt Start\n"));

        typename CryptoPP::ECB_Mode<Ty>::Decryption Decryptor(KEY, Ty::DEFAULT_KEYLENGTH);
        return Decrypt(Decryptor, PlainText);
    }


    // ------- 패딩 모드 리턴 ---------- //
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
    void testEncyp(CString inputStr, CString mod, CryptoPP::BlockPaddingSchemeDef::BlockPaddingScheme pad)
    {
        string sText;
        if (inputStr != "")
            sText = string(CT2CA(inputStr));
        else
            sText = "Plain Text";

        string sEnc, sDec;

        byte KEY[CryptoType::DEFAULT_KEYLENGTH] = { 0, };
        // byte KEY[CryptoType::DEFAULT_KEYLENGTH] = "abcdefg";
        byte IV[CryptoType::BLOCKSIZE] = { 0x01, };

        CString strt(KEY);      // byte to CString

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
        
        // strResult = sEnc.c_str();
        
        // return sEnc;
    }
};

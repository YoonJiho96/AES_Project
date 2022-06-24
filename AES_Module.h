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
private:
    // 암호화 결과값
    string strResult;
    string strDecResult;

public:
    CAES_Module::CAES_Module()
    {
        OutputDebugString(_T("객체생성\n"));
    }
    CAES_Module::~CAES_Module()
    {
        OutputDebugString(_T("객체제거\n"));
    }


    // 암호화 결과값 리턴
    CAES_Module::string GetEncResult()
    {
        return strResult;
    }

    CAES_Module::string GetDecResult()
    {
        return strDecResult;
    }


    // ----- 암호화 템플릿 ----- //
    template <class TyMode>
    string Encrypt(TyMode &Encryptor, const string &PlainText, CString pad)
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

            // 패딩 타입 불러오기
            CryptoPP::BlockPaddingSchemeDef::BlockPaddingScheme paddingType = GetPaddingSch(pad);
            
            // 모듈 개별 생성으로 변경
            CryptoPP::StringSink *strSnk = new CryptoPP::StringSink(*EncodedText);
            CryptoPP::Base64Encoder *bs = new CryptoPP::Base64Encoder(strSnk, false);
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
    string Decrypt(TyMode &Decryptor, const string &EncodedText, CString pad)
    {
        OutputDebugString(_T("복호화\n"));

        string *recoveredText = new string();

        try
        {
            CryptoPP::BlockPaddingSchemeDef::BlockPaddingScheme paddingType = GetPaddingSch(pad);
            // CryptoPP::BlockPaddingSchemeDef::BlockPaddingScheme paddingType = CryptoPP::BlockPaddingSchemeDef::BlockPaddingScheme::ZEROS_PADDING;

            /*
            CryptoPP::StringSource(EncodedText, true,
                new CryptoPP::Base64Decoder(
                new CryptoPP::StreamTransformationFilter(Decryptor,
                new CryptoPP::StringSink(*recoveredText),
                CryptoPP::BlockPaddingSchemeDef::ZEROS_PADDING
                )
                )
                );
                */
            /*
            CryptoPP::StringSource(EncodedText, true,
                new CryptoPP::Base64Decoder(
                new CryptoPP::StreamTransformationFilter(Decryptor, new CryptoPP::StringSink(*recoveredText), paddingType)
                )
                );
            */
            CryptoPP::StringSink *strSnk = new CryptoPP::StringSink(*recoveredText);
            CryptoPP::StreamTransformationFilter *stmFmt = new CryptoPP::StreamTransformationFilter(Decryptor, strSnk, paddingType);
            CryptoPP::Base64Decoder *b64Dec = new CryptoPP::Base64Decoder(stmFmt);
            CryptoPP::StringSource strSrc = new CryptoPP::StringSource(EncodedText, true, b64Dec);
        }
        catch (...)
        {
            OutputDebugString(_T("Decrypt Error\n"));
        }

        char buff_dec[100];
        //sprintf(buff_dec, "복호 결과 : %s\n", *recoveredText);
        // OutputDebugStringA(buff_dec);

        strDecResult = *recoveredText;

        return *recoveredText;
    }

    // ------- CBC 모드 -------- //
    // CBC 모드 암호화
    template <class Ty>
    string CBC_Encrypt(byte *KEY, byte *IV, const string &PlainText, CString pad)
    {
        OutputDebugString(_T("CBC_Encrypt Start\n"));

        typename CryptoPP::CBC_Mode<Ty>::Encryption Encryptor;
        Encryptor.SetKeyWithIV(KEY, Ty::DEFAULT_KEYLENGTH, IV);
        return Encrypt(Encryptor, PlainText, pad);
    }

    // CBC 모드 복호화
    template <class Ty>
    string CBC_Decrypt(byte *KEY, byte *IV, const std::string &PlainText, CString pad)
    {
        OutputDebugString(_T("CBC_Decrypt Start\n"));
        
        typename CryptoPP::CBC_Mode<Ty>::Decryption Decryptor(KEY, Ty::DEFAULT_KEYLENGTH, IV);
        return Decrypt(Decryptor, PlainText, pad);
    }


    // ------- ECB 모드 --------- //
    // ECB 모드 암호화
    template <class Ty>
    string ECB_Encrypt(byte *KEY, const std::string &PlainText, CString pad)
    {
        OutputDebugString(_T("ECB_Encrypt Start\n"));

        typename CryptoPP::ECB_Mode<Ty>::Encryption Encryptor(KEY, Ty::DEFAULT_KEYLENGTH);
        return Encrypt(Encryptor, PlainText, pad);
    }

    // ECB 모드 복호화
    template <class Ty>
    string ECB_Decrypt(byte *KEY, const std::string &PlainText, CString pad)
    {
        OutputDebugString(_T("ECB_Decrypt Start\n"));

        typename CryptoPP::ECB_Mode<Ty>::Decryption Decryptor(KEY, Ty::DEFAULT_KEYLENGTH);
        return Decrypt(Decryptor, PlainText, pad);
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
        else if (selected == "W3C_PADDING")
            return CryptoPP::BlockPaddingSchemeDef::W3C_PADDING;
    }


    // 모드, 패딩 정보 포함한 동작
    template <class CryptoType>
    void testEncyp(CString inputStr, CString mod, CString pad)
    {
        // 평문 확인
        string sText;
        if (inputStr != "")
            sText = string(CT2CA(inputStr));
        else
            sText = "Plain Text";

        // 결과 문자열
        string sEnc, sDec;

        // 키/벡터 설정
        // byte KEY[CryptoType::DEFAULT_KEYLENGTH] = { 0, };
        byte KEY[CryptoType::DEFAULT_KEYLENGTH] = "abcdefg";
        byte IV[CryptoType::BLOCKSIZE] = { 0x01, };

        CString strt(KEY);      // KEY - byte to CString

        // 모드 별 동작
        if (mod == "ECB")
        {
            // ECB 모드
            // sEnc = ECB_Encrypt<CryptoType>(KEY, sText);
            sEnc = ECB_Encrypt<CryptoType>(KEY, sText, pad);
            sDec = ECB_Decrypt<CryptoType>(KEY, sEnc, pad);
        }
        else if (mod == "CBC")
        {
            // CBC 모드
            sEnc = CBC_Encrypt<CryptoType>(KEY, IV, sText, pad);
            sDec = CBC_Decrypt<CryptoType>(KEY, IV, sEnc, pad);
        }
        
        // strResult = sEnc.c_str();
        
        // return sEnc;
    }


    template < class CryptoType >
    void DoEncryptResult(CString inputStr, CString mod, CString pad)
    {
        // 평문 확인
        string sText;
        if (inputStr != "")
            sText = string(CT2CA(inputStr));
        else
        {
            AfxMessageBox(_T("Need PlainText!"));
            return
        }

        // 결과 문자열
        string sEnc, sDec;

        // 키/벡터 설정
        byte KEY[CryptoType::DEFAULT_KEYLENGTH] = { 0, };
        byte IV[CryptoType::BLOCKSIZE] = { 0x01, };

        CString strt(KEY);      // KEY - byte to CString

        // 모드 별 동작
        if (mod == "ECB")
        {
            // ECB 모드
            // sEnc = ECB_Encrypt<CryptoType>(KEY, sText);
            sEnc = ECB_Encrypt<CryptoType>(KEY, sText, pad);
            sDec = ECB_Decrypt<CryptoType>(KEY, sEnc, pad);
        }
        else if (mod == "CBC")
        {
            // CBC 모드
            sEnc = CBC_Encrypt<CryptoType>(KEY, IV, sText, pad);
            sDec = CBC_Decrypt<CryptoType>(KEY, IV, sEnc, pad);
        }

        // strResult = sEnc.c_str();

        // return sEnc;
    }

    template < class CryptoType >
    void DoDecryptResult(CString inputStr, CString mod, CString pad)
    {
        // 평문 확인
        string sText;
        if (inputStr != "")
            sText = string(CT2CA(inputStr));
        else
            sText = "Plain Text";

        // 결과 문자열
        string sEnc, sDec;

        // 키/벡터 설정
        byte KEY[CryptoType::DEFAULT_KEYLENGTH] = { 0, };
        // byte KEY[CryptoType::DEFAULT_KEYLENGTH] = "abcdefg";
        byte IV[CryptoType::BLOCKSIZE] = { 0x01, };

        CString strt(KEY);      // KEY - byte to CString

        // 모드 별 동작
        if (mod == "ECB")
        {
            // ECB 모드
            // sEnc = ECB_Encrypt<CryptoType>(KEY, sText);
            sEnc = ECB_Encrypt<CryptoType>(KEY, sText, pad);
            sDec = ECB_Decrypt<CryptoType>(KEY, sEnc, pad);
        }
        else if (mod == "CBC")
        {
            // CBC 모드
            sEnc = CBC_Encrypt<CryptoType>(KEY, IV, sText, pad);
            sDec = CBC_Decrypt<CryptoType>(KEY, IV, sEnc, pad);
        }

        // strResult = sEnc.c_str();

        // return sEnc;
    }

};

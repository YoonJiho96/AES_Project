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
    string GetEncResult()
    {
        return strResult;
    }

    string GetDecResult()
    {
        return strDecResult;
    }


    // ----- 암호화 템플릿 ----- //
    template <class TyMode>
    void Encrypt(TyMode &Encryptor, const string &PlainText, CString pad)
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
            OutputDebugString(_T("Encrypt Error\n"));
        }

        // 출력 후 스택 오버런 오류 발생.
        //char buff1[100];
        //sprintf(buff1, "암호 결과 : %s\n", *EncodedText);
        ///OutputDebugStringA(buff1);

        strResult = *EncodedText;
    }

    // ----- 복호화 템플릿 ------ //
    template <class TyMode>
    void Decrypt(TyMode &Decryptor, const string &EncodedText, CString pad)
    {
        OutputDebugString(_T("복호화\n"));

        string *recoveredText = new string();
        try
        {
            CryptoPP::BlockPaddingSchemeDef::BlockPaddingScheme paddingType = GetPaddingSch(pad);
            CryptoPP::StringSink *strSnk = new CryptoPP::StringSink(*recoveredText);
            CryptoPP::StreamTransformationFilter *stmFmt = new CryptoPP::StreamTransformationFilter(Decryptor, strSnk, paddingType);
            CryptoPP::Base64Decoder *b64Dec = new CryptoPP::Base64Decoder(stmFmt);
            CryptoPP::StringSource strSrc = new CryptoPP::StringSource(EncodedText, true, b64Dec);
        }
        catch (...)
        {
            OutputDebugString(_T("Decrypt Error\n"));
            // 키, IV 등의 정보가 정확하지 않아 복호에 오류가 있을 경우 처리.
            AfxMessageBox(_T("Decryption Error\nCheck Inputs"));
        }

        // char buff_dec[100];
        // sprintf(buff_dec, "복호 결과 : %s\n", *recoveredText);
        // OutputDebugStringA(buff_dec);

        strDecResult = *recoveredText;
    }

    // ------- CBC 모드 -------- //
    // CBC 모드 암호화
    template <class Ty>
    void CBC_Encrypt(byte *KEY, byte *IV, const string &PlainText, CString pad)
    {
        OutputDebugString(_T("CBC_Encrypt Start\n"));

        typename CryptoPP::CBC_Mode<Ty>::Encryption Encryptor;
        Encryptor.SetKeyWithIV(KEY, Ty::DEFAULT_KEYLENGTH, IV);
        Encrypt(Encryptor, PlainText, pad);
    }

    // CBC 모드 복호화
    template <class Ty>
    void CBC_Decrypt(byte *KEY, byte *IV, const std::string &PlainText, CString pad)
    {
        OutputDebugString(_T("CBC_Decrypt Start\n"));
        
        typename CryptoPP::CBC_Mode<Ty>::Decryption Decryptor(KEY, Ty::DEFAULT_KEYLENGTH, IV);
        Decrypt(Decryptor, PlainText, pad);
    }


    // ------- ECB 모드 --------- //
    // ECB 모드 암호화
    template <class Ty>
    void ECB_Encrypt(byte *KEY, const std::string &PlainText, CString pad)
    {
        OutputDebugString(_T("ECB_Encrypt Start\n"));

        typename CryptoPP::ECB_Mode<Ty>::Encryption Encryptor(KEY, Ty::DEFAULT_KEYLENGTH);
        Encrypt(Encryptor, PlainText, pad);
    }

    // ECB 모드 복호화
    template <class Ty>
    void ECB_Decrypt(byte *KEY, const std::string &PlainText, CString pad)
    {
        OutputDebugString(_T("ECB_Decrypt Start\n"));

        typename CryptoPP::ECB_Mode<Ty>::Decryption Decryptor(KEY, Ty::DEFAULT_KEYLENGTH);
        Decrypt(Decryptor, PlainText, pad);
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

    // ------- 암호화 실행 ------- //
    template < class CryptoType >
    void DoEncryptResult(CString inputStr, CString mod, CString pad, byte *KEY, byte *IV)
    {
        // 평문 확인
        string sText;
        if (inputStr != "")
        {
            sText = string(CT2CA(inputStr));
        }
        else
        {
            AfxMessageBox(_T("Need PlainText!"));
            return;
        }

        // 모드 별 동작
        if (mod == "ECB")
        {
            // ECB 모드
            ECB_Encrypt<CryptoType>(KEY, sText, pad);
        }
        else if (mod == "CBC")
        {
            // CBC 모드
            CBC_Encrypt<CryptoType>(KEY, IV, sText, pad);
        }
    }

    // ------- 복호화 실행 ------- //
    template < class CryptoType >
    void DoDecryptResult(CString inputStr, CString mod, CString pad, byte *KEY, byte *IV)
    {
        // 평문 확인
        string sText;
        if (inputStr != "")
            sText = string(CT2CA(inputStr));
        else
        {
            AfxMessageBox(_T("Need PlainText!"));
            return;
        }

        // 모드 별 동작
        if (mod == "ECB")
        {
            // ECB 모드
            ECB_Decrypt<CryptoType>(KEY, sText, pad);
        }
        else if (mod == "CBC")
        {
            // CBC 모드
            CBC_Decrypt<CryptoType>(KEY, IV, sText, pad);
        }
    }
};

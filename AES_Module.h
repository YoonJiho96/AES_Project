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

#include <cstring>

//#pragma comment(lib, "cryptlib")
//#pragma comment(lib, "cryptopp")        // dll �Ͻ��� ��ŷ


// ���ø��� ����� ����
class CAES_Module
{
public:
    string strResult;

    CAES_Module::CAES_Module()
    {
        OutputDebugString(_T("��ü����\n"));
    }


    CAES_Module::~CAES_Module()
    {
        OutputDebugString(_T("��ü����\n"));
    }

    // ----- ��ȣȭ ���ø� ----- //
    template <class TyMode>
    string Encrypt(TyMode &Encryptor, const string &PlainText)
    {
        OutputDebugString(_T("��ȣȭ\n"));

        // DLL ������ �����ǵ��� ����
        string *EncodedText = new string();

        try
        {
            // �ϰ� ����
            /*
            CryptoPP::StringSource(PlainText, true,
                new CryptoPP::StreamTransformationFilter(Encryptor,
                    new CryptoPP::Base64Encoder(new CryptoPP::StringSink(EncodedText), false), 
                    CryptoPP::BlockPaddingSchemeDef::ZEROS_PADDING
                    )
                    );
            */
            
            // ��� ���� �������� ����
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
        sprintf(buff1, "��ȣ ��� : %s\n", *EncodedText);
        OutputDebugStringA(buff1);

        strResult = *EncodedText;
        return *EncodedText;
    }

    // ----- ��ȣȭ ���ø� ------ //
    template <class TyMode>
    string Decrypt(TyMode &Decryptor, const string &EncodedText)
    {
        OutputDebugString(_T("��ȣȭ\n"));

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
        sprintf(buff_dec, "��ȣ ��� : %s\n", *recoveredText);
        OutputDebugStringA(buff_dec);

        return *recoveredText;
    }

    // ------- CBC ��� -------- //
    // CBC ��� ��ȣȭ
    template <class Ty>
    string CBC_Encrypt(byte *KEY, byte *IV, const string &PlainText)
    {
        OutputDebugString(_T("CBC_Encrypt Start\n"));

        typename CryptoPP::CBC_Mode<Ty>::Encryption Encryptor;
        Encryptor.SetKeyWithIV(KEY, Ty::DEFAULT_KEYLENGTH, IV);
        return Encrypt(Encryptor, PlainText);
    }
    // CBC ��� ��ȣȭ
    template <class Ty>
    string CBC_Decrypt(byte *KEY, byte *IV, const std::string &PlainText)
    {
        OutputDebugString(_T("CBC_Decrypt Start\n"));
        
        typename CryptoPP::CBC_Mode<Ty>::Decryption Decryptor(KEY, Ty::DEFAULT_KEYLENGTH, IV);
        return Decrypt(Decryptor, PlainText);
    }


    // ------- ECB ��� --------- //
    // ECB ��� ��ȣȭ
    template <class Ty>
    string ECB_Encrypt(byte *KEY, const std::string &PlainText)
    {
        OutputDebugString(_T("ECB_Encrypt Start\n"));

        typename CryptoPP::ECB_Mode<Ty>::Encryption Encryptor(KEY, Ty::DEFAULT_KEYLENGTH);
        return Encrypt(Encryptor, PlainText);
    }
    // ECB ��� ��ȣȭ
    template <class Ty>
    string ECB_Decrypt(byte *KEY, const std::string &PlainText)
    {
        OutputDebugString(_T("ECB_Decrypt Start\n"));

        typename CryptoPP::ECB_Mode<Ty>::Decryption Decryptor(KEY, Ty::DEFAULT_KEYLENGTH);
        return Decrypt(Decryptor, PlainText);
    }


    // ------- �е� ��� ���� ---------- //
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
        
        // strResult = sEnc.c_str();
        
        // return sEnc;
    }
};

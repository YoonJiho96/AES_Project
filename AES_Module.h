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
private:
    // ��ȣȭ �����
    string strResult;
    string strDecResult;

public:
    CAES_Module::CAES_Module()
    {
        OutputDebugString(_T("��ü����\n"));
    }
    CAES_Module::~CAES_Module()
    {
        OutputDebugString(_T("��ü����\n"));
    }


    // ��ȣȭ ����� ����
    string GetEncResult()
    {
        return strResult;
    }

    string GetDecResult()
    {
        return strDecResult;
    }


    // ----- ��ȣȭ ���ø� ----- //
    template <class TyMode>
    void Encrypt(TyMode &Encryptor, const string &PlainText, CString pad)
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

            // �е� Ÿ�� �ҷ�����
            CryptoPP::BlockPaddingSchemeDef::BlockPaddingScheme paddingType = GetPaddingSch(pad);
            
            // ��� ���� �������� ����
            CryptoPP::StringSink *strSnk = new CryptoPP::StringSink(*EncodedText);
            CryptoPP::Base64Encoder *bs = new CryptoPP::Base64Encoder(strSnk, false);
            CryptoPP::StreamTransformationFilter *stf = new CryptoPP::StreamTransformationFilter(Encryptor, bs, paddingType);
            CryptoPP::StringSource strSrc = new CryptoPP::StringSource(PlainText, true, stf);
        }
        catch (...)
        {
            OutputDebugString(_T("Encrypt Error\n"));
        }

        // ��� �� ���� ������ ���� �߻�.
        //char buff1[100];
        //sprintf(buff1, "��ȣ ��� : %s\n", *EncodedText);
        ///OutputDebugStringA(buff1);

        strResult = *EncodedText;
    }

    // ----- ��ȣȭ ���ø� ------ //
    template <class TyMode>
    void Decrypt(TyMode &Decryptor, const string &EncodedText, CString pad)
    {
        OutputDebugString(_T("��ȣȭ\n"));

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
            // Ű, IV ���� ������ ��Ȯ���� �ʾ� ��ȣ�� ������ ���� ��� ó��.
            AfxMessageBox(_T("Decryption Error\nCheck Inputs"));
        }

        // char buff_dec[100];
        // sprintf(buff_dec, "��ȣ ��� : %s\n", *recoveredText);
        // OutputDebugStringA(buff_dec);

        strDecResult = *recoveredText;
    }

    // ------- CBC ��� -------- //
    // CBC ��� ��ȣȭ
    template <class Ty>
    void CBC_Encrypt(byte *KEY, byte *IV, const string &PlainText, CString pad)
    {
        OutputDebugString(_T("CBC_Encrypt Start\n"));

        typename CryptoPP::CBC_Mode<Ty>::Encryption Encryptor;
        Encryptor.SetKeyWithIV(KEY, Ty::DEFAULT_KEYLENGTH, IV);
        Encrypt(Encryptor, PlainText, pad);
    }

    // CBC ��� ��ȣȭ
    template <class Ty>
    void CBC_Decrypt(byte *KEY, byte *IV, const std::string &PlainText, CString pad)
    {
        OutputDebugString(_T("CBC_Decrypt Start\n"));
        
        typename CryptoPP::CBC_Mode<Ty>::Decryption Decryptor(KEY, Ty::DEFAULT_KEYLENGTH, IV);
        Decrypt(Decryptor, PlainText, pad);
    }


    // ------- ECB ��� --------- //
    // ECB ��� ��ȣȭ
    template <class Ty>
    void ECB_Encrypt(byte *KEY, const std::string &PlainText, CString pad)
    {
        OutputDebugString(_T("ECB_Encrypt Start\n"));

        typename CryptoPP::ECB_Mode<Ty>::Encryption Encryptor(KEY, Ty::DEFAULT_KEYLENGTH);
        Encrypt(Encryptor, PlainText, pad);
    }

    // ECB ��� ��ȣȭ
    template <class Ty>
    void ECB_Decrypt(byte *KEY, const std::string &PlainText, CString pad)
    {
        OutputDebugString(_T("ECB_Decrypt Start\n"));

        typename CryptoPP::ECB_Mode<Ty>::Decryption Decryptor(KEY, Ty::DEFAULT_KEYLENGTH);
        Decrypt(Decryptor, PlainText, pad);
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
        else if (selected == "W3C_PADDING")
            return CryptoPP::BlockPaddingSchemeDef::W3C_PADDING;
    }

    // ------- ��ȣȭ ���� ------- //
    template < class CryptoType >
    void DoEncryptResult(CString inputStr, CString mod, CString pad, byte *KEY, byte *IV)
    {
        // �� Ȯ��
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

        // ��� �� ����
        if (mod == "ECB")
        {
            // ECB ���
            ECB_Encrypt<CryptoType>(KEY, sText, pad);
        }
        else if (mod == "CBC")
        {
            // CBC ���
            CBC_Encrypt<CryptoType>(KEY, IV, sText, pad);
        }
    }

    // ------- ��ȣȭ ���� ------- //
    template < class CryptoType >
    void DoDecryptResult(CString inputStr, CString mod, CString pad, byte *KEY, byte *IV)
    {
        // �� Ȯ��
        string sText;
        if (inputStr != "")
            sText = string(CT2CA(inputStr));
        else
        {
            AfxMessageBox(_T("Need PlainText!"));
            return;
        }

        // ��� �� ����
        if (mod == "ECB")
        {
            // ECB ���
            ECB_Decrypt<CryptoType>(KEY, sText, pad);
        }
        else if (mod == "CBC")
        {
            // CBC ���
            CBC_Decrypt<CryptoType>(KEY, IV, sText, pad);
        }
    }
};

#pragma once
#include "stdafx.h"

class CGetEncoding
{
public:
    enum CHARACTER_ENCODING
    {
        ANSI,
        Unicode,
        Unicode_big_endian,
        UTF8_with_BOM,
        UTF8_without_BOM
    };

    CHARACTER_ENCODING CGetEncoding::get_text_file_encoding(const char *filename)
    {
        CHARACTER_ENCODING encoding;

        unsigned char uniTxt[] = { 0xFF, 0xFE };// Unicode file header
        unsigned char endianTxt[] = { 0xFE, 0xFF };// Unicode big endian file header
        unsigned char utf8Txt[] = { 0xEF, 0xBB };// UTF_8 file header

        DWORD dwBytesRead = 0;
        HANDLE hFile = CreateFile((LPCWSTR)filename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hFile == INVALID_HANDLE_VALUE)
        {
            hFile = NULL;
            CloseHandle(hFile);
            throw runtime_error("cannot open file");
        }
        BYTE *lpHeader = new BYTE[2];
        ReadFile(hFile, lpHeader, 2, &dwBytesRead, NULL);
        CloseHandle(hFile);

        if (lpHeader[0] == uniTxt[0] && lpHeader[1] == uniTxt[1])// Unicode file
            encoding = CHARACTER_ENCODING::Unicode;
        else if (lpHeader[0] == endianTxt[0] && lpHeader[1] == endianTxt[1])//  Unicode big endian file
            encoding = CHARACTER_ENCODING::Unicode_big_endian;
        else if (lpHeader[0] == utf8Txt[0] && lpHeader[1] == utf8Txt[1])// UTF-8 file
            encoding = CHARACTER_ENCODING::UTF8_with_BOM;
        else
            encoding = CHARACTER_ENCODING::ANSI;   //Ascii

        delete[]lpHeader;
        return encoding;
    }
};

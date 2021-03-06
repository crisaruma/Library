﻿
#ifndef __LIB_STRING_H__
#define __LIB_STRING_H__

#include "LibData.h"

namespace CLib
{
    class CString
    {
        protected:
	        static std::map< const wchar_t *, const char * >    ConvMap;
            static string mTempString;
            static wstring mTemWString;

        public:
            static const Uint16* Utf8ToUtf16( const char* _pStr );
            static const char* Utf16ToUtf8( const Uint16* _pStr );

            static const char* _WideToUtf8( const wchar_t * str );
            static const char* WideToUtf8( const wchar_t* _str );

            static const wchar_t* _Utf8ToWide( const char* _pStr );


			//	文字列置換
			static string Replace(const string& _src, const string& _dst, const string& _exchange);

			//	文字列の分解
			static const Sint32 Split(CDataMap& _result, const string& _src, const string& _delimita);

    };

};

#define utf8(str)   CString::WideToUtf8(L##str)


typedef CLib::CList<string>         CStringList;
typedef CLib::CMap<string,string>   CStringMap;

#endif
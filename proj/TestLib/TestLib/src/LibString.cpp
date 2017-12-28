
#include "LibString.h"


std::map< const wchar_t *, const char * >   CString::ConvMap;
string                                      CString::mTempString;
wstring                                     CString::mTemWString;

//  Utf8 -> Utf16 の変換
const Uint16* CString::Utf8ToUtf16( const char* _pStr )
{
    const Sint32 len = static_cast<Sint32>(strlen(_pStr) + 1 );
    const Sint32 memSize = len * sizeof( Uint16 ) * 2 ;

    char* pBuf = new char[memSize];
    Uint16* pBuf16 = reinterpret_cast< Uint16* >( pBuf );
    Uint16* pWork = pBuf16;

    for( const char* pInStr = _pStr ; *pInStr != '\0' ; pInStr++ )
    {
        Uint8 c0 = *pInStr;
        if( ( c0 & 0x80 ) == 0 )
        {
            *pWork++ = ( c0 & 0x7F );
        }
        else
        {
            Uint8 c1 = *(++pInStr);
            if( ( c1 & 0xE0 ) == 0xC0 )
            {
                *pWork++ = (( c0 & 0x3F ) << 6) | ( c1 & 0x3F );
            }
            else
            {
                *pWork++ = (( c0 & 0x0F ) << 12 ) | ((c1 & 0x3F) << 6 ) | (*(++pInStr) & 0x3F );
            }
        }
    }
    
    *pWork = 0;
    mTemWString = wstring( reinterpret_cast<wchar_t*>(pBuf16));
    delete[] pBuf;
    return (Uint16*)( mTemWString.c_str() );
}


//  utf16 -> utf8 の変換
const char* CString::Utf16ToUtf8( const Uint16* _pStr )
{
    Uint32 len = 0;
    const Uint16* pStr = _pStr;

    //  メモリ長を検索
    while( *pStr != 0 )
    {
        len++;
        pStr++;
    }

    const Sint32 memSize = (len + 1 ) * 4;
    char* pBuf = new char[memSize];

    char* pWork = pBuf;
    for( const Uint16* inStr = _pStr ; *inStr != 0 ; inStr++ )
    {
        Uint16 code = *inStr;

        if( code < 0x80 )
        {
            *pWork++ = code & 0xFF;
        }
        else
        {
            if( code < 0x800 )
            {
                *pWork++ = ( (( code >> 6 ) & 0x1f ) | 0xC0 );
            }
            else
            {
                *pWork++ = ( ( code >> 12 ) | 0xE0 );
                *pWork++ = ( (( code >> 6 ) & 0x3f ) | 0x80 );
            }
            *pWork++ = ( ( code & 0x3f ) | 0x80 );
        }
    }
    *pWork = 0;
    mTempString = pBuf;
    delete[] pBuf;

    return mTempString.c_str();
}



const char* CString::_WideToUtf8( const wchar_t * str )
{
#ifdef WCHAR_MAX
	#if WCHAR_MAX <= 0xffff 
		return Utf16ToUtf8( reinterpret_cast< const Uint16 * >( str ) );
	#else
		//return UTF32ToUTF8( reinterpret_cast< const Uint32 * >( str ) );
	#endif
#else
	if( sizeof( wchar_t ) == 2 ){
		return Utf16ToUtf8( reinterpret_cast< const Uint16 * >( str ) );
	} else {
		//return UTF32ToUTF8( reinterpret_cast< const Uint32 * >( str ) );
	}
#endif
}


//  Wide To Utf8
const char* CString::WideToUtf8( const wchar_t* _str )
{

	std::map< const wchar_t *, const char * >::iterator fi = ConvMap.find( _str );
	const char * result = NULL;
	if( fi == ConvMap.end() )
    {
		const char * utf8 = _WideToUtf8( _str );
		Uint32 len = static_cast< Uint32 >( strlen( utf8 ) );
		char* pBuf = new char[ len+1 ];
        memcpy( pBuf , utf8 , len+1 );

		result = pBuf;
		ConvMap[ _str ] = result;
	}
    else
    {
		result = fi->second;
	}
    return result;
}




//	文字列置換
string CString::Replace(const string& _src, const string& _dst, const string& _exchange)
{
	string result = _src;
	std::string::size_type  Pos(result.find(_dst));
	while (Pos != std::string::npos)
	{
		result.replace(Pos, _dst.length(), _exchange);
		Pos = result.find(_dst, Pos + _exchange.length());
	}
	return result;
}


//	文字列の分解
const Sint32 CString::Split(CDataMap& _result, const string& _src, const string& _delimita)
{
	_result.Initialize();
	string::size_type pos = 0;
	while (1) {
		string::size_type findPos = _src.find(_delimita, pos);
		if (findPos == string::npos)
		{
			_result.Add(_result.Count(), _src.substr(pos).c_str());
			break;
		}
		_result.Add(_result.Count(), _src.substr(pos, findPos - pos).c_str());
		pos = findPos + _delimita.size();
	}
	return _result.Count();
}



#include "LibString.h"
#include "LibFile.h"""

#include <fstream>

int main( int _argc , const char* _argv[] )
{
    //	printf( _argv[1] );
    //	printf( "\n" );
	//	
    //	printf( utf8("%s\n") , _argv[1] );
    //	printf( utf8("test_%d \n") , 999 );

    string pathBase = "_debug/";
    CStringList newList;
    newList.Add( "doc_SJIS_CRLF.txt" );
    newList.Add( "doc_UTF8_CRLF.txt" );
    newList.Add( "doc_UTF8_CRLF_bom.txt" );

    CStringList::Ite Ite = newList.begin();
    for( ; Ite != newList.end() ; Ite++ )
    {
        string pathReadFile = pathBase;
               pathReadFile += Ite->c_str();

		CFile tempFile;
		if (tempFile.Load(pathReadFile.c_str()))
		{
			tempFile.Dump();
			tempFile.Finalize();
		}
		

        //FILE* pSjis = fopen( pathReadFile.c_str() , "rb");
        //if( pSjis )
        //{
        //    fseek( pSjis , 0 , SEEK_END );
        //    const Sint32 fSize = ftell( pSjis );
        //    fseek( pSjis , 0 , SEEK_SET );

        //    char* pBuf = new char[fSize];
        //    memset( pBuf , 0x00 , fSize );
        //    fread( pBuf , fSize , 1 , pSjis );

        //    {
        //        Uint8* pDump = reinterpret_cast<Uint8*>(pBuf);
        //        for(Sint32 i=0; i<fSize ; i++ , pDump++ )
        //        {
        //            if( (*pDump) == 0x00 ){
        //                break;
        //            }

        //            printf( utf8("%02x ") , (*pDump) );
        //            if( ( (i+1) % 32 ) == 0 )
        //            {
        //                printf( utf8("\n") );
        //            }
        //        }
        //        printf( utf8("\n\n") );
        //    }

        //    //printf( pBuf );

        //    string outfile = pathBase;
        //    outfile += "output/";
        //    outfile += Ite->c_str();

        //    ofstream fStream( outfile.c_str() );
        //    if( fStream.is_open() )
        //    {
        //        fStream.write( pBuf , fSize );
        //        fStream.close();
        //    }
        //    delete[] pBuf;
        //}
    }
    return 0;
};
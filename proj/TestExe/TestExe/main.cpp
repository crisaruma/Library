

#include "LibString.h"
#include "LibFileCsv.h"

#include <fstream>

int main( int _argc , const char* _argv[] )
{
    string pathBase = "_debug/";

    {
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

                string pathWriteFile = pathBase + utf8("output/") + Ite->c_str();
                tempFile.Save( pathWriteFile.c_str() );

			    tempFile.Finalize();
		    }
        }
    }

    {
        CStringList newList;
        newList.Add( "csv_test.csv" );

        CStringList::Ite Ite = newList.begin();
        for( ; Ite != newList.end() ; Ite++ )
        {
            string pathReadFile = pathBase;
                   pathReadFile += Ite->c_str();

		    CFileCsv tempFile;
		    if (tempFile.Load(pathReadFile.c_str()))
		    {
			    tempFile.Dump();

                string pathWriteFile = pathBase + utf8("output/") + Ite->c_str();
                tempFile.Save( pathWriteFile.c_str() );

			    tempFile.Finalize();
		    }
        }
    }

    return 0;
};
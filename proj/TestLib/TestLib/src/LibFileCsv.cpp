
#include "LibFileCsv.h"


CFileCsv::CFileCsv()
: CFile()
, mTable()
{
}


CFileCsv::~CFileCsv()
{
    this->Finalize();
}

void CFileCsv::Initialize(void)
{
    CFile::Initialize();
    mTable.Initialize();
}


void CFileCsv::Finalize(void)
{
    CFile::Finalize();
    mTable.Finalize();
}


const Sint32 CFileCsv::Load(const char* _pathFile)
{
    if( CFile::Load( _pathFile ) == 0 ){
        return 0;
    }

    mTable.Initialize();

    string src = static_cast<char*>(mBuff);

    CDataMap tempMap;
    src = CString::Replace( src , "\r\n" , "\n" ); 
    src = CString::Replace( src , "\r"   , "\n" ); 
    CString::Split( tempMap , src , "\n" );

    CDataMap::Ite ite = tempMap.begin();
    for( ; ite != tempMap.end() ; ite++ )
    {
        CTable::CRecord* pRecord = mTable.CreateRecord();
        if( !pRecord )
        {
            continue;
        }
        pRecord->Assign( ite->second.GetAsStr() );
    }
    return 1;
}


//  
void CFileCsv::Dump(void)
{
    for( mTable.First() ; !mTable.IsEof() ; mTable.Next() )
    {
        CTable::CRecord* pRecord = mTable.GetRecord();
        string newLine;
        CDataMap::Ite itePrm = pRecord->begin();
        for( ; itePrm != pRecord->end() ; itePrm++ ){
            if( itePrm != pRecord->begin() ){
                newLine += ",";
            }
            newLine += itePrm->second.GetAsStr();
        }
        newLine += "\n";
        printf( newLine.c_str() );
    }
}

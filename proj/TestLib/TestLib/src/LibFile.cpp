
#include "LibString.h"
#include "LibFile.h"
#include <fstream>



CFile::CFile()
: mBuff(NULL)
, mSize(0)
{
}


CFile::~CFile()
{
	this->Finalize();
}


void CFile::Initialize(void)
{
	mBuff = NULL;
	mSize = 0;
}


void CFile::Finalize(void)
{
	this->UnLoad();
}


void CFile::UnLoad(void)
{
	if (mBuff) {
		delete[] mBuff;
	}
	mBuff = NULL;
	mSize = 0;
}


const Sint32 CFile::Load(const char* _pathFile)
{
	this->UnLoad();

	ifstream input(_pathFile , fstream::binary );
	if (!input.is_open()) 
	{
		return 0;
	}

	input.seekg(0, fstream::end);
	mSize = input.tellg();

	input.clear();
	input.seekg(0, fstream::beg);

	//	バッファ確保
	mBuff = static_cast<void*>(new char[mSize+1]);
	char* pBuf = static_cast<char*>(mBuff);
	memset(mBuff, 0x00, mSize+1);

	//	読み込み
	input.read(pBuf, mSize);

	input.close();
	return mSize;
}


//  
const Sint32 CFile::Save(const char* _pathFile)
{
	ofstream output(_pathFile , fstream::binary );
	if (!output.is_open()) 
	{
		return 0;
	}

	output.write( static_cast<char*>(mBuff) , mSize );
	output.close();
    return mSize;
}



//	
void CFile::Dump(void)
{
	Uint8* pDump = reinterpret_cast<Uint8*>(mBuff);
	for (Sint32 i = 0; i<mSize; i++, pDump++)
	{
		if ((*pDump) == 0x00) {
			break;
		}

		printf(utf8("%02x "), (*pDump));
		if (((i + 1) % 32) == 0)
		{
			printf(utf8("\n"));
		}
	}
	printf(utf8("\n\n"));

}









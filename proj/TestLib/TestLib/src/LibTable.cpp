#include "LibTable.h"



//==============================================================================
//
//  フィールドラベル
//
//==============================================================================
CTable::CLabel::CLabel()
: mIndex()
, mName()
{
}

CTable::CLabel::~CLabel()
{
    this->Finalize();
}


void CTable::CLabel::Initialize(void)
{
    mIndex.Initialize();
    mName.Initialize();
}


void CTable::CLabel::Finalize(void)
{
    mIndex.Finalize();
    mName.Finalize();
}


bool CTable::CLabel::Assign( const char* _pCsvLine )
{
    CDataMap temp;
	const Sint32 numPrm = CString::Split( temp, _pCsvLine, ",");
	if (numPrm <= 0) {
		return false;
	}

    CDataMap::Ite Ite = temp.begin();
    for( ; Ite != temp.end() ; Ite++ )
    {
        this->Add( Ite->second.GetAsStr() );
    }
	return true;
}


void CTable::CLabel::Add( const char* _nameField )
{
    const Uint32 hashKey = CHash::CRC32( _nameField );
    const Sint32 fldIndex = mIndex.Count();
    mIndex.Add( hashKey , fldIndex );
    mName.Add( fldIndex , _nameField );
}


const Sint32 CTable::CLabel::Count(void)
{
    return mIndex.Count();
}


const Sint32 CTable::CLabel::Get( const Uint32& _nameHashField ) const 
{
    const Sint32* pIndex = mIndex.Search( _nameHashField ); 
    if( !pIndex ){
        return -1;
    }
    return *pIndex;
}


const Sint32 CTable::CLabel::Get( const char* _nameField ) const 
{
    return this->Get( CHash::CRC32( _nameField ) );
}


const char* CTable::CLabel::GetName( const Sint32& _fldIndex )
{
    string* pName = mName.Search( _fldIndex );
    if( !pName ){
        return NULL;
    }
    return pName->c_str();
}







//==============================================================================
//
//  テーブルレコード
//
//==============================================================================
CTable::CRecord::CRecord()
: mParam()
{
}


CTable::CRecord::CRecord(const char* _pCsvLine)
: mParam()
{
    Assign( _pCsvLine );
}


CTable::CRecord::~CRecord()
{
    Finalize();
}


void CTable::CRecord::Initialize(void)
{
    mParam.Initialize();
}


void CTable::CRecord::Finalize(void)
{
    mParam.Finalize();
}

//  レコードのアサイン
bool CTable::CRecord::Assign( const char* _pCsvLine )
{
	const Sint32 numPrm = CString::Split( mParam, _pCsvLine, ",");
	if (numPrm <= 0) {
		return false;
	}
	return true;
}


//  パラメータを新規フィールドとして追加
void CTable::CRecord::Add(const CData& _param)
{
    mParam.Add( mParam.Count() , _param );
}

//  フィールドにパラメータを設定
void CTable::CRecord::Set(const Sint32& _index , const CData& _param )
{
    CData* pParam = mParam.Get( mParam.Count() );
    if( pParam ){
        *pParam = _param;
        return ;
    }
    mParam.Add( _index , _param );
}

//  フィールドの取得
CData* CTable::CRecord::Get(const Sint32& _index )
{
    return mParam.Get(_index);
}


const CData* CTable::CRecord::Get(const Sint32& _index ) const 
{
    return mParam.Get(_index);
}



//==============================================================================
//
//  テーブルクラス
//
//==============================================================================
CTable::CTable()
: mLabel()
, mTable()
, mCurrent()
{
}

CTable::~CTable()
{
    this->Finalize();
}


void CTable::Initialize(void)
{
    mLabel.Initialize();
    mTable.Initialize();
    mCurrent = CRecordList::Ite();
}


void CTable::Finalize(void)
{
    mLabel.Finalize();
    mTable.Finalize();
    mCurrent = CRecordList::Ite();
}


//  ラベルの設定
void CTable::SetLabel( const CLabel& _label )
{
    mLabel = _label;
}


//  ラベルの追加
void CTable::AddLabel( const char* _fldName )
{
    mLabel.Add( _fldName );
}



void CTable::AddRecord( CRecord& _record )
{
    mTable.Add( mTable.Count() , _record );
}


//  
bool CTable::RemoveRecord( const Sint32& _recordIndex )
{
    if( !mTable.Remove( _recordIndex ) ){
        return false;
    }

    CRecordList tmpTable = mTable;
    mTable.Initialize();
    CRecordList::Ite ite = tmpTable.begin();
    for( ; ite != tmpTable.end() ; ite++ ){
        mTable.Add( mTable.Count() , ite->second );
    }
    return true;
}


bool CTable::MoveRecord( const Sint32& _recordIndex )
{
    CRecordList::Ite ite = mTable.find(_recordIndex);
    if( ite == mTable.end() ){
        return false;
    }
    mCurrent = ite;
    return true;
}


//  レコードを先頭に合わせる
bool CTable::First(void){
    mCurrent = mTable.begin();
}


bool CTable::IsEof(void) const {
    if( mCurrent == mTable.end() )
    {
        return false;
    }
    return true;
}

bool CTable::Next(void){
    if( !IsEof() )
    {
        mCurrent++;
        return true;
    }
    return false;
}


const Sint32 CTable::Count(void) const 
{
    return mTable.Count();
}


CTable::CRecord* CTable::GetRecord(const Sint32& _recordIndex )
{
    if( _recordIndex < 0 ){
        if( IsEof() ){
            return NULL;
        }
        return &(mCurrent->second);
    }
    return mTable.Search(_recordIndex);
}


const CTable::CRecord* CTable::GetRecord(const Sint32& _recordIndex ) const 
{
    if( _recordIndex < 0 ){
        if( IsEof() ){
            return NULL;
        }
        return &(mCurrent->second);
    }
    return mTable.Search(_recordIndex);
}


//  フィールドインデックスを取得する
const Sint32 CTable::GetFieldIndex( const char* _fldName ) const 
{
    return mLabel.Get( _fldName );   
}



//  指定レコードのフィールド名を指定してパラメータを取得
CData* CTable::GetFieldParam( const char* _nameField , CRecord* _pRecord )
{
    if( !_pRecord )
    {
        return NULL;
    }
    const Sint32 fldIndex = this->GetFieldIndex( _nameField );
    if( fldIndex < 0 )
    {
        return NULL;
    }
    return _pRecord->Get( fldIndex );
}

const CData* CTable::GetFieldParam( const char* _nameField , const CRecord* _pRecord) const 
{
    if( !_pRecord )
    {
        return NULL;
    }
    const Sint32 fldIndex = this->GetFieldIndex( _nameField );
    if( fldIndex < 0 )
    {
        return NULL;
    }
    return _pRecord->Get( fldIndex );
}



//  カレントレコードのフィールド名を指定してパラメータを取得
CData* CTable::GetFieldParam( const char* _nameField ){
    return this->GetFieldParam( _nameField , this->GetRecord() );
}


const CData* CTable::GetFieldParam( const char* _nameField ) const {
    return this->GetFieldParam( _nameField , this->GetRecord() );
}




//CTable::CTable()
//: mIndex()
//, mLabel()
//, mTable()
//, mCurrent()
//{
//}
//
//CTable::~CTable()
//{
//	Finalize();
//}
//
//void CTable::Initialize(void)
//{
//	mIndex.Initialize();
//	mLabel.Initialize();
//
//	mTable.Initialize();
//	mCurrent = CRecordList::Ite();
//}
//
//
//void CTable::Finalize(void)
//{
//	mIndex.Finalize();
//	mLabel.Finalize();
//
//	mTable.Finalize();
//	mCurrent = CRecordList::Ite();
//}
//
//void CTable::AssignIndex(const char* _pCSV)
//{
//	mIndex.Initialize();
//
//	CDataMap tempMap;
//	CString::Split(tempMap, _pCSV, ",");
//	CDataMap::CIte ItePrm = tempMap.begin();
//	for (; ItePrm != tempMap.end(); ItePrm++) 
//	{
//		mIndex.Add(CHash::CRC32(ItePrm->second.GetAsStr()), ItePrm->first );
//	}
//}
//
//
//
////	
//bool CTable::LoadCsv(const char* _path)
//{
//	FILE* fp = NULL;
//	errno_t error = fopen_s( &fp,_path, "rb");
//	if (error) {
//		return false;
//	}
//	if (!fp) {
//		return false;
//	}
//
//	fseek(fp, 0, SEEK_END);
//	Sint32 fileSize = ftell(fp);
//	fseek(fp, 0, SEEK_SET);
//
//	void* pPtr = malloc(fileSize);
//	if (pPtr)
//	{
//		fread(pPtr, fileSize, 1, fp);
//
//		const char* pFile = reinterpret_cast<const char*>(pPtr);
//
//		CString::Replace(pFile, "\r", "\n");
//
//		CDataMap tempFile;
//		CString::Split(tempFile, pFile, "\n");
//		free(pPtr);
//
//		CDataMap::CIte IteRec = tempFile.begin();
//		for (; IteRec != tempFile.end(); IteRec++)
//		{
//			AssignRecord(IteRec->second.GetAsStr());
//		}
//	}
//	fclose(fp);
//
//	return true;
//}
//
//
//void CTable::AssignRecord(const char* _pCSV)
//{
//	if (mIndex.Count() <= 0) 
//	{
//		mLabel.Assign(_pCSV);
//		return AssignIndex(_pCSV );
//	}
//
//	CRecord* pNewRecord = mTable.Add(mTable.Count(), CRecord());
//	if (pNewRecord) 
//	{
//		pNewRecord->Assign(_pCSV);
//	}
//}
//
//
////	
//void CTable::Dump(void) 
//{
//	{//	パラメータの印刷
//		CRecordList::CIte IteRec = mTable.begin();
//		for (; IteRec != mTable.end(); IteRec++) 
//		{
//			CMapS32::CIte IteIndex = mIndex.begin();
//			for (; IteIndex != mIndex.end(); IteIndex++)
//			{
//				const CData* pLabel = mLabel.GetField(IteIndex->second);
//				const CData* pParam = IteRec->second.GetField(IteIndex->second);
//				if (!pParam) 
//				{
//					continue;
//				}
//
//				string lineText;
//				lineText += pLabel->GetAsStr();
//				lineText += ":";
//				lineText += pParam->GetAsStr();
//				lineText += "\n";
//				printf(utf8("%s"), lineText.c_str());
//				//OutputDebugStringA(lineText.c_str());
//			}
//		}
//	}
//}
//
//
//void CTable::First(void){
//	mCurrent = mTable.begin();
//}
//
//void CTable::Next(void) {
//	mCurrent++;
//}
//
//
//bool CTable::IsEof(void) const {
//	if (mCurrent == mTable.end()) {
//		return true;
//	}
//	return false;
//}
//
//
////	
//const Sint32 CTable::GetFieldIndex(const char* _pFieldName){
//	const Sint32* pIndex = mIndex.Search(CHash::CRC32(_pFieldName));
//	if (!pIndex) {
//		return -1;
//	}
//	return (*pIndex);
//}
//
////	フィールドのラベルを取得する
//const char* CTable::GetFieldName(const Sint32& _FieldIndex ) {
//	const CData* pData = mLabel.GetField(_FieldIndex); 
//	if (!pData) {
//		return NULL;
//	}
//	return pData->GetAsStr();
//}
//
//
////	最後尾に新規レコードを作成する
//CTable::CRecord* CTable::CreateRecord(void) 
//{
//	const Sint32 newIndex = mTable.Count();
//	CRecord* pRecord = mTable.Search(newIndex);
//	if (!pRecord) {
//		return NULL;
//	}
//
//	
//	CMapS32::Ite IteIndex = mIndex.begin();
//	for (; IteIndex != mIndex.end(); IteIndex++) 
//	{
//		pRecord->AddParam( (Sint32)(0) );
//	}
//	mCurrent = mTable.find(newIndex);
//	return pRecord;
//}
//
//
//CTable::CRecord* CTable::GetRecord(void)
//{
//	if (IsEof()) {
//		return NULL;
//	}
//	return &(mCurrent->second);
//}
//
//const CTable::CRecord* CTable::GetRecord(void) const
//{
//	if (IsEof()) {
//		return NULL;
//	}
//	return &(mCurrent->second);
//}
//
//
////	
//const bool CTable::AddParam(const char* _pFieldName, const CData& _dat) 
//{
//	const Sint32 hashKey = CHash::CRC32(_pFieldName);
//	Sint32* pIndex = mIndex.Search(hashKey);
//	if (!pIndex) 
//	{//	レコードを作成する
//		const Sint32 newFldIndex = mLabel.count();
//
//		mLabel.AddParam(_pFieldName);		//	カラム名を追加
//		mIndex.Add(hashKey, newFldIndex);	//	追加したフィールドインデックスを取得
//		pIndex = mIndex.Search(hashKey);	//	追加したフィールドを検索
//	}
//	return this->SetParam(*pIndex, _dat);
//}
//
//
////	フィールドパラメータの設定
//const bool CTable::SetParam(const char* _pFieldName, const CData& _dat)
//{
//	const Sint32* pIndex = mIndex.Search(CHash::CRC32(_pFieldName));
//	if (!pIndex) {
//		return NULL;
//	}
//	return this->SetParam(*pIndex,_dat);
//}
//
//const bool CTable::SetParam(const Sint32& _FieldIndex, const CData& _dat)
//{
//	if (IsEof()) {
//		return false;
//	}
//	CData* pDat = mCurrent->second.GetField(_FieldIndex);
//	if (!pDat) {
//		return false;
//	}
//	*pDat = _dat;
//	return true;
//}
//
//const CData* CTable::GetParam(const char* _pFieldName)
//{
//	const Sint32* pIndex = mIndex.Search( CHash::CRC32(_pFieldName));
//	if (!pIndex) {
//		return NULL;
//	}
//	return this->GetParam(*pIndex);
//}
//
//const CData* CTable::GetParam(const Sint32& _FieldIndex)
//{
//	if (IsEof()) {
//		return NULL;
//	}
//	return mCurrent->second.GetField(_FieldIndex);
//}
//
//
//
////	自身のテーブルに渡されたテーブルを取り込む
//bool CTable::DoIntegration(CTable* _pTbl)
//{
//	const CRecord& fldTable = _pTbl->GetFieldTable();
//	const CDataMap& labelPrm = fldTable.GetParam();
//
//	for (_pTbl->First(); !_pTbl->IsEof(); _pTbl->Next())
//	{
//		CTable::CRecord* pRecord = _pTbl->GetRecord();
//		this->CreateRecord();
//
//		CDataMap::CIte IteLabel = labelPrm.begin();
//		for (; IteLabel != labelPrm.end(); IteLabel++)
//		{
//			const Sint32 fldIndexSrc = IteLabel->first;
//			const char* fldNameSrc = IteLabel->second.GetAsStr();
//			const CData* pFldItem = pRecord->GetField(fldIndexSrc);
//			if (!pFldItem) {
//				continue;
//			}
//			this->AddParam(fldNameSrc , *pFldItem );
//		}
//	}
//
//	return true;
//}
//
//
////	渡されたテーブルに自信のテーブルを統合する
//bool CTable::DoClone(CTable* _pTbl)
//{
//	const CRecord& fldTable = this->GetFieldTable();
//	const CDataMap& labelPrm = fldTable.GetParam();
//
//	for (this->First(); !this->IsEof(); this->Next())
//	{
//		CTable::CRecord* pRecord = this->GetRecord();
//		_pTbl->CreateRecord();
//
//		CDataMap::CIte IteLabel = labelPrm.begin();
//		for (; IteLabel != labelPrm.end(); IteLabel++)
//		{
//			const Sint32 fldIndexSrc = IteLabel->first;
//			const char* fldNameSrc = IteLabel->second.GetAsStr();
//			const CData* pFldItem = pRecord->GetField(fldIndexSrc);
//			if (!pFldItem) {
//				continue;
//			}
//			_pTbl->AddParam(fldNameSrc, *pFldItem);
//		}
//	}
//	return true;
//}
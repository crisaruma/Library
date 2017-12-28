

#ifndef __LIB_TABLE_H__
#define __LIB_TABLE_H__


#include "LibString.h"
#include "LibHash.h"


namespace CLib
{

	//===================================================
	//	CTable
	//===================================================
	class CTable
	{
	public:
		//	1件のレコード情報
		class CRecord {
			public:
			protected:
				CDataMap	mParam;

			public:
				CRecord();
				~CRecord();

				void Initialize(void);
				void Finalize(void);

				void AddParam(const CData& _param);
				void SetParam(const Sint32& _index , const CData& _param);

				bool Assign(const char* _pCsv);

				CData* GetField(const Sint32& _index);
				const CData* GetField(const Sint32& _index) const ;

				inline const Sint32 count(void) { return mParam.Count(); }

				inline CDataMap& GetParam(void) { return mParam; }
				inline const CDataMap& GetParam(void) const { return mParam; }
		};


		typedef CMap<Sint32, CRecord>	CRecordList;


	protected:
		CMapS32				mIndex;
		CRecord				mLabel;

		CRecordList			mTable;
		CRecordList::Ite	mCurrent;

	public:
		CTable();
		virtual ~CTable();

		virtual void Initialize(void);
		virtual void Finalize(void);

		virtual bool LoadCsv(const char* _path);

		virtual void AssignIndex(const char* _pCSV);
		virtual void AssignRecord(const char* _pCSV);

		virtual void Dump(void);

		virtual void First(void);
		virtual void Next(void);
		virtual bool IsEof(void) const ;

		const Sint32 GetFieldIndex(const char* _pFieldName);
		const char* GetFieldName(const Sint32& _FieldIndex);
		const CRecord& GetFieldTable(void) { return mLabel;  }

		CRecord* CreateRecord(void);
		CRecord* GetRecord(void);
		const CRecord* GetRecord(void) const;

		const bool AddLabel(const char* _pFieldName);
		const bool AddParam(const char* _pFieldName, const CData& _dat);

		//	
		const bool SetParam(const char* _pFieldName, const CData& _dat);
		const bool SetParam(const Sint32& _FieldIndex , const CData& _dat);

		const CData* GetParam(const char* _pFieldName);
		const CData* GetParam(const Sint32& _FieldIndex);

		//	自身のテーブルに渡されたテーブルを取り込む
		virtual bool DoIntegration(CTable* _pTbl);

		//	渡されたテーブルに自信のテーブルを統合する
		virtual bool DoClone(CTable* _pTbl);

	};

};


#endif
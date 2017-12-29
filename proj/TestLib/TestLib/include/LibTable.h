

#ifndef __LIB_TABLE_H__
#define __LIB_TABLE_H__


#include "LibString.h"
#include "LibHash.h"


namespace CLib
{
    typedef CMap<Sint32,string> CFieldTable;

    class CTable
    {
        public:
            //  �t�B�[���h���x��
            class CLabel{
                public:
                protected:
                    CMapS32     mIndex; // nameHashField , indexField 
                    CFieldTable mName;  // indexField    , nameField

                public:
                    CLabel();
                    ~CLabel();

                    void Initialize(void);
                    void Finalize(void);

                    bool Assign( const char* _pCsvLine );

                    void Add( const char* _nameField );

                    const Sint32 Count(void);

                    const Sint32 Get( const Uint32& _nameHashField ) const ;
                    const Sint32 Get( const char* _nameField ) const ;

                    const char* GetName( const Sint32& _fldIndex );

                    CFieldTable::Ite begin(void){ return mName.begin(); }
                    CFieldTable::Ite end(void){ return mName.end(); }

                    CFieldTable::CIte begin(void) const { return mName.begin(); }
                    CFieldTable::CIte end(void) const { return mName.end(); }

            };

            //  ���R�[�h
            class CRecord{
                public:
                protected:
                    CDataMap    mParam;

                public:
                    CRecord();
                    CRecord(const char* _pCsvLine);
                    ~CRecord();

                    void Initialize(void);
                    void Finalize(void);

                    //  ���R�[�h�̃A�T�C��
                    bool Assign( const char* _pCsvLine );

                    //  �p�����[�^��V�K�t�B�[���h�Ƃ��Ēǉ�
                    void Add(const CData& _param);

                    //  �t�B�[���h�Ƀp�����[�^��ݒ�
                    void Set(const Sint32& _index , const CData& _param );

                    //  �t�B�[���h�̎擾
                    CData* Get(const Sint32& _index );
                    const CData* Get(const Sint32& _index ) const ;

                    CDataMap& GetRecord(void){ return mParam; }
                    const CDataMap& GetRecord(void) const { return mParam; }

                    CDataMap::Ite begin(void){ return mParam.begin(); }
                    CDataMap::Ite end(void){ return mParam.end(); }

                    CDataMap::CIte begin(void) const { return mParam.begin(); }
                    CDataMap::CIte end(void) const { return mParam.end(); }

            };
            typedef CMap<Sint32,CRecord>    CRecordList;


        protected:
            CLabel              mLabel;     //  CSV���x���ƃt�B�[���h�C���f�b�N�X�̃}�b�v
            CRecordList         mTable;     //  ���R�[�h�̃��X�g(�e�[�u��)
            CRecordList::Ite    mCurrent;   //  �J�����g���R�[�h

        public:
            CTable();
            virtual ~CTable();

            virtual void Initialize(void);
            virtual void Finalize(void);

            //  ���x��
            void SetLabel( const CLabel& _label );
            void AddLabel( const char* _fldName );
            CLabel& GetLabel(void){ return mLabel; }
            const CLabel& GetLabel(void) const { return mLabel; }

            //  ���R�[�h
            CRecord* CreateRecord(void);
            void AddRecord( CRecord& _record );
            bool RemoveRecord( const Sint32& _recordIndex );
            bool MoveRecord( const Sint32& _recordIndex );

            bool First(void);
            bool IsEof(void) const ;
            bool Next(void);

            const Sint32 Count(void) const ;

            CRecord* GetRecord(const Sint32& _recordIndex = -1);
            const CRecord* GetRecord(const Sint32& _recordIndex = -1) const ;

            //  �t�B�[���h�C���f�b�N�X���擾����
            const Sint32 GetFieldIndex( const char* _fldName ) const ;

            //  �w�背�R�[�h�̃t�B�[���h�����w�肵�ăp�����[�^���擾
            CData* GetFieldParam( const char* _nameField , CRecord* _pRecord );
            const CData* GetFieldParam( const char* _nameField , const CRecord* _pRecord ) const ;

            //  �J�����g���R�[�h�̃t�B�[���h�����w�肵�ăp�����[�^���擾
            CData* GetFieldParam( const char* _nameField );
            const CData* GetFieldParam( const char* _nameField ) const ;

    };

	////===================================================
	////	CTable
	////===================================================
	//class CTable
	//{
	//public:
	//	//	1���̃��R�[�h���
	//	class CRecord {
	//		public:
	//		protected:
	//			CDataMap	mParam;

	//		public:
	//			CRecord();
	//			~CRecord();

	//			void Initialize(void);
	//			void Finalize(void);

	//			void AddParam(const CData& _param);
	//			void SetParam(const Sint32& _index , const CData& _param);

	//			bool Assign(const char* _pCsv);

	//			CData* GetField(const Sint32& _index);
	//			const CData* GetField(const Sint32& _index) const ;

	//			inline const Sint32 count(void) { return mParam.Count(); }

	//			inline CDataMap& GetParam(void) { return mParam; }
	//			inline const CDataMap& GetParam(void) const { return mParam; }
	//	};


	//	typedef CMap<Sint32, CRecord>	CRecordList;


	//protected:
	//	CMapS32				mIndex;
	//	CRecord				mLabel;

	//	CRecordList			mTable;
	//	CRecordList::Ite	mCurrent;

	//public:
	//	CTable();
	//	virtual ~CTable();

	//	virtual void Initialize(void);
	//	virtual void Finalize(void);

	//	virtual bool LoadCsv(const char* _path);

	//	virtual void AssignIndex(const char* _pCSV);
	//	virtual void AssignRecord(const char* _pCSV);

	//	virtual void Dump(void);

	//	virtual void First(void);
	//	virtual void Next(void);
	//	virtual bool IsEof(void) const ;

	//	const Sint32 GetFieldIndex(const char* _pFieldName);
	//	const char* GetFieldName(const Sint32& _FieldIndex);
	//	const CRecord& GetFieldTable(void) { return mLabel;  }

	//	CRecord* CreateRecord(void);
	//	CRecord* GetRecord(void);
	//	const CRecord* GetRecord(void) const;

	//	const bool AddLabel(const char* _pFieldName);
	//	const bool AddParam(const char* _pFieldName, const CData& _dat);

	//	//	
	//	const bool SetParam(const char* _pFieldName, const CData& _dat);
	//	const bool SetParam(const Sint32& _FieldIndex , const CData& _dat);

	//	const CData* GetParam(const char* _pFieldName);
	//	const CData* GetParam(const Sint32& _FieldIndex);

	//	//	���g�̃e�[�u���ɓn���ꂽ�e�[�u������荞��
	//	virtual bool DoIntegration(CTable* _pTbl);

	//	//	�n���ꂽ�e�[�u���Ɏ��M�̃e�[�u���𓝍�����
	//	virtual bool DoClone(CTable* _pTbl);

	//};

};


#endif
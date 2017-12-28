

#ifndef __LIB_DATA_H__
#define __LIB_DATA_H__

#include "LibType.h"


namespace CLib
{
	//	汎用パラメータ
	class CData
	{
	public:
		enum Type
		{
			TypeInvalid = 0	,
			TypeSint32	= 1	,
			TypeFloat	= 2	,
			TypeDouble  = 3 ,
			TypeString	= 4	,
		};

	protected:
		Type	mType;
		Sint32	mInt;
		double	mFlt;
		string  mStr;
		static string mTempStr;

	public:
		CData();
		CData(const Sint32& _val );
		CData(const float& _val);
		CData(const double& _val);
		CData(const char* _pVal );

		void Initialize(void);
		void Finalize(void);

		const Type& GetType(void) const;

		void SetAsInt(const Sint32& _val);
		const Sint32 GetAsInt(void) const ;

		void SetAsFlt(const float& _val);
		const float GetAsFlt(void) const;

		void SetAsDbl(const double& _val);
		const double GetAsDbl(void) const;

		void SetAsStr(const char* _pVal);
		const char* GetAsStr(void) const ;

	};

	typedef CList<CData>			CDataList;

	typedef CMap<Sint32, CData>		CDataMap;
	typedef CMap<Sint32, CDataList>	CDataTable;

};


#endif
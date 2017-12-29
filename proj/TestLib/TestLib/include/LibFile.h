
#ifndef __LIB_FILE_H__
#define __LIB_FILE_H__

#include "LibType.h"


namespace CLib
{
    class CFile
    {
        public:

		protected:
			void*	mBuff;	//	
			Uint32	mSize;	//	

		public:
			CFile();
			virtual ~CFile();

			virtual void Initialize(void);
			virtual void Finalize(void);

			virtual void UnLoad(void);
			virtual const Sint32 Load(const char* _pathFile);
            virtual const Sint32 Save(const char* _pathFile);

			virtual void Dump(void);
    };

};



#endif

#ifndef __LIB_FILE_CSV_H__
#define __LIB_FILE_CSV_H__

#include "LibFile.h"
#include "LibTable.h"

namespace CLib
{
    class CFileCsv : public CFile
    {
        public:

		protected:
            CTable  mTable;

		public:
			CFileCsv();
			virtual ~CFileCsv();

			virtual void Initialize(void);
			virtual void Finalize(void);

			virtual const Sint32 Load(const char* _pathFile);

            virtual void Dump(void);
    };

};



#endif
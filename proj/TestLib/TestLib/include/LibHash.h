
#ifndef __LIB_HASH_H__
#define __LIB_HASH_H__

#include "LibType.h"


namespace CLib
{
    class CHash
    {
        public:
            static const Uint32 CRC32(const char* _pVal );
            static const Uint32 CRC32(const char* _pVal , const Uint32& _size );

        public:
            static const Uint32 mMask;
            static const Uint32 mTable[256];
    };

};



#endif
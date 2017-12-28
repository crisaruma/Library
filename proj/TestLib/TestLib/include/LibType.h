
#ifndef __LIB_TYPE_H__
#define __LIB_TYPE_H__

#include <vector>
#include <map>

using namespace std;

typedef char    Sint8;
typedef short   Sint16;
typedef long    Sint32;

typedef unsigned char   Uint8;
typedef unsigned short  Uint16;
typedef unsigned long   Uint32;

namespace CLib
{
    template <typename _Val>
    class CList
    {
    public:
        typedef vector<_Val>                          CType;
        typedef typename vector<_Val>::iterator       Ite;
        typedef typename vector<_Val>::const_iterator CIte;

    protected:
        CType   mList;

    public:
        CList()
        : mList()
        {
        };

        ~CList(){
            Finalize();
        }

        void Initialize(void){
            mList = CType();
        }

        void Finalize(void){
            mList = CType();
        }

        const Sint32 Count(void) const 
        {
            return mList.size(); 
        }

        const bool IsAmount(const Sint32& _index )
        {
            return (_index < Count()) ? true : false;
        }

        void Add(const _Val& _param )
        {
            mList.push_back(_param);
        }

        _Val Get(const Sint32& _index ){
            if( !IsAmount(_index) )
            {
                return _Val();
            }
            return mList[_index];
        }

        Ite begin(void){ return mList.begin(); }
        Ite end(void){ return mList.end(); }

        CIte begin(void) const { return mList.begin(); }
        CIte end(void) const { return mList.end(); }


    };

    typedef CList<Sint8>      CListS8;
    typedef CList<Sint16>     CListS16;
    typedef CList<Sint32>     CListS32;

    typedef CList<Uint8>      CListU8;
    typedef CList<Uint16>     CListU16;
    typedef CList<Uint32>     CListU32;


    //-----------------------------------------------
    template <typename _Key,typename _Val>
    class CMap
    {
    public:
        typedef map<_Key,_Val>                          CType;
        typedef typename map<_Key,_Val>::iterator       Ite;
        typedef typename map<_Key,_Val>::const_iterator CIte;
        typedef typename map<_Key,_Val>::value_type     CValue;

    protected:
        CType   mList;

    public:
        CMap()
        : mList()
        {
        };

        ~CMap(){
            Finalize();
        }

        void Initialize(void){
            mList = CType();
        }

        void Finalize(void){
            mList = CType();
        }

        const Sint32 Count(void) const 
        {
            return mList.size(); 
        }

        void Add(const _Key& _key , const _Val& _val )
        {
            mList.insert( CValue( _key , _val ) );
        }

        _Val* Search(const _Key& _key )
        {
            Ite ite = mList.find( _key );
            if( ite == mList.end() ){
                return NULL;
            }
            return &(ite->second);
        }

        const _Val* Search(const _Key& _key ) const 
        {
            CIte ite = mList.find( _key );
            if( ite == mList.end() ){
                return NULL;
            }
            return &(ite->second);
        }

        _Val* Get(const _Key& _key )
        {
            return Search(_key);
        }

        const _Val* Get(const _Key& _key ) const 
        {
            return Search(_key);
        }

        Ite begin(void){ return mList.begin(); }
        Ite end(void){ return mList.end(); }

        CIte begin(void) const { return mList.begin(); }
        CIte end(void) const { return mList.end(); }
    };

    typedef CMap<Sint32,Sint32>     CMapS32;



};



using namespace CLib;


#endif
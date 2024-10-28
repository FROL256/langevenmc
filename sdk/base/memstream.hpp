








#ifndef _KLDB_MEMSTREAM_HPP_
#define _KLDB_MEMSTREAM_HPP_

#include "xarray.hpp"
#include "bytestream.hpp"
#include "export.h"

KIAM_NAMESPACE_START


class MemStream : public ByteStream
  {
  public:
    
    
    
    INTAPI_BASE MemStream(bool imp);
    
    INTAPI_BASE MemStream(const MemStream &src);
    

  public:
    
    
    
    INTAPI_BASE virtual const BYTE *Data() = 0;
    
    INTAPI_BASE virtual SIZE_T Length() = 0;
    

    
    INTAPI_BASE virtual bool IsFile() const;

  };  



class ReadMemStream : public MemStream
  {
  public:
    
    
    
    INTAPI_BASE ReadMemStream(const BYTE *area, SIZE_T length);
    
    INTAPI_BASE ReadMemStream(const ReadMemStream &src);
    
    INTAPI_BASE virtual ~ReadMemStream();
    
    inline void operator =(const ReadMemStream &src);
    

  public:
    
    
    
    INTAPI_BASE virtual OKAY Open();
    
    INTAPI_BASE virtual OKAY Close();
    

  public:
    
    
    
    INTAPI_BASE virtual void Byte(void *ptr);
    
    INTAPI_BASE virtual void Bytes(void *ptr, SIZE_T len);
    
    INTAPI_BASE virtual bool EndOfStream();
    

  public:
    
    
    
    INTAPI_BASE virtual const BYTE *Data();
    
    INTAPI_BASE virtual SIZE_T Length();
    

  private:
    
    const BYTE *area;
    
    const SIZE_T length;
    
    SIZE_T cur;
  };  



class WriteMemStream : public MemStream
  {
  public:
    
    
    
    INTAPI_BASE WriteMemStream(SIZE_T block_size = 64000, SIZE_T initial_size = 64000);
    
    INTAPI_BASE WriteMemStream(const WriteMemStream &src);
    
    inline virtual ~WriteMemStream();
    

  public:
    
    
    
    INTAPI_BASE virtual OKAY Open();
    
    INTAPI_BASE virtual OKAY Close();
    

  public:
    
    
    
    INTAPI_BASE virtual void Byte(void *ptr);
    
    INTAPI_BASE virtual void Bytes(void *ptr, SIZE_T len);
    

  public:
    
    
    
    INTAPI_BASE virtual const BYTE *Data();
    
    INTAPI_BASE virtual SIZE_T Length();
    

  private:
    
    XArray<BYTE> area;
    
    SIZE_T cur;
  };  








void ReadMemStream::operator =(const ReadMemStream &src)
  {
  Assert(false);
  }






WriteMemStream::~WriteMemStream()
  {
  }

KIAM_NAMESPACE_END
#endif

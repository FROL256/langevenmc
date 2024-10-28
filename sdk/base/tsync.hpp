








#ifndef _ELMG_TSYNC_HPP_
#define _ELMG_TSYNC_HPP_

#include "export.h"
#include "garray.hpp"

KIAM_NAMESPACE_START



class TSync
  {
  public:
    
    
    
    INTAPI_BASE TSync();
    
    INTAPI_BASE virtual ~TSync();
    

  public:
    
    
    
    INTAPI_BASE void Mono();
    
    INTAPI_BASE void Multi();
    
    
    INTAPI_BASE bool TryMono();
    

  private:
    
    
    
    void operator =(const TSync &src);
    
    TSync(const TSync &src);
    

  private:
    
    void *handle;
  };  


class TAutoSync
  {
  public:
    
    
    
    INTAPI_BASE TAutoSync(TSync *tsync);
    
    INTAPI_BASE virtual ~TAutoSync();
    

  public:
    
    
    
    
    INTAPI_BASE void Mono();
    
    INTAPI_BASE void Multi();
    

  private:
    
    TSync *sync;
  };  


class TEvent
  {
  public:
    
    
    
    INTAPI_BASE TEvent();
    
    INTAPI_BASE virtual ~TEvent();
    

  public:
    
    
    
    INTAPI_BASE void Signal();
    
    INTAPI_BASE void Wait();
    

  private:
    
    
    
    INTAPI_BASE TEvent(const TEvent &src);
    

  private:
    
    void *event;

    
    friend class TEventSet;
  };  



class TEventSet
  {
  public:
    
    
    
    inline TEventSet();
    
    INTAPI_BASE TEventSet(const TEventSet &src);
    
    inline virtual ~TEventSet();
    

  public:
    
    
    
    INTAPI_BASE OKAY Add(TEvent &event);
    
    INTAPI_BASE OKAY Add(void *event);
    
    INTAPI_BASE void Remove(TEvent &event);
    
    INTAPI_BASE void Remove(void *event);
    
    INTAPI_BASE void Wait();
    

  private:
    
    GArray<void *> events;
  };  






TEventSet::TEventSet()
  {
  }



TEventSet::~TEventSet()
  {
  }

KIAM_NAMESPACE_END
#endif

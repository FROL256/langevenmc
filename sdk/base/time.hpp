









#ifndef _KLBC_TIME_HPP_
#define _KLBC_TIME_HPP_

#include "export.h"
#include "str.hpp"

KIAM_NAMESPACE_START


class Timer
  {
  public:
    
    
    
    INTAPI_BASE Timer();
    
    INTAPI_BASE Timer(const Timer &t);
    
    INTAPI_BASE ~Timer();
    

  public:
    
    
    
    INTAPI_BASE void Reset();
    
    INTAPI_BASE unsigned int Elapsed() const;
    
    INTAPI_BASE unsigned int Wait(unsigned int time) const;
    
    INTAPI_BASE Str TimeStamp(bool show_ms = false) const;
    

  private:
    
    static void GetTime(int &out_sec, int &out_msec);

    
    
    
    int sec;
    
    int msec;
    
  }; 


class Time
  {
  public:
    
    
    
    inline Time();
    
    inline Time(const unsigned t);
    
    INTAPI_BASE Time(const int year0, const int month0, const int day0,
                     const int hour0 = 0, const int min0 = 0,
                     const int sec0 = 0);
    
    INTAPI_BASE Time(const Time &lt);
    

  public:
    
    INTAPI_BASE static unsigned int Get();

  public:
    
    
    
    INTAPI_BASE bool IsCorrect() const;
    
    INTAPI_BASE bool SetFromSekisuiString(const Str &str);
    
    INTAPI_BASE Str DateStamp() const;
    
    INTAPI_BASE Str DateStampD() const;
    
    INTAPI_BASE Str TimeStamp() const;
    
    INTAPI_BASE Str DateTimeString() const;
    
    INTAPI_BASE operator unsigned () const;
    
    INTAPI_BASE void Set(const unsigned t);
    


  public:
    
    
    
    INTAPI_BASE bool operator == (const Time &tc) const;
    
    INTAPI_BASE bool operator != (const Time &tc) const;
    

  public:
    
    
    
    int year;
    
    int month;
    
    int day;
    
    int hour;
    
    int minute;
    
    int second;
    

  }; 



INTAPI_BASE void GetTicksNumber(INT64 *num);









Time::Time()
  {
  Set(Time::Get());
  }






Time::Time(const unsigned t)
  {
  Set(t);
  }

KIAM_NAMESPACE_END
#endif

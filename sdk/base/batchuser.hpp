








#ifndef _KLXX_BATCHUSER_HPP_
#define _KLXX_BATCHUSER_HPP_

#include <base/time.hpp>
#include <base/user.hpp>

#include "export.h"
#include "user.hpp"

KIAM_NAMESPACE_START


class BatchUser : public IUser
  {
  public:
    
    
    
    INTAPI_BASE BatchUser();
    
    INTAPI_BASE virtual ~BatchUser();
    

  protected:
    
    
    
    INTAPI_BASE virtual void ErrorMsg(const CHAR *msg);
    
    INTAPI_BASE virtual void WarningMsg(const CHAR *msg);
    
    INTAPI_BASE virtual void StatusMsg(const CHAR *msg);
    
    INTAPI_BASE virtual bool Ask(const CHAR *msg, ReplyStyle rs, bool def);
    INTAPI_BASE virtual int Information(const CHAR *msg, const CHAR *button0text = NULL,
      const CHAR *button1text = NULL, const CHAR *button2text = NULL,
      int def_button = 0, int esc_button = -1);
    
    INTAPI_BASE virtual void InitProgr(int level);
    
    INTAPI_BASE virtual void TermProgr(int level);
    
    INTAPI_BASE virtual void ShowProgr(double done, const CHAR *msg);
    
    INTAPI_BASE virtual void PrintMsg(const CHAR *msg);
    
    INTAPI_BASE virtual bool Break();
    

  }; 


INTAPI_BASE IUser *GetBatchUser();

KIAM_NAMESPACE_END

#endif


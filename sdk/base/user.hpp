








#ifndef _KLXX_USER_HPP_
#define _KLXX_USER_HPP_

#include "iarray.hpp"
#include "str.hpp"
#include "export.h"

KIAM_NAMESPACE_START
class Entity;


#if (_MSC_VER >= 1400) || defined(__linux)

#define ErrorMessage(x, ...) ErrorMessageEx(ExTr##x, x, ##__VA_ARGS__)

#define WarningMessage(x, ...) WarningMessageEx(ExTr##x, x, ##__VA_ARGS__)

#define StatusMessage(x, ...) StatusMessageEx(ExTr##x, x, ##__VA_ARGS__)

#define ExTr

#define ExTrTr(str, ...) FTr(str, ##__VA_ARGS__)

#define ExTrFTr(str, ...) FTr(str, ##__VA_ARGS__)

#define ExTrtr(str, ...) ftr(str, ##__VA_ARGS__)

#define ExTrftr(str, ...) ftr(str, ##__VA_ARGS__)
#else 

#define ErrorMessage(x) ErrorMessageEx(x, x)

#define WarningMessage(x) WarningMessageEx(x, x)

#define StatusMessage(x) StatusMessageEx(x, x)
#endif


class IUser
  {
  public:
    
    
    
    INTAPI_BASE IUser(unsigned active_progr_delay = 1000U);
    
    INTAPI_BASE virtual ~IUser();

  private:
    
    IUser(const IUser &);
    

  public:
    
    
    
    INTAPI_BASE OKAY ErrorMessageEx(const CHAR *format_notr, const CHAR *format, ...);
    
    INTAPI_BASE void WarningMessageEx(const CHAR *format_notr, const CHAR *format, ...);
    
    INTAPI_BASE void PostponeWarnings(bool postpone);
    
    INTAPI_BASE void StatusMessageEx(const CHAR *format_notr, const CHAR *format = NULL, ...);
    
    INTAPI_BASE void ClearStatusMessage();
    
    INTAPI_BASE void Printf(const char *format, ...);
    
    INTAPI_BASE virtual void NotifyAction(Entity *object, const Str &name);
    

  public:
    
    
    
    INTAPI_BASE void AskOK(const CHAR *format, ...);
    
    INTAPI_BASE bool AskOKCancel(const CHAR *format, ...);
    
    INTAPI_BASE bool AskYESNo(const CHAR *format, ...);
    
    INTAPI_BASE bool AskYesNO(const CHAR *format, ...);
    
    INTAPI_BASE virtual int Information(const CHAR *msg,
                const CHAR *button0text = NULL,
                const CHAR *button1text = NULL,
                const CHAR *button2text = NULL,
                int def_button = 0, int esc_button = -1);
    

  public:
    
    
    
    INTAPI_BASE OKAY ErrorNoMemory(INT64 amount = -1);
    
    INTAPI_BASE OKAY InternalError(const CHAR *format = NULL, ...);
    

  public:
    
    
    
    INTAPI_BASE virtual void InitProgress(bool stopable = false, bool busy_mode = false);
    
    INTAPI_BASE virtual void ShowProgress(double to_be_done, const CHAR *format, ...);
    
    INTAPI_BASE virtual void TermProgress();
    
    INTAPI_BASE bool InProgress() const;
    
    INTAPI_BASE bool GetProgressQuietMode();
    
    INTAPI_BASE void SetProgressQuietMode(bool quiet = false);
    
    INTAPI_BASE virtual void UseThreadControls(bool val);
    
    INTAPI_BASE void SetMultiProgress(bool val);
    
    INTAPI_BASE bool IsMultiProgress() const;
    
    INTAPI_BASE bool IsProgressStopable() const;
    

  protected:
    
    
    
    virtual void InitProgr(int level) = 0;
    
    virtual void ShowProgr(double done, const CHAR *msg) = 0;
    
    virtual void TermProgr(int level) = 0;
    

  protected:
    
    
    
    
    INTAPI_BASE int ProgrCount() const;
    
    INTAPI_BASE bool BusyMode() const;
    
    INTAPI_BASE const CHAR *GetProgressMsg(int level) const;
    
    INTAPI_BASE double GetProgressVal(int level) const;
    

  public:
    
    
    
    INTAPI_BASE virtual bool Break();
    
    INTAPI_BASE bool IsBreak() const;
    
    INTAPI_BASE virtual void SetBreak();
    
    INTAPI_BASE void ResetBreak();
    
    INTAPI_BASE void SetExit();
    
    INTAPI_BASE virtual void ProcessEvents();
    

  public:
    
    INTAPI_BASE virtual void SetTopmost(bool topmost);
    
    INTAPI_BASE virtual void SetEventFilterUsed(bool used);
    
    INTAPI_BASE virtual bool IsEventFilterUsed();
    
    INTAPI_BASE void SetCATIAMode(bool mode);
    
    INTAPI_BASE bool GetCATIAMode();


  public:
    
    INTAPI_BASE virtual Str NumberFormat(const char *number, int dec_num = 0);

  protected:
    
    enum ReplyStyle
      {
      
      RS_OK,
      
      RS_OKCANCEL,
      
      RS_YESNO
      };

  private:
    
    
    
    
    
    struct ProgrInfo
      {
      
      double p_left;
      
      double p_right;
      
      Str p_last_msg;
      
      unsigned p_next_time;
      
      bool p_busy_mode;
      
      bool p_inited;
      };

  private:
    
    enum { MAX_PROGRESS_LEVEL = 12 };

  protected:
    
    
    
    virtual void ErrorMsg(const CHAR *msg) = 0;
    
    virtual void WarningMsg(const CHAR *msg) = 0;
    
    virtual void StatusMsg(const CHAR *msg) = 0;
    
    virtual bool Ask(const CHAR *msg, ReplyStyle rs, bool def) = 0;
    
    virtual void PrintMsg(const CHAR *msg) = 0;
    

  public:
    
    INTAPI_BASE int StartScripting();
    
    INTAPI_BASE void FinishScripting(int progr_count);

  protected:
    
    INTAPI_BASE bool InScript();

  public:
    
    
    
    INTAPI_BASE static const char *GetIofSignature();
    
    INTAPI_BASE static void SetIofSignature(const char *signature);
    

  public:
    
    
    
    INTAPI_BASE static const char *GetApplVersion();
    
    INTAPI_BASE static void SetApplVersion(const char *version);
    

  public:
  public:
    
    INTAPI_BASE static unsigned SessionElapsed();

  public:
    
    
    
    INTAPI_BASE static const Str SessionTimeStamp(bool show_ms = false);
    

  public:
    
    
    
    INTAPI_BASE static void DisableQuickEdit();
    
    INTAPI_BASE static void RestoreQuickEdit();
    

  public:
    
    INTAPI_BASE virtual void InitProgressMT(bool stopable = false, bool busy_mode = false);
    
    INTAPI_BASE virtual void ShowProgressMT(double to_be_done, const CHAR *format, ...);
    
    INTAPI_BASE virtual void TermProgressMT();
    
    INTAPI_BASE virtual bool BreakMT();
    
    INTAPI_BASE virtual void SetBreakMT();
    
    INTAPI_BASE void ResetBreakMT();
    
    INTAPI_BASE void ShowLastProgressMT();

  protected:
    
    Str data_path;

  private:
    
    int m_progr_count;
    
    int m_active_progr_count;
    
    unsigned m_active_progr_delay;
    
    int m_script_count;
    
    bool m_progr_quiet;
    
    bool break_flag;
    
    bool m_exit_flag;
    
    ProgrInfo m_progr_info[MAX_PROGRESS_LEVEL];
    
    Str m_prev_progr_msg;
    
    bool m_multi_progr;
    
    bool m_stopable;
    
    bool m_postpone_warn;
    
    IArray *m_postponed_warn; 
    
    void *user_progr_thread_id;
    
    void *user_progr_thread_id_mt;
    
    double last_progr_value;
    
    Str last_progr_msg;
    
    double last_shown_progr_value;

  private:
    
    static Str s_iof_sign;
    
    static Str s_version_str;
    bool catia_mode;

  }; 





INTAPI_BASE void Debug(const char *format, ...);


INTAPI_BASE void SetUser(IUser *user);


INTAPI_BASE void SetThreadUser(IUser *user, void *id);


INTAPI_BASE IUser *User();



#define AssertLog(_Expression) (void)( (!!(_Expression)) || \
  (Assert(_Expression)))

KIAM_NAMESPACE_END

#endif


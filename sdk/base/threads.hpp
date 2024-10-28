















#ifndef _ELML_THREADS_HPP_
#define _ELML_THREADS_HPP_


#define INFINITE 0xFFFFFFFF

#include "export.h"

KIAM_NAMESPACE_START


INTAPI_BASE int NumberOfPhysicalCores();

INTAPI_BASE int NumberOfLogicalCores();






struct ThreadContext
  {
  
  int (*RunThread)(void *data);
  
  void *data_ptr;
  };



struct ThreadTiming
  {
  
  INT64 CreationTime;
  
  INT64 ExitTime;
  
  INT64 KernelTime;
  
  INT64 UserTime;
  };




INTAPI_BASE void *IntCreateThread(ThreadContext *cont, const char *name = NULL,
                                  int numa_node_id = -1);

INTAPI_BASE void IntCloseThread(void *handle);

INTAPI_BASE DWORD  IntResumeThread(void *handle);

INTAPI_BASE DWORD  IntSuspendThread(void *handle);

INTAPI_BASE void *IntGetCurrentThreadId();

INTAPI_BASE bool SetThreadPriorityAboveNormal(void *handle);

INTAPI_BASE bool SetThreadPriorityBelowNormal(void *handle);

INTAPI_BASE bool SetNormalThreadPriority(void *handle);

INTAPI_BASE int IntWaitForSingleThread(void const *lpHandle,
                                       DWORD dwMilliseconds);

INTAPI_BASE int IntWaitForMultipleThreads(DWORD nCount,
                                          void * const *lpHandles,
                                          bool fWaitAll, DWORD dwMilliseconds);

INTAPI_BASE bool IntGetThreadTimes(void *handle, ThreadTiming &times);





INTAPI_BASE void IntInitializeCriticalSection(void **crt, int sc = 0);

INTAPI_BASE void IntDeleteCriticalSection(void *crt);

INTAPI_BASE void IntEnterCriticalSection(void *crt);

INTAPI_BASE void IntLeaveCriticalSection(void *crt);





INTAPI_BASE void *IntCreateEvent();

INTAPI_BASE void *IntCreateEvent(bool manual_reset);

INTAPI_BASE void *IntCreateEvent(bool manual_reset, const char *name);

INTAPI_BASE void *IntOpenEvent(const char *name);

INTAPI_BASE void IntCloseEvent(void *h_event);

INTAPI_BASE bool IntResetEvent(void *h_event);

INTAPI_BASE bool IntSetEvent(void *h_event);

INTAPI_BASE int IntWaitForSingleEvent(void const *lpHandle,
                                      DWORD dwMilliseconds);

INTAPI_BASE int IntWaitForMultipleEvents(DWORD nCount,
                                         void * const *lpHandles,
                                         bool fWaitAll, DWORD dwMilliseconds);





INTAPI_BASE void *IntCreateFileMapping(const char *name, DWORD size);

INTAPI_BASE void *IntOpenFileMapping(const char *name);

INTAPI_BASE void IntCloseFileMapping(void *handle);

INTAPI_BASE void *IntMapViewOfFile(void *mapfile);

INTAPI_BASE bool IntUnmapViewOfFile(void *data_block);

INTAPI_BASE DWORD IntGetSharedMemBlockSize(void *data_block);





INTAPI_BASE void *IntSendMessage(HANDLE wnd, DWORD msg, void *data);

INTAPI_BASE bool IntSendNotifyMessage(HANDLE wnd, DWORD msg, void *data);


INTAPI_BASE bool IntSendMessageCallback(HANDLE wnd, DWORD msg, void *data,
                                        void *callback_proc, unsigned long callback_param);

INTAPI_BASE int GetUserMsgOffset();

INTAPI_BASE void *IntGetWndProc(HANDLE wnd);

INTAPI_BASE void *IntSetWndProc(HANDLE wnd, void *new_wnd_proc);

INTAPI_BASE void *IntCallWindowProc(void *old_wnd_proc,
                                        HANDLE wnd,
                                        DWORD msg,
                                        DWORD wParam,
                                        void *lParam);

INTAPI_BASE bool IntSetForegroundWindow(HANDLE hwnd);

INTAPI_BASE HANDLE IntGetForegroundWindow();

INTAPI_BASE void IntSetWndTopmost(HANDLE wnd, bool topmost);

INTAPI_BASE void IntShowWindow(HANDLE wnd, bool show);

INTAPI_BASE bool IntIsProcessRunning(DWORD pid);

INTAPI_BASE bool IntIsWindow(HANDLE wnd);

INTAPI_BASE bool IntIsWindowVisible(HANDLE wnd);

INTAPI_BASE bool IntEnableWindow(HANDLE wnd, bool enabled);

INTAPI_BASE HANDLE IntGetParent(HANDLE wnd);

INTAPI_BASE DWORD IntGetWindowPID(HANDLE wnd);

INTAPI_BASE DWORD IntGetCurrentProcessId();



INTAPI_BASE INT64 IntInterlockedOr64(INT64 &value, INT64 mask);

INTAPI_BASE INT64 IntInterlockedAnd64(INT64 &value, INT64 mask);

INTAPI_BASE INT64 IntInterlockedCompareExchange64(INT64 &value, INT64 new_value, INT64 comp_value);


INTAPI_BASE int IntInterlockedIncrement(int &value);

INTAPI_BASE int IntInterlockedIncrement(unsigned &value);

INTAPI_BASE INT64 IntInterlockedIncrement(INT64 &value);

INTAPI_BASE UINT64 IntInterlockedIncrement(UINT64 &value);


INTAPI_BASE int AtomicAdd(int &pd, int d); 

INTAPI_BASE unsigned AtomicAdd(unsigned &pd, unsigned d); 

INTAPI_BASE INT64 AtomicAdd(INT64 &pd, INT64 d); 

INTAPI_BASE UINT64 AtomicAdd(UINT64 &pd, UINT64 d); 

INTAPI_BASE float AtomicAdd(float &pd, float d); 

INTAPI_BASE double AtomicAdd(double &pd, double d); 

KIAM_NAMESPACE_END

#endif


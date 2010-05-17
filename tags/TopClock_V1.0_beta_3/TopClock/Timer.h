#ifndef __TIMER_H__
#define __TIMER_H__

#if _WIN32_WCE >= 0x501
#define TIME_NOTIFY_PATH	TEXT("\\System\\State\\DateTime\\")
#define TIME_NOTIFY_VALUE	TEXT("Time")
#else //_WIN32_WCE >= 0x501
#define TIMER_ID		1
#define TIMER_ELAPSE	500
#endif //_WIN32_WCE >= 0x501

void	CreateTimer(HWND hWnd);
void	DestroyTimer(HWND hWnd);

#endif //__TIMER_H__
#ifndef __TIMER_H__
#define __TIMER_H__

#define TIME_NOTIFY_PATH	TEXT("\\System\\State\\DateTime\\")
#define TIME_NOTIFY_VALUE	TEXT("Time")

void	CreateTimer(HWND hWnd);
void	DestroyTimer(HWND hWnd);

#endif //__TIMER_H__
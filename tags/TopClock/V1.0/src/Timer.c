#include <windows.h>

#include "../inc/Timer.h"

#include "../inc/Clock.h"

static void CALLBACK TimerProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
	UpdateClock(hWnd);
}

void CreateTimer(HWND hWnd)
{
	SetTimer(hWnd, TIMER_ID, TIMER_ELAPSE, TimerProc);
}

void DestroyTimer(HWND hWnd)
{
	KillTimer(hWnd, TIMER_ID);
}

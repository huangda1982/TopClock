//#include <regext.h>
#include <windows.h>

#include "../inc/Timer.h"

#include "../inc/Clock.h"

#if _WIN32_WCE >= 0x501
static HREGNOTIFY	s_hNotify = {0};

static void NotifyCallback(HREGNOTIFY hNotify, DWORD dwUserData, const PBYTE pData, const UINT cbData)
{
	UpdateClock((HWND)dwUserData);
}

void CreateTimer(HWND hWnd)
{
	RegistryNotifyCallback(HKEY_LOCAL_MACHINE, TIME_NOTIFY_PATH, TIME_NOTIFY_VALUE,
		NotifyCallback, (DWORD)hWnd, NULL, &s_hNotify);
}

void DestroyTimer(HWND hWnd)
{
	RegistryCloseNotification(s_hNotify);
}
#else //_WIN32_WCE >= 0x501
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
#endif //_WIN32_WCE >= 0x501

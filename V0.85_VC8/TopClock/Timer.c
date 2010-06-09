#include <Regext.h>

#include "Timer.h"

#include "Clock.h"

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


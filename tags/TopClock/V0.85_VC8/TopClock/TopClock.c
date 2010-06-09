// TopClock.cpp : 定义应用程序的入口点。

#pragma comment(lib, "aygshell.lib") 

#include <Windows.h>
#include <AygShell.h>

#include "TopClock.h"
#include "Clock.h"
#include "Timer.h"

#define MAX_LOADSTRING 256

HINSTANCE	g_hInst = NULL;
HWND		g_hwndMenuBar = NULL;

BOOL		g_b12H = FALSE;
BOOL		g_bHide = FALSE;
BOOL		g_bColor = FALSE;

static COLORREF GetTrayTextColor()
{
	BYTE		themeValues[COLOR_TRAYTEXT_SIZE] = {0};
	int			i = COLOR_TRAYTEXT_SIZE;
	HKEY		hKey = NULL;
	COLORREF	color = 0;

	RegOpenKeyEx(HKEY_LOCAL_MACHINE, COLOR_TRAYTEXT_PATH, 0, 0, &hKey);
	RegQueryValueEx(hKey, COLOR_TRAYTEXT_VALUE, NULL, NULL, themeValues, (LPDWORD)&i);

	color = *(DWORD*)(themeValues + COLOR_TRAYTEXT_OFFSET);
	
	return color;
}

static void DoCommandLine(LPTSTR lpCmdLine)
{
	int			nIndex1 = 0, nIndex2 = 0;
	int			nR = 0, nG = 0, nB = 0;
	BOOL		bColor = FALSE;
	COLORREF	color = 0;
	TCHAR		acArg[MAX_LOADSTRING] = {0};

	do
	{
		if(lpCmdLine[nIndex1] && !IsSpace(lpCmdLine[nIndex1]))
		{
			acArg[nIndex2++] = lpCmdLine[nIndex1];
		}
		else
		{
			acArg[nIndex2] = '\0';
			nIndex2 = 0;

			if(bColor)
			{
				if(acArg[0] == ARG_COLOR_HEAD)
				{
					SScanF(acArg, TEXT("#%2x%2x%2x"), &nR, &nG, &nB);
					SetClockColor(RGB(nR, nG, nB));
					g_bColor = TRUE;
				}
				bColor = FALSE;
			}
			else
			{
				if(!StrCmp(StrLwr(acArg), ARG_12H))
				{
					g_b12H = TRUE;
				}

				if(!StrCmp(StrLwr(acArg), ARG_HIDE))
				{
					g_bHide = TRUE;
				}

				if(!StrCmp(StrLwr(acArg), ARG_COLOR))
				{
					bColor = TRUE;
				}
			}
		}
	}while(lpCmdLine[nIndex1++]);
}

static BOOL CALLBACK DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int		wmId;
	int		wmEvent;
	RECT	rect = {INFO_X, INFO_Y, INFO_RIGHT, INFO_BOTTOM};
	BOOL	b12H = FALSE;

	SHINITDLGINFO	sid;
	SHMENUBARINFO	mbi;

	switch (uMsg) 
	{
	case WM_COMMAND:
		wmId	= LOWORD(wParam); 
		wmEvent = HIWORD(wParam); 
		switch (wmId)
		{
		case IDM_HIDE:
			ShowWindow(hwndDlg, SW_HIDE);
			break;
		case IDM_EXIT:
			DestroyWindow(hwndDlg);
			PostQuitMessage(0);
			break;
		default:
			return FALSE;
			break;
		}
		break;

	case WM_SYSCOLORCHANGE:
		if(!g_bColor)
		{
			SetClockColor(GetTrayTextColor());
			UpdateClock(hwndDlg);
		}
		break;

	case WM_INITDIALOG:
		sid.dwMask = SHIDIM_FLAGS;
		sid.dwFlags = SHIDIF_SIZEDLGFULLSCREEN;
		sid.hDlg = hwndDlg;

		if (!SHInitDialog(&sid)) 
		{
			return FALSE;
		}

		memset(&mbi, 0, sizeof(SHMENUBARINFO));
		mbi.cbSize	   = sizeof(SHMENUBARINFO);
		mbi.hwndParent = hwndDlg;
		mbi.nToolBarId = IDR_MENU;
		mbi.hInstRes   = g_hInst;

		if (SHCreateMenuBar(&mbi)) 
		{
			g_hwndMenuBar = mbi.hwndMB;
			ShowWindow(g_hwndMenuBar, SW_HIDE);
		}

		if(!g_bColor)
		{
			SetClockColor(GetTrayTextColor());
		}

		CreateClock(hwndDlg);
		CreateTimer(hwndDlg);
		break;

	case WM_PAINT:
		ShowWindow(g_hwndMenuBar, SW_SHOW);
		return FALSE;
		break;

	case WM_CLOSE:
		DestroyWindow(hwndDlg);
		PostQuitMessage(0);
		break;

	case WM_DESTROY:
		DestroyTimer(hwndDlg);
		CommandBar_Destroy(g_hwndMenuBar);
		DestroyClock(hwndDlg);
		break;

	default:
		return FALSE;
		break;
	}

	return TRUE;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	MSG		msg;
	HWND	hWnd;
	TCHAR	szTitle[MAX_LOADSTRING];

	g_hInst = hInstance;

	nCmdShow = SW_HIDE;
	DoCommandLine(lpCmdLine);

	SHInitExtraControls();

	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING); 
	hWnd = FindWindow(DIALOG_CLASS, szTitle);	
	if(hWnd) 
	{
		ShowWindow(hWnd, SW_SHOW);
		SetForegroundWindow((HWND)((ULONG) hWnd | 0x00000001));

		return 0;
	} 

	hWnd = CreateDialog(g_hInst, MAKEINTRESOURCE(IDD_TOPCLOCK), NULL, DialogProc);

	if (!hWnd)
	{
		return FALSE;
	}

	SetWindowText(hWnd, szTitle);
	ShowWindow(hWnd, nCmdShow);

	if(!g_bHide)
	{
		ShowWindow(hWnd, SW_SHOW);
		ShowWindow(g_hwndMenuBar, SW_SHOW);
	}

	while(GetMessage(&msg, NULL, 0, 0)) 
	{
		if(!IsDialogMessage(hWnd, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}

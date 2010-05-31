#include <windows.h>
#include "../inc/TopClock.h"

#include "../inc/Clock.h"

static COLORREF	s_color = 0;
static HICON	s_hHourIcon = NULL;
static HICON	s_hMinIcon = NULL;

static void ClearBitmap(HBITMAP hbm, COLORREF colorRef)
{
	HDC		hdc = CreateCompatibleDC(NULL);
	HBRUSH	hbr = CreateSolidBrush(colorRef);
	BITMAP	bm = {0};
	RECT	rt = {0};
	HGDIOBJ hOldBitmap = NULL;

	GetObject(hbm, sizeof(bm), &bm);
	rt.right = bm.bmWidth;
	rt.bottom = bm.bmHeight;

	hOldBitmap = SelectObject(hdc, hbm);
	FillRect(hdc, &rt, hbr);

	SelectObject(hdc, hOldBitmap);
	DeleteObject(hbr);
	DeleteDC(hdc);
}

static void DrawCharacter(HDC hdcDst, int nBitmapID, int x, int y)
{
	HDC		hdcSrc = CreateCompatibleDC(hdcDst);
	HBITMAP	hbmSrc = LoadBitmap(g_hInst, MAKEINTRESOURCE(nBitmapID));
	BITMAP	bm = {0};
	HGDIOBJ hOldBitmap = NULL;

	GetObject(hbmSrc, sizeof(bm), &bm);
	hOldBitmap = SelectObject(hdcSrc, hbmSrc);
	BitBlt(hdcDst, x, y, bm.bmWidth, bm.bmHeight,
		hdcSrc, 0, 0, SRCCOPY);

	SelectObject(hdcSrc, hOldBitmap);
	DeleteObject(hbmSrc);
	DeleteDC(hdcSrc);
}

static HBITMAP CreateTimeBitmap(BOOL bHour, int nNum)
{
	HBITMAP	hbmDst = NULL;
	HGDIOBJ	hOldDstBitmap = NULL;
	HDC		hdcDst = CreateCompatibleDC(NULL);
	BOOL	bAM = FALSE;
	int		D1 = 0;

	hbmDst = CreateBitmap(ICON_WIDTH, ICON_HEIGHT, 1, 1,NULL);
	ClearBitmap(hbmDst, RGB(0, 0, 0));
	hOldDstBitmap = SelectObject(hdcDst, hbmDst);

	if(bHour && g_b12H)
	{
		if (nNum < 12) bAM = TRUE;
		if (nNum > 12) nNum -= 12;
	}

	D1 = nNum / 10;
	if(!bHour || D1 > 0)
	{
		DrawCharacter(hdcDst, IDB_0 + D1, DIGIT1_X, DIGIT1_Y);
	}

	DrawCharacter(hdcDst, IDB_0 + nNum % 10, DIGIT2_X, DIGIT2_Y);

	if(bHour)
	{
		if(g_b12H)
		{
			DrawCharacter(hdcDst, bAM ? IDB_AM : IDB_PM, AM_PM_X, AM_PM_Y);
		}
	}
	else
	{
		DrawCharacter(hdcDst, IDB_COLON, COLON_X, COLON_Y);
	}

	SelectObject(hdcDst, hOldDstBitmap);
	DeleteDC(hdcDst);

	return hbmDst;
}
static HBITMAP MakeColor(HWND hWnd, HBITMAP hBitmap, COLORREF colorRef)
{
	HDC hdcSrc = CreateCompatibleDC(NULL);
	HDC hdcDst = CreateCompatibleDC(NULL);
	HDC hdcWnd = GetWindowDC(hWnd);

	HBITMAP hbmColor = CreateCompatibleBitmap(hdcWnd, ICON_WIDTH, ICON_HEIGHT);

	HGDIOBJ hOldSrcBitmap = SelectObject(hdcSrc, hBitmap);
	HGDIOBJ hOldDstBitmap = SelectObject(hdcDst, hbmColor);

	SetBkColor(hdcDst, ~colorRef);
	SetTextColor(hdcDst, RGB(255, 255, 255));

	BitBlt(hdcDst, 0, 0, ICON_WIDTH, ICON_HEIGHT, hdcSrc, 0, 0, NOTSRCCOPY);

	SelectObject(hdcSrc, hOldSrcBitmap);
	SelectObject(hdcDst, hOldDstBitmap);

	DeleteDC(hdcSrc);
	DeleteDC(hdcDst);

	ReleaseDC(hWnd, hdcWnd);

	return hbmColor;
}

static HBITMAP MakeMask(HBITMAP hBitmap)
{
	HDC hdcSrc = CreateCompatibleDC(NULL);
	HDC hdcDst = CreateCompatibleDC(NULL);

	HBITMAP hbmMask = CreateBitmap(ICON_WIDTH, ICON_HEIGHT, 1, 1, NULL);

	HGDIOBJ hOldSrcBitmap = SelectObject(hdcSrc, hBitmap);
	HGDIOBJ hOldDstBitmap = SelectObject(hdcDst, hbmMask);

	BitBlt(hdcDst, 0, 0, ICON_WIDTH, ICON_HEIGHT, hdcSrc, 0, 0, NOTSRCCOPY);

	SelectObject(hdcSrc, hOldSrcBitmap);
	SelectObject(hdcDst, hOldDstBitmap);

	DeleteDC(hdcSrc);
	DeleteDC(hdcDst);

	return hbmMask;
}

static HICON MakeIcon(HBITMAP hbmMask, HBITMAP hbmColor)
{
	ICONINFO ii = {0};
	ii.fIcon = TRUE;
	ii.hbmMask = hbmMask;
	ii.hbmColor = hbmColor;

	return CreateIconIndirect(&ii);
}

static void DeleteStatusBarIcons(HWND hWnd)
{
	NOTIFYICONDATA st_NID = {0};

	st_NID.cbSize = sizeof(st_NID);
	st_NID.uFlags = NIF_ICON;
	st_NID.hWnd = hWnd;

	st_NID.uID = HOUR_ICON_ID;
	st_NID.hIcon = s_hHourIcon;
	Shell_NotifyIcon(NIM_DELETE, &st_NID);
	DestroyIcon(s_hHourIcon);

	st_NID.uID = MIN_ICON_ID;
	st_NID.hIcon = s_hMinIcon;
	Shell_NotifyIcon(NIM_DELETE, &st_NID);
	DestroyIcon(s_hMinIcon);
}

void SetClockColor(COLORREF color)
{
	s_color = color;
}

void UpdateClock(HWND hWnd)
{
	static BOOL s_IconsAdded = FALSE;
	static int	s_hour = -1;
	static int	s_min = -1;

	SYSTEMTIME	st;

	int	nNIM;

	HBITMAP	hBitmap;
	HBITMAP	hbmMask;
	HBITMAP	hbmColor;

	NOTIFYICONDATA st_NID = {0};

	GetLocalTime(&st);
	if (s_hour != st.wHour || s_min != st.wMinute)
	{
		s_hour = st.wHour;
		s_min = st.wMinute;


		hBitmap = CreateTimeBitmap(TRUE, s_hour);
		hbmColor = MakeColor(hWnd, hBitmap, s_color);
		hbmMask = MakeMask(hBitmap);
		DestroyIcon(s_hHourIcon);
		s_hHourIcon = MakeIcon(hbmMask, hbmColor);

		DeleteObject(hBitmap);
		DeleteObject(hbmColor);
		DeleteObject(hbmMask);

		hBitmap = CreateTimeBitmap(FALSE, s_min);
		hbmColor = MakeColor(hWnd, hBitmap, s_color);
		hbmMask = MakeMask(hBitmap);
		DestroyIcon(s_hMinIcon);
		s_hMinIcon = MakeIcon(hbmMask, hbmColor);

		DeleteObject(hBitmap);
		DeleteObject(hbmColor);
		DeleteObject(hbmMask);

		if(!s_IconsAdded)
		{
			nNIM = NIM_ADD;
			s_IconsAdded = TRUE;
		}
		else
		{
			nNIM = NIM_MODIFY;
		}

		st_NID.cbSize = sizeof(st_NID);
		st_NID.hWnd = hWnd;
		st_NID.uFlags = NIF_ICON;

		st_NID.hIcon = s_hHourIcon;
		st_NID.uID = HOUR_ICON_ID;
		Shell_NotifyIcon(nNIM, &st_NID);

		st_NID.hIcon = s_hMinIcon;
		st_NID.uID = MIN_ICON_ID;
		Shell_NotifyIcon(nNIM, &st_NID);
	}
}

void DestroyClock(HWND hWnd)
{
	DeleteStatusBarIcons(hWnd);
}

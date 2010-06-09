#ifndef __TOPCLOCK_H__
#define __TOPCLOCK_H__

#include <tchar.h>

#include "../res/resource.h"

#define	IsSpace iswspace
#define	StrLen	wcslen
#define	StrCpy	wcscpy
#define	StrCmp	wcscmp
#define	StrLwr	wcslwr
#define	SScanF	swscanf

#define	DIALOG_CLASS		TEXT("Dialog")

#define	ARG_HIDE			TEXT("-hide")
#define	ARG_12H				TEXT("-12")
#define	ARG_COLOR			TEXT("-color")
#define	ARG_COLOR_HEAD		'#'
#define	ARG_COLOR_FORMAT	TEXT("#%2x%2x%2x")

#define	INFO_X			(BAR_HEIGHT / 2)
#define	INFO_Y			INFO_X
#define	INFO_RIGHT		(SCREEN_WIDTH - INFO_X)
#define	INFO_BOTTOM		(SCREEN_HEIGHT - BAR_HEIGHT * 2)

extern HINSTANCE	g_hInst;
extern HWND			g_hwndMenuBar;

extern BOOL			g_b12H;
extern BOOL			g_bHide;
extern BOOL			g_bColor;

#endif //__TOPCLOCK_H__


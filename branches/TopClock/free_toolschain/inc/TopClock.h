#ifndef __TOPCLOCK_H__
#define __TOPCLOCK_H__

#include "../res/resource.h"

#define IsSpace iswspace
#define StrLen	wcslen
#define StrCpy	wcscpy
#define StrCmp wcscmp
#define StrLwr wcslwr
#define SScanF	swscanf

#define DIALOG_CLASS			TEXT("Dialog")

#define ARG_HIDE				TEXT("-hide")
#define ARG_12H				TEXT("-12")
#define ARG_COLOR				TEXT("-color")
#define ARG_COLOR_HEAD		'#'

#define	INFO_X					(BAR_HEIGHT / 2)
#define	INFO_Y					INFO_X
#define	INFO_RIGHT				(SCREEN_WIDTH - INFO_X)
#define	INFO_BOTTOM				(SCREEN_HEIGHT - BAR_HEIGHT * 2)

#if _WIN32_WCE < 0x501
#define	DEFAULT_COLOR			RGB(0xFF, 0xFF, 0xFF)
#endif //_WIN32_WCE < 0x501

extern HINSTANCE	g_hInst;
extern HWND			g_hwndMenuBar;

extern BOOL			g_b12H;
extern BOOL			g_bHide;
extern BOOL			g_bColor;

#ifndef QVGA
#define RES_IDB_0        IDB_0
#define RES_IDB_1        IDB_1
#define RES_IDB_2        IDB_2
#define RES_IDB_3        IDB_3
#define RES_IDB_4        IDB_4
#define RES_IDB_5        IDB_5
#define RES_IDB_6        IDB_6
#define RES_IDB_7        IDB_7
#define RES_IDB_8        IDB_8
#define RES_IDB_9        IDB_9
#define RES_IDB_COLON    IDB_COLON
#define RES_IDB_AM       IDB_AM
#define RES_IDB_PM       IDB_PM
#define RES_IDB_SEAL     IDB_SEAL
#define RES_IDD_TOPCLOCK IDD_TOPCLOCK
#define RES_IDC_INFO     IDC_INFO
#define RES_IDC_SIGN     IDC_SIGN
#define RES_IDD_TOPCLOCK IDD_TOPCLOCK
#else
#define RES_IDB_0        IDB_0_QVGA
#define RES_IDB_1        IDB_1_QVGA
#define RES_IDB_2        IDB_2_QVGA
#define RES_IDB_3        IDB_3_QVGA
#define RES_IDB_4        IDB_4_QVGA
#define RES_IDB_5        IDB_5_QVGA
#define RES_IDB_6        IDB_6_QVGA
#define RES_IDB_7        IDB_7_QVGA
#define RES_IDB_8        IDB_8_QVGA
#define RES_IDB_9        IDB_9_QVGA
#define RES_IDB_COLON    IDB_COLON_QVGA
#define RES_IDB_AM       IDB_AM_QVGA
#define RES_IDB_PM       IDB_PM_QVGA
#define RES_IDB_SEAL     IDB_SEAL_QVGA
#define RES_IDD_TOPCLOCK IDD_TOPCLOCK_QVGA
#define RES_IDC_INFO     IDC_INFO_QVGA
#define RES_IDC_SIGN     IDC_SIGN_QVGA
#define RES_IDC_SEAL     IDC_SEAL_QVGA
#define RES_IDD_TOPCLOCK IDD_TOPCLOCK_QVGA
#endif

#endif //__TOPCLOCK_H__

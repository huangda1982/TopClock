#ifndef __CLOCK_H__
#define __CLOCK_H__

#define COLOR_TRAYTEXT_OFFSET	0x0058
#define COLOR_TRAYTEXT_PATH		TEXT("\\SOFTWARE\\Microsoft\\Color\\")
#define COLOR_TRAYTEXT_VALUE	TEXT("ThemeValues")
#define COLOR_TRAYTEXT_SIZE		0x0118

#define HOUR_WIDTH          (ICON_WIDTH - HOUR_OFFSET)
#define MIN_WIDTH           ICON_WIDTH

#define HOUR_WIDTH          (ICON_WIDTH - HOUR_OFFSET)
#define MIN_WIDTH           ICON_WIDTH

#define HOUR_OFFSET         3
#define HOUR_ICON_ID			100
#define MIN_ICON_ID				(HOUR_ICON_ID + 1)

#define TIMER_ID				1
#define CLOCK_TIME_OUT			1000

#define ICON_WIDTH				BAR_HEIGHT
#define ICON_HEIGHT				ICON_WIDTH

#ifndef QVGA
#define SCREEN_WIDTH		176
#define SCREEN_HEIGHT		220
#define BAR_HEIGHT			16

#define DIGIT1_X            3
#define DIGIT1_Y            2

#define DIGIT2_X            10
#define DIGIT2_Y            DIGIT1_Y

#define DIGIT_WIDTH         6
#define DIGIT_HEIGHT        13

#define AM_PM_X             0
#define AM_PM_Y             DIGIT1_Y

#define AM_PM_WIDTH         6
#define AM_PM_HEIGHT        13

#define COLON_X             0
#define COLON_Y             (DIGIT1_Y + (DIGIT_HEIGHT - COLON_HEIGHT) / 2)

#define COLON_WIDTH         2
#define COLON_HEIGHT        7
#else //QVGA
#define SCREEN_WIDTH		240
#define SCREEN_HEIGHT		320
#define BAR_HEIGHT			22

#define DIGIT1_X            3
#define DIGIT1_Y            4

#define DIGIT2_X            13
#define DIGIT2_Y            DIGIT1_Y

#define DIGIT_WIDTH         9
#define DIGIT_HEIGHT        15

#define AM_PM_X             0
#define AM_PM_Y             DIGIT1_Y

#define AM_PM_WIDTH         9
#define AM_PM_HEIGHT        15

#define COLON_X             0
#define COLON_Y             (DIGIT1_Y + (DIGIT_HEIGHT - COLON_HEIGHT) / 2)

#define COLON_WIDTH         2
#define COLON_HEIGHT        7
#endif //QVGA

void	SetClockColor(COLORREF color);
#define	CreateClock(hWnd)	UpdateClock(hWnd)
void	UpdateClock(HWND hWnd);
void	DestroyClock(HWND hWnd);

#endif //__CLOCK_H__
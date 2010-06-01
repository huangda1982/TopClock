ARCH=arm-mingw32ce-
CC=${ARCH}gcc
CFLAGS=-g -D_WIN32_IE=0x0501 -D_WIN32_WCE=0x501
topClock.exe:	Clock.o Timer.o TopClock.o ../res/TopClock.rsc
	${CC} ${CFLAGS} -o $@ $? -lcommctrl -laygshell

.c.o:
	${CC} -c $<

clean:
	-rm -f topClock.exe *.o
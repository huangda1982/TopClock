ARCH=arm-mingw32ce
CC=${ARCH}-gcc

TopClock.exe:	Clock.o Timer.o TopClock.o ../res/TopClock.res
	${CC} -o $@ $? -lcommctrl

.c.o:
	${CC} -c -o $@ $<

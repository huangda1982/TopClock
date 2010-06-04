ARCH=arm-mingw32ce-
CC=${ARCH}gcc
#CFLAGS=-g -D_WIN32_WCE=501
CFLAGS=-D_WIN32_WCE=501 -O2 -shared-libgcc

all: TopClock.exe

TopClock.exe: Clock.o Timer.o TopClock.o ../res/TopClock.rsc
	${CC} ${CFLAGS} -o $@ $? -lcommctrl -laygshell

.c.o:
	${CC} ${CFLAGS} -c $<

clean:
	-rm -f TopClock.exe *.o

remake: clean all

ARCH=arm-mingw32ce-
CC=${ARCH}gcc
CFLAGS=-Os
LIBS=-laygshell

all: TopClock.exe

TopClock.exe: Clock.o Timer.o TopClock.o ../res/TopClock.rsc
	${CC} -s -o $@ $? ${LIBS}

.c.o:
	${CC} ${CFLAGS} -c $<

clean:
	-rm -f TopClock.exe *.o

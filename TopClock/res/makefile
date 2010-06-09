ARCH=arm-mingw32ce
WINDRES=${ARCH}-windres
RESFLAG=-c 936

TopClock.rsc:	TopClock.rc resource.h
	${WINDRES} ${RESFLAG} ${CODEPAGE} $< $@

clean:
	-rm -f TopClock.rsc


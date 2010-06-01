ARCH=arm-mingw32ce
WINDRES=${ARCH}-windres

TopClock.rsc:	TopClock.rc resource.h
	${WINDRES} $< $@

clean:
	-rm -f TopClock.rsc


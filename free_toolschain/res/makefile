ARCH=arm-mingw32ce
WINDRES=${ARCH}-windres

TopClock.res:	TopClock.rc resource.h
	${WINDRES} $< $@

clean:
	-rm -f TopClock.res


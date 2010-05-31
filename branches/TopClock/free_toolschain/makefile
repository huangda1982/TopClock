#ARCH=		arm-mingw32ce
#CC=		${ARCH}-gcc
#WINDRES=	${ARCH}-windres

#CFLAGS=		-g -D_WIN32_IE=0x0400

#menu-resource.exe:	menu-resource.o menu-resource.rsc
#	${CC} -o $@ menu-resource.o menu-resource.rsc -lcommctrl
#
#menu-resource.o:	menu-resource.c
#	${CC} -c $?

all:
	make -C res

clean:
	make clean -C res


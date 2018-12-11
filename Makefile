CPPFLAGS = -D_DEFAULT_SOURCE -D_BSD_SOURCE -D_POSIX_C_SOURCE=2 \
			-nostdinc \
			-I./include -I/usr/lib/gcc/x86_64-linux-gnu/6/include
# hack gcc, it's not compliant with free standing.
CFLAGS =  -std=c99 -pedantic \
		-O0 -g -m32 \
		-ffreestanding -fno-strict-aliasing \
		${CPPFLAGS}
LDFLAGS = -m32 -static -nostdlib \
		-Xlinker -T kern.lds -Xlinker --build-id=none
#		-Wl,-z,max-page-size=4096 -Wl,-z,common-page-size=4096 // trick for amd64, atm only i36, so ignore

SRC = kern.c boot.S
OBJ = ${patsubst %.S,%.o,${patsubst %.c,%.o,${SRC}}}

all: kern

.c.o:
	cc -c ${CFLAGS} $<

.S.o:
	cc -c ${CFLAGS} $<

kern: ${OBJ}
	cc -o $@ ${OBJ} ${LDFLAGS}

clean:
	rm -f kern ${OBJ}
.PHONY: all clean ${SRC}

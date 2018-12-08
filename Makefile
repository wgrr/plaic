CPPFLAGS = -D_DEFAULT_SOURCE -D_BSD_SOURCE -D_POSIX_C_SOURCE=2 \
			-nostdinc
CFLAGS = -std=c99 -pedantic \
		-O2 -g \
		-ffreestanding -fno-strict-aliasing \
		${CPPFLAGS}
LDFLAGS = -nostdlib -Xlinker -T kern.lds

SRC = kern.c
OBJ = ${SRC:.c=.o}

all: kern

.c.o:
	cc -c ${CFLAGS} $<

kern: ${OBJ}
	${CC} -o $@ ${OBJ} ${LDFLAGS}

clean:
	rm -f kern ${OBJ}
.PHONY: all clean ${SRC}

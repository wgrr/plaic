CPPFLAGS = -D_DEFAULT_SOURCE -D_BSD_SOURCE -D_POSIX_C_SOURCE=2
CFLAGS = -std=c99 -pedantic \
		-O2 -ggdb3 \
		-ffreestanding -fno-strict-aliasing \
		${CPPFLAGS}
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

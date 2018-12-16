#!/bin/bash

SRC=\
'
src/kern.c
src/boot.S
src/io/serport.S
'

OBJ='obj/boot.o obj/kern.o'

CPPFLAGS=-nostdinc
CFLAGS='-c -Og -g -m32 -ffreestanding -fno-strict-aliasing '$CPPFLAGS
LDFLAGS='
-melf_i386 -static -nostdlib
-T src/script.ld --build-id=none -o bin/kern
'

if [ "$1" = "clean" ]; then
	echo rm -f $OBJ
	rm -f $OBJ
	exit 0
fi

for s in $SRC; do
	echo 'cc' $CFLAGS -o obj/`echo $s|sed "s/src\///g"|sed "s/[\.c|\.S]//g"`.o $s
	cc $CFLAGS -o obj/`echo $s|sed "s/src\///g"|sed "s/[\.c|\.S]//g"`.o $s || exit 1
done

echo 'ld' $LDFLAGS $OBJ
ld $LDFLAGS $OBJ || exit 1


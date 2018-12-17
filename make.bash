#!/bin/bash

CC=clang

OBJ=`du -a ./obj | grep '\.o$' | awk '{print $2}'`
if [ "$1" = "clean" ]; then
	echo rm -f $OBJ bin/kern
	rm -f $OBJ bin/kern
	exit 0
fi

SRC=`du -a ./src | grep '\.c$' | awk '{print $2}'`
ASM=`du -a ./src | grep '\.s$' | awk '{print $2}'`

CPPFLAGS='-nostdinc -I./include'
CFLAGS='-c -O0 -g -m32 -ffreestanding '$CPPFLAGS
LDFLAGS='-melf_i386 -static -nostdlib -T src/script.ld --build-id=none -o bin/kern '

for s in $SRC; do
	echo $CC $CFLAGS -o obj/`echo $s|sed "s/\.\/src\///g"|sed "s/\.c$/\.o/g"` $s
	$CC $CFLAGS -o obj/`echo $s|sed "s/\.\/src\///g"|sed "s/\.c$/\.o/g"` $s || exit 1
done

for s in $ASM; do
	echo $CC -c -m32 -no-integrated-as -x assembler-with-cpp -nostdinc -I./include -o obj/`echo $s|sed "s/\.\/src\///g"|sed "s/\.s$/\.o/g"` $s
	$CC -c -m32 -no-integrated-as -x assembler-with-cpp -nostdinc -I./include -o obj/`echo $s|sed "s/\.\/src\///g"|sed "s/\.s$/\.o/g"` $s || exit 1
done

echo 'ld' $LDFLAGS $OBJ
ld $LDFLAGS $OBJ || exit 1

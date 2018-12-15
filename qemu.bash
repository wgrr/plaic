#!/bin/bash

TMP=$(mktemp -d)
CDROOT=$TMP/cdroot

mkdir -p $CDROOT/boot/grub
cp bin/kern $CDROOT/boot
echo -n 'set timeout=1
menuentry "kern" --class os {
	multiboot (hd96)/boot/kern
}' > $CDROOT/boot/grub/grub.cfg

grub-mkrescue -o $TMP/g.iso $CDROOT || exit 1

qemu-system-i386 -enable-kvm -gdb tcp::8000 \
		 -m 64 -nographic \
		 -cdrom $TMP/g.iso -boot d || rm -rf $TMP; exit 1

rm -rf $TMP


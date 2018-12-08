#!/bin/sh

TMP=$(mktemp -d)
CDROOT=$TMP/cdroot

mkdir -p $CDROOT/boot/grub
cp kern $CDROOT/boot
echo -n 'set timeout=1 menuentry "kern" --class os { multiboot (hd96)/boot/kern }'\
> $CDROOT/boot/grub/grub.cfg

grub-mkrescue -o $TMP/g.iso $CDROOT

qemu-system-x86_64 -enable-kvm -ctrl-grab -gdb tcp::1234 -m 64 -monitor stdio\
					-cdrom $TMP/g.iso -boot d

rm -rf $TMP

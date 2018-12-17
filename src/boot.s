.section .hdr, "a"

#include <limits.h>

#define mboot_flags 0x0
#define mboot_magik 0x1BADB002
#define mboot_chk 0x2BADB002

/* multiboot headers:
	uint32: magic
	uint32: flags
	uint32: checksum
*/
.int mboot_magik
.int mboot_flags
.int -(mboot_flags+mboot_magik)

.section .text, "ax"

_entry:
	cmp $mboot_chk, %eax
	jne .
	mov $boot·stack, %esp
	add $boot·stacklen, %esp
	jmp main

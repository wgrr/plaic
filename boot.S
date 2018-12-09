#include <defs.h>
.section .hdr, "a"
.code32

#define BOOT_FLAGS 0x0

/* multiboot headers:
	uint32: magic
	uint32: flags
	uint32: checksum
*/
.int 0x1BADB002
.int BOOT_FLAGS
.int -(BOOT_FLAGS+0x1BADB002)

.global print
.section .text, "ax"

_start:
	cmp $0x2badb002, %eax
	/* maybe instead of looping forever, should print something */
	jnz .
	mov $stack, %esp
	add $_STACKSIZE, %esp
	jmp main

/* bad, move to C, atm it's messing with stack frame for some reason */
print:
	movzwl 0xb8000, %eax
	or     $0x761, %ax
	mov    %ax,0xb8000
	ret

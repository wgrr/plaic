.section .hdr, "a"

#define mboot_flags 0x0
#define mboot_magik 0x1BADB002
#define mboot_chk 0x2BADB002
#define stacklen 4096

/* multiboot headers:
	uint32: magic
	uint32: flags
	uint32: checksum
*/
.int mboot_magik
.int mboot_flags 
.int -(mboot_flags+mboot_magik)

.section .text, "ax"

_start:
	cmp $mboot_chk, %eax
	jnz .
	mov $stack, %esp
	add $stacklen, %esp 
	jmp main

#undef mboot_flags
#undef mboot_magik
#undef mboot_chk
#undef stacklen


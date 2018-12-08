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

.section .text
.globl cpu·eflags

#define CPU_EFLAGS_MASK 0x200

cpu·eflags:
	pushf
	pop %eax
	ret

cpu·setint:
	sti
	ret

cpu·unusetint:
	cli
	ret

cpu·has_int:
	pushf
	pop %eax
	and $CPU_EFLAGS_MASK, %eax
	shr $0x9, %eax
	ret

cpu·lgdt:
	lgdt
	ret
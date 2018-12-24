.section .text
.globl cpu·eflags
.globl cpu·lgdt
.globl cpu·setint
.globl cpu·unusetint
.globl cpu·can_int
.globl cpu·lidt

#define CPU_EFLAGS_MASK 0x200

// gdt indexes, should match cpu.c:/GDT_INDEX

// skip TI and RPL bits of selector
// TODO(wgr): jump to ref file instead of commenting here
// local ref: file:///usr/wgr/lib/pdf/intel-arch-ref.pdf#G41.3940
// online ref: access: (Fri Dec 21 12:07:42 -02 2018) https://software.intel.com/sites/default/files/managed/39/c5/325462-sdm-vol-1-2abcd-3abcd.pdf#G41.31794
#define GDT_NIL 0
#define GDT_CODE 1 << 3
#define GDT_DATA 2 << 3
#define GDT_N 3

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

cpu·can_int:
	pushf
	pop %eax
	and $CPU_EFLAGS_MASK, %eax
	shr $0x9, %eax
	ret

cpu·lgdt:
	mov 4(%esp), %eax
	lgdt (%eax)

	mov $(GDT_DATA), %eax
	mov %eax, %ds
	mov %eax, %es
	mov %eax, %fs
	mov %eax, %gs
	mov %eax, %ss
	ljmp $(GDT_CODE), $1f
1:
	ret

cpu·lidt:
	mov 4(%esp), %eax
	lidt (%eax)
	ret

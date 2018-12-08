/* TODO(wgr): describe */
MEMORY {
	RAM : ORIGIN = 0x100000, LENGTH = 63M
}

SECTIONS {
	/* TODO(wgr): plumb to ref docs */
	.text  : {
		*(.text)
	} > RAM
	.data : {
		*(.data)
	} > RAM
	.bss : {
		*(.bss)
	} > RAM
}
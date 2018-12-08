/* TODO(wgr): describe */
MEMORY
{
	RAM : ORIGIN = 0x100000, LENGTH = 63M
}

PHDRS
{
	hdr	PT_LOAD FLAGS(4);
	text	PT_LOAD FLAGS(5);
	data	PT_LOAD FLAGS(6);
}

SECTIONS
{
	/* TODO(wgr): plumb to ref docs */
	.hdr : {
		*(.hdr)
	} > RAM : hdr
	.text  : {
		*(.text)
	} > RAM : text
	.data : {
		*(.data)
	} > RAM : data
	.bss : {
		*(.bss)
	} > RAM : data
	/* discard debug section */
	/DISCARD/ : {
		*(.eh_frame)
	}
}
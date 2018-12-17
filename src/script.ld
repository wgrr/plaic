ENTRY(_entry)

MEMORY
{
	RAM : ORIGIN = 1M, LENGTH = 63M
}

PHDRS
{
	hdr PT_LOAD FLAGS(4);
	text PT_LOAD FLAGS(5);
	data PT_LOAD FLAGS(6);
}

SECTIONS
{
	.hdr : {
		*(.hdr)
	} > RAM : hdr

	.text : {
		*(.text)
	} > RAM : text

	.data : {
		*(.data)
	} > RAM : data

	.bss : {
		*(.bss)
	} > RAM : data

	/DISCARD/ : {
		*(.eh_frame)
	}
}

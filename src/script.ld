ENTRY(_entry)

MEMORY
{
	RAM : ORIGIN = 1M, LENGTH = 63M
}

PHDRS
{
	multiboot_hdr PT_LOAD FLAGS(4);
	text PT_LOAD FLAGS(5);
	data PT_LOAD FLAGS(6);
}

SECTIONS
{
	.multiboot_hdr : {
		*(.multiboot_hdr)
	} > RAM : multiboot_hdr

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

.section .text

.globl serport_write

serport_write:
	mov 8(%esp), %eax
	mov 4(%esp), %edx
	out %al, %dx
	jmp .

.section .text

.globl serport·write

serport·write:
	mov 8(%esp), %eax
	mov 4(%esp), %edx
	out %al, %dx
	ret

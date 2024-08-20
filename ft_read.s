global ft_read
extern __errno_location

section .text

ft_read:
	xor		rax, rax
	syscall
	test	rax, rax
	js		.error ; sign
	ret

.error:
	neg		rax
	mov		rdx, rax
	call	__errno_location wrt ..plt ;ASLR
	mov		[rax], rdx
	mov		rax, -1
	ret
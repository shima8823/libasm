global ft_strlen

section .text

ft_strlen:
	mov	rax, rdi
	mov	rcx, rax

.loop:
	cmp	byte[rax], 0
	je	.done
	inc rax
	jmp .loop

.done:
	sub rax, rcx
	ret
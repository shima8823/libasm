global ft_strcpy

section .text

ft_strcpy:	;dest: rdi, src: rsi
	mov	rax, rdi

.loop:
	cmp	byte[rsi], 0
	je	.done
	mov	cl, byte[rsi]
	mov byte[rdi], cl
	inc rdi
	inc rsi
	jmp .loop

.done:
	mov byte[rdi], 0
	ret
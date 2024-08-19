global ft_strcmp

section .text

ft_strcmp:	;s1: rdi, s2: rsi

.loop:
	cmp	byte[rdi], 0
	je	.done
	cmp	byte[rsi], 0
	je	.done

	mov	al, byte[rdi]
	cmp al, byte[rsi]
	jnz .done

	inc rdi
	inc rsi
	jmp .loop

.done:
	movzx	rax, byte[rdi]
	movzx	rcx, byte[rsi]
	sub	rax, rcx
	ret
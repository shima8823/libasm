global ft_strcmp

section .text

ft_strcmp:	;s1: rdi, s2: rsi

.loop:
	mov	al, [rdi]
	mov	cl, [rsi]

	cmp	al, cl
	jne	.done
	
	cmp	al, 0
	je	.done

	inc rdi
	inc rsi
	jmp .loop

.done:
	sub		al, cl
	movsx	rax, al
	ret
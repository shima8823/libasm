global ft_strcmp

section .text

ft_strcmp:	;s1: rdi, s2: rsi

.loop:
	mov	al, [rdi]
	mov	cl, [rsi]

	cmp	al, cl
	jne	.done
	
	test	al, al
	jz	.done

	inc rdi
	inc rsi
	jmp .loop

.done:
	sub		al, cl
	movsx	eax, al
	ret
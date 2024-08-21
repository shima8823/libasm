global ft_strdup

extern ft_strcpy
extern ft_strlen
extern malloc

section .text

ft_strdup:	; s: rdi
	xor rax, rax
	test rdi, rdi ; null check
	jz .done
	push rdi
	call ft_strlen wrt ..plt
	inc rax ; ft_strlen(s1) + 1 * sizeof(char)
	mov rdi, rax 
	call malloc wrt ..plt
	pop rsi
	test rax, rax ; malloc null check
	jz .done
	mov rdi, rax
	call ft_strcpy wrt ..plt
.done:
	ret
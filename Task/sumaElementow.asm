section .text
	global sumaElementow

sumaElementow:
	mov ebx, 0
	mov eax, 0
	jmp .ileZostalo

.dodaj:
	lea rcx, [rdi + rbx * 4]
	add eax, [rcx]

	inc ebx
.ileZostalo:
	cmp ebx, esi
	jl .dodaj

	ret


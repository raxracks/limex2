global _store_registers
global _restore_registers

_store_registers:
    push rdi
    push rsi
    push rbp
    push rsp
    push rbx
    push rdx
    push rcx
    push rax
	mov ax, ds
	push rax
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

_restore_registers:
    mov rdi, rax

	pop rax
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
    pop rax
    pop rcx
    pop rdx
    pop rbx
    pop rsp
    pop rbp
    pop rsi
    mov rax, rdi
    pop rdi

	add rsp, 0x10

    iretq
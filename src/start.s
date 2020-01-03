[bits 32]

MAGIC equ 0xE85250D6
ARCH equ 0
HEADER_LENGTH equ (header_end - header_start)
CHECKSUM equ -(MAGIC + ARCH + HEADER_LENGTH)

; The start of the multiboot header
section .multiboot
header_start:
	dd MAGIC
	dd ARCH
	dd HEADER_LENGTH
	dd -(MAGIC + ARCH + HEADER_LENGTH)

	dw 0
	dw 0
	dd 8
header_end:

section .bss
align 16
	stack_bottom:
		resb 16384
	stack_top:

; Make 'start' accessible outside this file
global start

section .text
	start:
		cli
		; Create the stack
		mov esp, stack_top

		; Clear space for paging tables
		mov edi, 0x1000
		mov cr3, edi
		xor eax, eax
		mov ecx, 4096
		rep stosd
		mov edi, cr3

		; Setup the PML4T
		mov dword [edi], 0x2003
		add edi, 0x1000
		; Setup the PDPT
		mov dword [edi], 0x3003
		add edi, 0x1000
		; Setup the PDT
		mov dword [edi], 0x4003
		add edi, 0x1000

		mov ebx, 0x00000003
		mov ecx, 512

		.SetEntry:
			mov dword [edi], ebx
			add ebx, 0x1000
			add edi, 8
			loop .SetEntry
		
		; Enable PAE paging
		mov eax, cr4
		or eax, 1 << 5
		mov cr4, eax

		; Set the long mode bit
		mov ecx, 0xC0000080
		rdmsr
		or eax, 1 << 8
		wrmsr

		; Enable paging
		mov eax, cr0
		or eax, 1 << 31
		mov cr0, eax

		lgdt [GDT64.Pointer]
		jmp GDT64.Code:Realm64

GDT64:                           ; Global Descriptor Table (64-bit).
    .Null: equ $ - GDT64         ; The null descriptor.
    dw 0xFFFF                    ; Limit (low).
    dw 0                         ; Base (low).
    db 0                         ; Base (middle)
    db 0                         ; Access.
    db 1                         ; Granularity.
    db 0                         ; Base (high).
    .Code: equ $ - GDT64         ; The code descriptor.
    dw 0                         ; Limit (low).
    dw 0                         ; Base (low).
    db 0                         ; Base (middle)
    db 10011010b                 ; Access (exec/read).
    db 10101111b                 ; Granularity, 64 bits flag, limit19:16.
    db 0                         ; Base (high).
    .Data: equ $ - GDT64         ; The data descriptor.
    dw 0                         ; Limit (low).
    dw 0                         ; Base (low).
    db 0                         ; Base (middle)
    db 10010010b                 ; Access (read/write).
    db 00000000b                 ; Granularity.
    db 0                         ; Base (high).
    .Pointer:                    ; The GDT-pointer.
    dw $ - GDT64 - 1             ; Limit.
    dq GDT64                     ; Base.


[bits 64]
; 'kernel_main' is external to this file
extern kernel_main

Realm64:
	; Welcome to long mode!
	cli
	mov ax, GDT64.Data
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	mov edi, 0xB8000
	mov rax, 0x1F201F201F201F20
	mov ecx, 500
	rep stosq
	
	call kernel_main

	hang:
		cli
		hlt
		jmp hang

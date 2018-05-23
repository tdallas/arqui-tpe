GLOBAL cpuVendor
GLOBAL get_time_RTC
GLOBAL get_key
GLOBAL beep

EXTERN ticks_delay

SECTION .text

cpuVendor:
	push rbp
	mov rbp, rsp
	push rbx

	mov rax, 0
	cpuid


	mov [rdi], ebx
	mov [rdi + 4], edx
	mov [rdi + 8], ecx

	mov byte [rdi+13], 0

	mov rax, rdi

	pop rbx

	mov rsp, rbp
	pop rbp
	ret

get_time_RTC:
	push rbp
  	mov rbp, rsp

  	mov al,0x0B ; RTC Status Register B
  	out 70h,al
  	in al, 71h
  	or al, 0x04 ; Second bit = 1
  	out 71h, al ; Overwrite config

  	mov rax, rdi
  	out 70h,al
	in al,71h
  	movzx rax, al

  	mov rsp, rbp
  	pop rbp
  	ret

get_key:
  	push rbp
  	mov rbp, rsp

  	and rax, 0h
  	in al, 60h

  	mov rsp, rbp
  	pop rbp
  	ret

; -----------------------------------------------------------------------------
; os_speaker_beep -- Create a standard OS beep
; IN:	Nothing
; OUT:	All registers preserved
beep:
	push rbp
  	mov rbp, rsp

	push rax
	push rcx

	xor ecx, ecx
	mov cx, 0x0C80		; Store note value for now
	mov al, 182
	out 0x43, al		; System timers..
	mov ax, cx		; Set up frequency
	out 0x42, al
	mov al, ah		; 64-bit mode.... AH allowed????
	out 0x42, al
	in al, 0x61		; Switch PC speaker on
	or al, 0x03
	out 0x61, al

	push rdi
	mov rdi, 4		; A quarter of a second delay
	call ticks_delay
	pop rdi

	in al, 0x61		; Switch PC speaker off
	and al, 0xFC
	out 0x61, al

	pop rcx
	pop rax

	mov rsp, rbp
  	pop rbp
	ret
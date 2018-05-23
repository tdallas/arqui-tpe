GLOBAL cpuVendor
GLOBAL get_time_RTC
GLOBAL key_pressed
GLOBAL get_key
GLOBAL os_speaker_beep
GLOBAL os_speaker_tone
GLOBAL os_speaker_off
GLOBAL inf_loop

SECTION .text

cpuVendor:
	push rbp
	mov rbp, rsp
	call os_speaker_beep
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
  
key_pressed:
  	push rbp
  	mov rbp, rsp
  
  	in al, 64h
  	and al, 1h

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
; os_speaker_tone -- Generate a tone on the PC speaker
; IN:	RAX = note frequency
; OUT:	All registers preserved
; Note:	Call os_speaker_off to stop the tone
os_speaker_tone:
	push rax
	push rcx

	mov cx, ax		; Store note value for now
	mov al, 182
	out 0x43, al		; System timers..
	mov ax, cx		; Set up frequency
	out 0x42, al
	mov al, ah		; 64-bit mode.... AH allowed????
	out 0x42, al
	in al, 0x61		; Switch PC speaker on
	or al, 0x03
	out 0x61, al

	pop rcx
	pop rax
	ret
; -----------------------------------------------------------------------------


; -----------------------------------------------------------------------------
; os_speaker_off -- Turn off PC speaker
; IN:	Nothing
; OUT:	All registers preserved
os_speaker_off:
	push rax

	in al, 0x61		; Switch PC speaker off
	and al, 0xFC
	out 0x61, al

	pop rax
	ret
; -----------------------------------------------------------------------------


; -----------------------------------------------------------------------------
; os_speaker_beep -- Create a standard OS beep
; IN:	Nothing
; OUT:	All registers preserved
os_speaker_beep:
	push rax
	push rcx

	xor eax, eax
	mov ax, 0x0C80
	call os_speaker_tone
	mov ax, 2		; A quarter of a second
	call inf_loop
	call os_speaker_off

	pop rcx
	pop rax
	ret

inf_loop:
	push rbx
	mov rbx, 200
	
	.loop:
	cmp rbx, 0
	jnz .loop

	pop rbx
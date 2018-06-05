GLOBAL cpuVendor
GLOBAL getTimeRTC
GLOBAL getKeyCode
GLOBAL speakerBeep
GLOBAL speakerOn
GLOBAL speakerOff

SECTION .text

; -----------------------------------------------------------------------------
; cpuVendor -- Writes information of the cpu on the buffer
; IN:	RDI = pointer to buffer
; OUT:	RAX = pointer of the buffer with the information
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
; -----------------------------------------------------------------------------

; -----------------------------------------------------------------------------
; getTimeRTC -- Gets the corresponding actual unit of time requested
; IN:	RDI = 0 for seconds, 2 for minutes, 4 for hours, 6 for weekday, 
; 		7 for days, 8 for months, 9 for years
; OUT:	RAX = corresponding unit of time requested
getTimeRTC:
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
; -----------------------------------------------------------------------------

; -----------------------------------------------------------------------------
; getKeyCode -- Gets the key code of the key pressed
; IN:	Nothing
; OUT:	RAX = key code
getKeyCode:
  	push rbp
  	mov rbp, rsp

	xor rax, rax
	in al, 64h
	and al, 1 ;Me quedo con el ultimo bit
	test al, al
	jz .end
	in al, 60h
	
	.end:
  	mov rsp, rbp
  	pop rbp
  	ret
; -----------------------------------------------------------------------------

; -----------------------------------------------------------------------------
; speakerOn -- Generate a tone on the PC speaker
; IN:	RDI = note frequency
; OUT:	All registers preserved
; Note:	Call speakerOff to stop the tone
speakerOn:
	push rbp
  	mov rbp, rsp
	
	push rax

	mov al, 182
	out 0x43, al	; System timers..
	mov ax, di		; Set up frequency
	out 0x42, al
	mov al, ah		; 64-bit mode.... AH allowed????
	out 0x42, al
	in al, 0x61		; Switch PC speaker on
	or al, 0x03
	out 0x61, al

	pop rax

	mov rsp, rbp
  	pop rbp
	ret
; -----------------------------------------------------------------------------

; -----------------------------------------------------------------------------
; speakerOff -- Turn off PC speaker
; IN:	Nothing
; OUT:	All registers preserved
speakerOff:
	push rbp
  	mov rbp, rsp
	
	push rax

	in al, 0x61		; Switch PC speaker off
	and al, 0xFC
	out 0x61, al

	pop rax

	mov rsp, rbp
  	pop rbp
	ret
; -----------------------------------------------------------------------------

; -----------------------------------------------------------------------------
; speakerBeep -- Create a standard OS beep
; IN:	Nothing
; OUT:	All registers preserved
speakerBeep:
	push rbp
  	mov rbp, rsp
	
	push rax
	push rcx

	mov rax, 0x0000000000000C80  ;Frequency for beep
	call speakerOn

	call speakerOff

	pop rcx
	pop rax

	mov rsp, rbp
  	pop rbp
	ret
; -----------------------------------------------------------------------------
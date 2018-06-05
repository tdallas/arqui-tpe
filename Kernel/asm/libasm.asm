GLOBAL cpuVendor
GLOBAL getTimeRTC
GLOBAL getKeyCode
GLOBAL speakerOn
GLOBAL speakerOff

SECTION .text

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

; getTimeRTC -- Gets the corresponding actual unit of time requested
; IN:	RDI = 0 for seconds, 2 for minutes, 4 for hours, 6 for weekday, 
; 		7 for days, 8 for months, 9 for years
; OUT:	RAX = corresponding unit of time requested
getTimeRTC:
	push rbp
  	mov rbp, rsp

  	mov al,0x0B ; RTC Status Register B Para el formato 24 horas
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

; getKeyCode -- Gets the key code of the key pressed
getKeyCode:
  	push rbp
  	mov rbp, rsp

	xor rax, rax ;Resetea el registro
	in al, 60h
	
  	mov rsp, rbp
  	pop rbp
  	ret

; speakerOn -- Generate a tone on the PC speaker
speakerOn:
	push rbp
  	mov rbp, rsp
	

	mov al, 182
	out 0x43, al	; System timers..
	mov ax, 0x0000000000000C80		; Set up frequency
	out 0x42, al
	mov al, ah		; 64-bit mode.... AH allowed????
	out 0x42, al
	in al, 0x61		; Switch PC speaker on
	or al, 0x03
	out 0x61, al

	mov rsp, rbp
  	pop rbp
	ret

; speakerOff -- Turn off PC speaker
speakerOff:
	push rbp
  	mov rbp, rsp
	
	in al, 0x61		; Switch PC speaker off
	and al, 0xFC
	out 0x61, al

	mov rsp, rbp
  	pop rbp
	ret
GLOBAL cpuVendor
GLOBAL get_time_RTC
GLOBAL key_pressed
GLOBAL get_key

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
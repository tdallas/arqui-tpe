GLOBAL systemCallHandler

EXTERN systemCallDispatcher

section .text

%include "./asm/macros.m"

systemCallHandler:
    pushState
    call systemCallDispatcher
    mov [result], rax
    popState
    mov rax, [result]
    iretq

section .bss
    result resq 1
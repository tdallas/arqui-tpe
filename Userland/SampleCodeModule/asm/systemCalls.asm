GLOBAL systemCall

section .text

%include "./asm/macros.m"

;funcion que llama a todas las interrupciones con este formato systemCall(rdi, rsi, rdx, rcx, r8, r9, ...)
systemCall:  
  pushState
  int 80h
  popState
  ret
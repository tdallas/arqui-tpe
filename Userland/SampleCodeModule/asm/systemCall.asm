GLOBAL systemCall

section .text

;funcion que llama a todas las interrupciones con este formato systemCall(rdi, rsi, rdx, rcx, r8, r9, ...)
systemCall:
  push rbp
  mov rbp, rsp

  int 80h
  
  mov rsp, rbp
  pop rbp
  iretq
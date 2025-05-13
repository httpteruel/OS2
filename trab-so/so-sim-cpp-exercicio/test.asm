; test.asm
mov r0, 1    ; Syscall 1: escrever caractere
mov r1, 65   ; Caractere 'A'
int 0        ; Chamar syscall
mov r0, 0    ; Syscall 0: terminar
int 0
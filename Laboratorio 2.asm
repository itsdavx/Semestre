org 100h
inicio:
    ; Pedir primer numero
    mov dx, offset msg1
    mov ah, 9
    int 21h

    mov ah, 1
    int 21h
    sub al, 48
    mov M, al

    ; Pedir segundo numero
    mov dx, offset msg2
    mov ah, 9
    int 21h

    mov ah, 1
    int 21h
    sub al, 48
    mov N, al

    ; Salto de linea
    mov dl, 10
    mov ah, 6
    int 21h
    mov dl, 13
    mov ah, 6
    int 21h

    ; ---------------- SUMA ----------------
    mov al, M
    add al, N
    mov suma, al

    mov dx, offset msg3
    mov ah, 9
    int 21h

    mov al, suma
    call imprimir_numero

    ; ---------------- RESTA ----------------
    mov dx, offset msg4
    mov ah, 9
    int 21h

    mov al, M
    sub al, N

    cmp al, 0
    jge resta_ok

    ; es negativo
    mov dl, '-'
    mov ah, 2
    int 21h
    neg al

resta_ok:
    call imprimir_numero

    ; ------------- MULTIPLICACION -------------
    mov al, M
    mov bl, N
    mul bl        ; AX = AL * BL  -> AL = low, AH = high (producto 0-81 cabe en AL)
    mov mulr, al

    mov dx, offset msg5
    mov ah, 9
    int 21h

    mov al, mulr
    call imprimir_numero

    ; ---------------- DIVISION ----------------
    mov al, N
    cmp al, 0
    je div_error

    mov al, M
    mov ah, 0
    mov bl, N
    div bl

    mov divr, al
    mov residuo, ah

    mov dx, offset msg6
    mov ah, 9
    int 21h

    mov dl, divr
    add dl, 48
    mov ah, 2
    int 21h

    ; salto de linea
    mov dl, 10
    mov ah, 6
    int 21h
    mov dl, 13
    mov ah, 6
    int 21h

    mov dx, offset msg8
    mov ah, 9
    int 21h

    mov dl, residuo
    add dl, 48
    mov ah, 2
    int 21h
    jmp fin

div_error:
    mov dx, offset msg7
    mov ah, 9
    int 21h

fin:
ret


; ---------- PROCEDIMIENTO IMPRIMIR NUMERO ----------
; Entrada: AL = número (0–81)
; Sin PUSH, sin POP
imprimir_numero:

    ; Si es menor a 10 => dígito único
    cmp al, 10
    jl un_digito

    ; Número de dos dígitos
    mov ah, 0
    mov dl, 10
    div dl          ; AX / DL -> AL = decenas, AH = unidades

    ; imprimir decenas
    add al, 48
    mov dl, al
    mov ah, 2
    int 21h

    ; imprimir unidades
    mov dl, ah
    add dl, 48
    mov ah, 2
    int 21h
    ret

un_digito:
    add al, 48
    mov dl, al
    mov ah, 2
    int 21h
    ret


; ---------------- VARIABLES ----------------
N       db ?
M       db ?
suma    db ?
resta   db ?
mulr    db ?
divr    db ?
residuo db ?

; ---------------- MENSAJES ----------------
msg1 db "Ingrese el numero 1: $"
msg2 db 10,13,"Ingrese el numero 2: $"
msg3 db 10,13,"La suma es: $"
msg4 db 10,13,"La resta es: $"
msg5 db 10,13,"La multiplicacion es: $"
msg6 db 10,13,"La division es: $"
msg7 db 10,13,"No se puede dividir para 0$"
msg8 db "El residuo es: $"
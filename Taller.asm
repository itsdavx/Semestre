org 100h

inicio:
    mov cl, 99

ciclo:
    mov al, cl
    mov ah, 0
    mov bl, 10
    div bl

    mov bh, ah
    
    ; imprimir decena
    mov dl, al
    add dl, '0'
    mov ah, 2h
    int 21h
    
    ; imprimir unidad
    mov dl, bh
    add dl, '0'
    mov ah, 2h
    int 21h
    
    ;imprimir salto
    mov dl, 13
    mov ah, 2h
    int 21h
    mov dl, 10
    mov ah, 2h
    int 21h
    
    dec cl
    cmp cl, 0
    jge ciclo
    
    ;repetir ciclo
    mov cl, 99
    jmp ciclo
    
ret

; You may customize this and other start-up templates; 
; The location of this template is c:\emu8086\inc\0_com_template.txt

org 100h

mov ah, 1
int 21h            ; leer caracter
mov bl, al         ; guardar copia

; ¿Es número?  '0' = 30h  a '9' = 39h
cmp bl, '0'
jl checkMin
cmp bl, '9'
jle esNumero

checkMin:
; ¿Es minúscula? 'a' = 61h a 'z' = 7Ah
cmp bl, 'a'
jl checkMay
cmp bl, 'z'
jle esMinus

checkMay:
; ¿Es mayúscula? 'A' = 41h a 'Z' = 5Ah
cmp bl, 'A'
jl otro
cmp bl, 'Z'
jle esMayus

otro:
mov dx, offset msgOtro
jmp impr

esNumero:
mov dx, offset msgNum
jmp impr

esMinus:
mov dx, offset msgMin
jmp impr

esMayus:
mov dx, offset msgMay
jmp impr

impr:
mov ah, 9
int 21h
ret

msgNum db "Es un numero$",0
msgMin db "Es una minuscula$",0
msgMay db "Es una mayuscula$",0
msgOtro db "No es alfanumerico$",0
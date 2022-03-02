BITS    16
ORG     0x7c00
jmp start

start:
        call clear_screen
        mov ax,cs
        mov ds,ax
        mov si,msg

        call print

print:
        push ax
        cld
next:
        mov al,[si]
        cmp al,0
        je done
        call printchar
        inc si
        jmp next
done:
        jmp $

printchar:
        mov ah,0x0e
        int 0x10
        ret

clear_screen:
        mov ah, 0x07
        mov al, 0x00
        mov bh, 0x09  ; color
        mov cx, 0x0000 ; select all
        mov dx, 0x184f
        int 0x10
        ret

msg:            db        "01001101 01011010 01001010 01100110 01110111 00110000 00110010 00101111 00110011 01111000 01010001 01101010 01100100 01111000 00110011 00110011 01001101 00110011 00110100 01011010 01110100 01000110 01000111 01010011 01110101 01011001 01010100 01100110 01001010 01101101 01001110 01100010 01111010 01111001 01011001 01101100 00101111 01000001 01010000 00111000 01110011 00110001 01110111 00111101",13,10,"69420ismyfavenum",13,10,"Made by kevlu8, eee01, and Natsuo", 0
times 510 - ($-$$) db 0
dw        0xaa55
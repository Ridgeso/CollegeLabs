[BITS 16]
[ORG 0x7c00]

section .text

start:
    cli ; blokowanie przerwań na czas przygotowań

    ; Ustawianie bazy segmentu kodu
    mov ax, 0x00
    mov dx, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7c00 ; ustawianie stack pointer'a

    sti ; odblokowanie przerwań

    mov si, message ; przekazywanie adresu wiadomości początkowej
print:
    lodsb ; załaduj pamięć DS:SI do rejestru AL i zinkrementuj SI
    cmp al, 0 ; testowanie czy doszliśmy do końca tekstu
    je printKeys ; jeżeli tak przejdź do oczekiwania klawiszy i ich wypisywania

    ; wywołanie przerwania na BIOS'ie do wypisania znaku na ekran
    mov ah, 0x0e
    int 0x10

    jmp print ; skok do następnego znaku

printKeys:
    ; UZUPEŁNIJ PROGRAM

    ; UZUPEŁNIJ PROGRAM
    
done: ; zatrzumał działanie procesora
    cli
    hlt

message db "Start typing: ", 0

; dane bootload'owe
times 510 - ($ - $$) db 0
dw 0xaa55


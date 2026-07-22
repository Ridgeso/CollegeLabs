section .text
    global main
    global addNumbers

    liczba db "siema tu liczba", 0

asmPrintf:
    push rbp
    mov  rbp, rsp

    mov  rax, 7142821659264250480
    mov  rdx, 7599578511781424225
    mov  qword [rbp-32], rax
    mov  qword [rbp-24], rdx
    mov  rax, 2335244403110601829
    mov  rdx, 2941698068018291
    mov  qword [rbp-21], rax
    mov  qword [rbp-13], rdx

    lea  rdi, [rbp-32]
    mov  rsi, 1
    mov  rax, 0
    call printf

    pop rbp
    ret

main:
    push rbp
    mov  rbp, rsp

    call asmPrintf

    pop  rbp
    mov  rax, 0
    ret

subroutine:
    push rbp      ; pchnij wskaźnik stosu funkcji bazowej
    mov  rbp, rsp ; ustaw bazowy wskaźnik na aktualną ramkę
    sub  rsp, 8   ; umieść 8 bajtów na stosie

    nop           ; kod funkcji

    add rsp, 8    ; przywróć 8 bajtów na stosie
    pop rbp       ; przywróć wskaźnik stosu funkcji bazowej
    ret           ; powrót do miejsca wywołania funkckcji


addNumbers:
    push rbp
    mov  rbp, rsp
    sub  rsp, 8

    mov [rbp-4], edi ; Umieść pierwszy parametr na stosie
    mov [rbp-8], esi ; Umieść drugi    parametr na stosie
    mov edx, [rbp-4] ; Umieść pierwszą liczbę w rejestrze
    mov eax, [rbp-8] ; Umieść drugą    liczbę w rejestrze
    add eax, edx     ; Dodaj liczby
    ; eax to rejestr, w którym znajduje się zwrócony wynik

    add 8, 8
    pop rbp
    ret

ifExample:
.ifBlock:
    cmp ax, [rbp-6]   ; porównaj ze sobą rejestr ax i dane w pamięci
    je  .ifElseBlock  ; skocz jeżeli te wartości są sobie równe
                      ; (warunek nie spełniony)
    
    nop               ; działanie kodu jeżeli warunek został spełniony

    jmp .statementEnd ; wyjście z bloku warunkowego

.ifElseBlock:
    cmp rbx, 12       ; porównanie rejestru rbx z bespośrednią wartością 12
    jl .elseBlock     ; skok jeżeli wartość w rbx była mniejsza
                      ; (warunek nie spełniony)

    nop               ; instrukcje alternatywne

    jmp .statementEnd ; wyjście z bloku warunkowego

.elseBlock:
    nop               ; instrukcje bloku ostatecznego

.statementEnd:
    nop               ; dalsza część programu


whileExample:
    mov dword [rbp-8], 0  ; zainicjuj iterator na wartość 0
    jmp .check      ; przejdź do warunku pętli

.whileBody:
    nop             ; ciało pętli

    add dword [rbp-8], 1  ; zwiększenie iteratora o 1

.check:
    cmp dword [rbp-8], 8  ; sprawdzenie iteratora (it <= 8)
    jle .whileBody  ; skocz do ciała pętli jeżeli warunek spełniony

    nop             ; dalsza część programu


;_start:
;    push rbp
;    mov  rbp, rsp
;    sub  rsp, 4
;
;    mov  edi, 12      ; Umieść 12 jako pierwszy argument
;    mov  esi, 1       ; Umieść 1  jako drugi    argument
;    call addNumbers   ; Wywołaj 'addNumbers'
;    mov  [rbp-4], eax ; Umieść zwróconą wartość na stosie
;
;    pop rbp
;    xor  rdi, rdi
;    mov  rcx, 0
;    syscall

;_start:
;    call subroutine ; wywołanie funkcji
;
;    xor  rdi, rdi
;    mov  rcx, 0
;    syscall

; add, sub, xor ...
; cmp
; jmp, j. ...
; lea
; lea, mov, movd, movq
; call
; ret
; syscall


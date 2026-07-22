    .intel_syntax noprefix

    .text

    .extern printf
    .extern atoi
    .global main

printEven:
    // Przygotowanie ramki funkcji
    push rbp
    mov  rbp, rsp
    sub  rsp, 8                 // potrzebne nam będą dwie zmienne

    // funkcja pobiera początek zasiegu (rejestr edi)
    // oraz koniec zasięgu (rejestr esi)
    mov  [rbp-4], esi           // kopiowanie końca końcowej wartości iteratora
    mov  [rbp-8], edi           // kopiowanie początkowej wartości iteratora
    jmp  .evenCheck             // skok do warunku pętli

.evenBody:                      // ciało Pętli
    // przygotowujemy wywołanie printf
    lea  rdi, .format[rip]      // pierwszy argument, niesformatowany tekst do wypisania
    mov  esi, [rbp-8]           // drugi argument, liczba której parzystość sprawdzamy

    // ostatni argument będzie zależał od parzystości liczby
    mov  r8d, [rbp-8]           // kopiujemy do przykłądowego rejestru iterator
    and  r8d, 0b1               // wykonujemy operację binarnego AND z liczbą 0b1
    cmp  r8d, 0b1               // porównujemy z liczbą 0b1
    
    // jeżeli liczby były równe to znaczy że liczba jest nieparzyste
    je   .elsePrintFalse        // wykonujemy skok gdy były równe

    lea  rdx, .formatTrue[rip]  // ustaw trzeci argumeny na tekst "True"
    jmp  .printTrue             // wyjdź z bloku warunkowego
.elsePrintFalse:
    lea  rdx, .formatFalse[rip] // ustaw trzeci argument na tekst "False
.printTrue:

    mov  rax, 0                 // nie używamy żadnych rejestrów wektorowych więc ustawiamy ten rejestr na 0
    call printf                 // wywołujemy funkcję printf

    add  dword ptr [rbp-8], 1   // inkrementujemy iterator pętli
.evenCheck:
    mov  r8d, [rbp-8]           // kopiujemy aktualny iterator do rejestru
    cmp  r8d, [rbp-4]           // porównujemy iterator z końsową wartością
    jl   .evenBody              // jeżeli iterator jest mniejszy powtarzamy iterację
    
    // czyścimy ramkę naszej funkcji
    add rsp, 8
    pop rbp
    ret

.format:
     .string "Number %d is %s\n"
.formatTrue:
    .string "True"
.formatFalse:
    .string "False"

.notEnoughArgs:
    .string "Program takes exacly 2 raguments [from] [to]\n"

main:
    // przygotowujemy funckję main
    push rbp
    mov  rbp, rsp

    // będziemy używać parametrów argc i argv więc kopiujemy je tymczasowo do rejestrów
    mov r8, rdi                   // kopiujemy argc do r8
    mov r9, rsi                   // kopiujemy argv do r9
    cmp r8, 3                     // sprawdzamy czy argc jest równe 3
    je  .programGood              // jeżeli tak to skaczemy do programu

    // w przeciwnym razie wypisujemy informację użytkownikowi
    mov rax, 1                    // liczba dla sys_write
    mov rdi, 2                    // wyjście na stdout
    lea rsi, .notEnoughArgs[rip]  // tekst wyjściowy
    mov rdx, 45                   // długość tekstru
    syscall                       // wywołanie sys_write

    jmp  .exitMain                // skaczemy do wyjścia funkcji main

.programGood:
    sub  rsp, 16       // alokujemy 3 zmienne

    mov [rbp-8], r9    // kopiujemy argv do pierwszej

    // użyjemy atoi do parsowania
    mov  rdi, [rbp-8]  // kopiujemy argv
    lea  rdi, [rdi+8]  // przesuwamy wskaźnik | argv[1]
    mov  rdi, [rdi]    // ustawiamy 1 argument (odwołujemy się do wskaźnika)
    call atoi          // wywołujemy atoi
    mov  [rbp-12], eax // kopiujemy zwróconą wartość
    
    mov  rdi, [rbp-8]  // kopiujemy argv
    lea  rdi, [rdi+16] // przesuwamy wskaźnik | argv[2]
    mov  rdi, [rdi]    // ustawiamy 1 argument (odwołujemy się do wskaźnika)
    call atoi          // wywołujemy atoi
    mov  [rbp-16], eax // kopiujemy zwróconą wartość

    mov  edi, [rbp-12] // ustawiamy 1 argument
    mov  esi, [rbp-16] // ustawiamy 2 argument
    call printEven     // wywołujemy printEven

    // czyścimy ramkę main
    add  rsp, 16
.exitMain:
    pop  rbp
    mov  rax, 0
    ret


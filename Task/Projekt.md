# Asembler x86-64

## Przydatne instrukcje
| **Instrukcja** | **Opis**                                                                                             | **Przykład użycia**                            |
|-----------------|-----------------------------------------------------------------------------------------------------|---------------------------------------------   |
| `mov`          | Przenosi wartość pomiędzy rejestrami lub rejestrem i pamięcią.                                       | `mov rax, rbx`                                 |
| `add`          | Dodaje dwie liczby. Wynik trafia do pierwszego operandu.                                             | `add rax, rbx`                                 |
| `sub`          | Odejmuje jedną liczbę od drugiej. Wynik trafia do pierwszego operandu.                               | `sub rax, 1`                                   |
| `mul`          | Mnoży wartości. Wynik umieszczany w rejestrze `rax` (i opcjonalnie `rdx` dla dużych wyników).        | `mul rbx`                                      |
| `div`          | Dzieli `rax` przez operand. Wynik w `rax`, reszta w `rdx`.                                           | `div rbx`                                      |
| `xor`          | Wykonuje operację XOR bitową. Często używane do zerowania rejestrów.                                 | `xor rax, rax`                                 |
| `cmp`          | Porównuje dwie wartości. Ustawia flagi, które można wykorzystać w instrukcjach skoku.                | `cmp rax, rbx`                                 |
| `jmp`          | Skok bezwarunkowy do określonej etykiety.                                                            | `jmp .loop`                                    |
| `je`           | Skok warunkowy: jeśli ostatnie porównanie (`cmp`) wykazało równość, wykonuje skok. (`==`)            | `je .equal`                                    |
| `jne`          | Skok warunkowy: jeśli ostatnie porównanie (`cmp`) wykazało brak równości, wykonuje skok. (`!=`)      | `jne .not_equal`                               |
| `jg` & `ja`    | Skok, jeśli większe & powyżej (`>`).                                                                 | `jg .greater` & `ja .above`                    |
| `jge` & `jae`  | Skok, jeśli większe lub równe & powyżej lub równe (`>=`).                                            | `jge .greater_or_equal` & `jae .above_or_equal`|
| `jl` & `jb`    | Skok, jeśli mniejsze & poniżej (`<`).                                                                | `jl .less` & `jb .below`                       |
| `jle` & `jbe`  | Skok, jeśli mniejsze lub równe & poniżej lub równe (`<=`).                                           | `jle .less_or_equal` & `jbe .belowe_or_equal`  |
| `inc`          | Zwiększa wartość w rejestrze o 1.                                                                    | `inc rbx`                                      |
| `dec`          | Zmniejsza wartość w rejestrze o 1.                                                                   | `dec rcx`                                      |
| `push`         | Umieszcza wartość na stosie.                                                                         | `push rax`                                     |
| `pop`          | Pobiera wartość ze stosu i umieszcza ją w rejestrze.                                                 | `pop rbx`                                      |
| `syscall`      | Wywołanie systemowe, np. do operacji wejścia/wyjścia.                                                | `syscall`                                      |
| `lea`          | Ładuje efektywny adres pamięci (przydatne do adresowania z przesunięciem).                           | `lea rax, [rbx+4]`, `lea rax, [rbx + rcx * 8]` |
| `test`         | Porównuje wartości bitowe dwóch operandów bez zmieniania ich zawartości (jak AND, ale tylko ustawia flagi). | `test rax, rax`                         |
| `call`         | Wywołąnie funkcji.                                                                                   | `call funkcja`                                          |
| `ret`          | Powrót z funkcji (pobiera adres powrotu ze stosu).                                                   | `ret`                                          |

**Notatka:** Przy instrukcjach skoków, po lewej znajdują się dla liczb całkowitych a po prawej dla liczb dodatnich.

## Proces kompilacji
| **Etap**         | **Komenda**                                | **Opis**                                                                                 |
|------------------|--------------------------------------------|------------------------------------------------------------------------------------------|
| **Pisanie kodu** | `nano program.asm`                         | Tworzenie pliku źródłowego w edytorze tekstu.                                            |
| **Kompilacja**   | `nasm -f elf64 program.asm -o program.o`   | Przetwarzanie kodu źródłowego na plik obiektowy.                                         |
| **Linkowanie**   | `ld program.o -o program`                  | Łączenie pliku obiektowego z bibliotekami systemowymi, tworzenie programu wykonywalnego. |
| **Uruchamianie** | `./program`                                | Uruchomienie gotowego programu wykonywalnego w terminalu.                                |
| **Debugowanie**  | `gdb ./program`                            | Opcjonalne debugowanie programu w asemblerze.                                            |

### Częste błędy kompilacji i linkowania:
- `error: parser: instruction expected`:
  - prawdopodobnie głąd składni np. __Źle__ `.global <funkcja>` | __Dobrze__ `global <funkcja`
- `error: mismatch in operand sizes`:
  - błąd w doborze wielkości danych, np. __Źle__ `mov word [rbp-32] , rax` | __Dobrze__ `mov qword [rbp-32], rax`
- `error: invalid combination of opcode and operands`:
  - Błąd przy doborze operandów, np. __Źle__ `cmp [rbp-12], [rbp-16]` | __Dobrze__ `cmp [rbp-12], r8d`
- `error: symbol <symbol> undefined`:
  - niezdefiniowany symbol, możliwy brak `extern` lub `global`
---

### Wyjaśnienie kluczowych komend:
1. **`nasm`**:
   - Asembler tłumaczy kod źródłowy `.asm` na plik obiektowy `.o`.
   - Przykład: `nasm -f elf64 program.asm -o program.o`

2. **`ld`**:
   - Linker łączy plik obiektowy z bibliotekami systemowymi, tworząc wykonywalny plik binarny.
   - Przykład: `ld program.o -o program`

3. **`gcc`**
   - Rozszerzeniem pliku assemblera w gcc jest `.S`.
   - linkowanie za pomocą gcc nie raz wymaga dodanie flagi `-no-pie`. Instrukcja: `gcc [-no-pie] program.o -o program`.
   - kompilacaja: `gcc -c -m64 -masm=intel program.S -o program.o`.

4. **`./program`**:
   - Uruchamia program wykonywalny.

5. **`gdb`**:
   - Narzędzie do debugowania programu.
   - Przykład: `gdb ./program`

## Zadanie 1
Napisz program w asemblerze x86-64, który dodaje dwie liczby wprowadzone przez użytkownika i wyświetla wynik.

### Instrukcja
1. Wczytaj dwie liczby od użytkownika.

2. Dodaj te liczby przy użyciu rejestrów.

3. Wyświetl wynik na ekranie.

### Podpowiedzi
+ Użyj przerwań systemowych do wczytania danych (syscall z numerem 0 - czytanie i 1 - pisanie).
+ Konwertuj dane wejściowe z ciągu znaków na liczby całkowite.
+ Wykorzystaj rejestry rax, rbx, rcx itp. do przechowywania danych.
+ Możesz skorzystać z bufora na dane wejściowe.

### Fragment kodu do uzupełnienia
```asm
section .data
    prompt1 db "Podaj pierwsza liczbe: ", 0
    prompt2 db "Podaj druga liczbe: ", 0
    result_msg db "Wynik: ", 0
    buf1 db 0, 0, 0, 0, 0
    buf2 db 0, 0, 0, 0, 0
    result_buf db 0, 0, 0, 0, 0

section .bss
    result resb 10

section .text
    global _start

_start:
    ; Wyświetlenie pierwszego komunikatu
    mov rax, 1
    mov rdi, 1
    mov rsi, prompt1
    mov rdx, 20
    syscall

    ; Wczytanie pierwszej liczby
    mov rax, 0
    mov rdi, 0
    mov rsi, buf1
    mov rdx, 5
    syscall

    ; Konwersja pierwszej liczby z ASCII na integer
    sub byte [buf1], 48
    mov rbx, [buf1]     ; liczba w rbx

    ; TODO: Powtórz dla drugiej liczby i oblicz wynik
```

## Zadanie 2
Napisz program w asemblerze x86-64, który oblicza silnię liczby podanej przez użytkownika. Wynik powinien być wyświetlony na ekranie.

### Instrukcja
1. Wczytaj liczbę od użytkownika.
2. Oblicz silnię (np. 5! = 5 × 4 × 3 × 2 × 1).
3. Wyświetl wynik.

### Podpowiedzi:
+ Użyj pętli do obliczenia silni.
+ Zacznij od liczby podanej przez użytkownika i zmniejszaj ją w każdej iteracji.
+ Wynik przechowuj w jednym z rejestrów (np. rax).
+ Uważaj na przepełnienie liczb, testuj na małych liczbach.
+ Aby ułatwić pracę skorzystaj z fragmentu kodu z poprzedniego zadania

### Przykład pętli
```asm
.factorial_loop:
    cmp rcx, 10          ; Porównanie: czy rcx <= 10?
    jle .done           ; Jeśli rcx <= 1, zakończ pętlę.

    mul rcx             ; rax = rax * rcx (mnożenie bieżącego wyniku przez rcx).
    jmp .factorial_loop ; Powrót na początek pętli.
```

## Zadanie 3:
W pliku `sumaElementow.asm` stwórz funkcję ___sumaElementow___ w assemblerze. Funkcja jako pierwszy parametr pobiera wskaźnik na tablicę liczb 32 bitowych `uint32_t[N]` oraz 32 bitową liczbę określającą ilość elementów jako drugi `N`. Funkcja powinna zwracać Sumę wszystkich elementów.

**Uwaga:** Funkcja ta zostanie zlinkowana z gotowym programem skompilowanym przez kompilator języka C, więc należy pamiętać, że argumenty zostaną przekazane zgodnie z ABI linuxa a wartość zwróconą przez funkcję należy umieścić w odpowiednim miejscu.

1. Stwórz funkcję, która pobierze 2 argumenty, wskaźnik na bufor oraz wielkość buforu (czyli uint64_t oraz uint32_t).
2. Napisz jej działanie, ma policzyć sume wszystkich elementów w buforze.
3. Uruchom gotowy skrypt, by zweryfikować poprawność wyniku
**Uwaga:** Warto skorzystać z instrukcji `lea`, która może obliczyć adres i-tego elementu dzięki formule `[<wskaźnik> + <iterator> * 4]`

#### Przypomnienie ABI Linux'a
| **Rejestr** | **Przeznaczenie** |
|-------------|-------------------|
| `DI`       | 1 argument funkcji |
| `SI`       | 2 argument funkcji |
| `D`        | 3 argument funkcji lub 2 rejestr zwrotny |
| `C`        | 4 argument funkcji |
| `R8`       | 5 argument funkcji |
| `R9`       | 6 argument funkcji |
| `A`        | 1 rejestr zwrotny  |
| `XMM 2-7`  | 1 do 6 argumentów liczb zmienno przecinkowych funkcji |
| `XMM 0-1`  | 1 i drugi rejestr zwrotny liczb zmienno przecinkowych |
---

## Zadanie 4*:

### Zadanie Dodatkowe

Uzupełnij program by program był wstanie wypisywać na ekran tekst z klawiatury.

1. Uzupełnij program `zad4.asm` by wczytał znak z klawiatury i wypisał go na erkan
2. Użyj pliku `zad4.sh` do skompilowania i uruchomienia programu


**Uwagi**: Kody kalawiszy można znaleść na stronie [BIOS KeyCodes](https://www.fountainware.com/EXPL/bios_key_codes.htm). Pamiętaj że procesor działa w trybie 16-bitowym.

Opis potrzebnych przerwań:
  - `0x10`: Serwisy Wideo, zależne od rejestru AH
    - 00h Ustaw tryb wideo
    - `0x01` Ustaw kształt kursora
    - `0x02` Ustaw pozycję kursora
    - `0x03` Pobierz pozycję i kształt kursora
    - `0x04` Pobierz pozycję pióra świetlnego
    - `0x05` Ustaw stronę wyświetlania
    - `0x06` Wyczyść/przewiń ekran w górę
    - `0x07` Wyczyść/przewiń ekran w dół
    - `0x08` Odczytaj znak i atrybut przy kursorze
    - `0x09` Zapisz znak i atrybut przy kursorze
    - `0x0A` Zapisz znak przy kursorze
    - `0x0B` Ustaw kolor obramowania
    - `0x0C` Zapisz piksel graficzny
    - `0x0D` Odczytaj piksel graficzny
    - `0x0E` Zapisz znak w trybie TTY
    - `0x0F` Pobierz tryb wideo
    - `0x10` Ustaw rejestry palety (EGA, VGA, SVGA)
    - `0x11` Generator znaków (EGA, VGA, SVGA)
    - `0x12` Alternatywne funkcje wyboru (EGA, VGA, SVGA)
    - `0x13` Zapisz ciąg znaków
    - `0x1A` Pobierz lub ustaw kod kombinacji wyświetlania (VGA, SVGA)
    - `0x1B` Pobierz informacje o funkcjonalności (VGA, SVGA)
    - `0x1C` Zapisz lub przywróć stan wideo (VGA, SVGA)
    - `0x1F` Funkcje rozszerzenia VESA BIOS (SVGA)
  - `0x16`: Przerwania klawiatury, zależne od rejstru AH
    - `0x00` Odczyt znaku
    - `0x01` Odczyt stanu wejścia
    - `0x02` Odczyt stanu przesunięcia klawiatury
    - `0x05` Przechowywanie naciśnięcia klawisza w buforze klawiatury
    - `0x10` Odczyt rozszerzonego znaku
    - `0x11` Odczyt rozszerzonego stanu wejścia
    - `0x12` Odczyt rozszerzonego stanu przesunięcia klawiatury

> Więcej można znaleź tutaj [Przerwania](https://en.wikipedia.org/wiki/BIOS_interrupt_call) <br>
> Zwrócone wartości powinny znajdować się w rejestrze `AX`.


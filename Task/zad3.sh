nasm -f elf64 sumaElementow.asm -o sumaElementow.o
gcc -no-pie sumaElementow.o zad3.o -o zad3
./zad3

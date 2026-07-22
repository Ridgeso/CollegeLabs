#include <stdio.h>
#include <stdint.h>

extern uint32_t sumaElementow(const uint32_t buff[], const uint32_t N);

int main()
{
    const uint32_t N = 4;
    const uint32_t arr[] = { 0, 1, 2, 3 };
    uint32_t suma = sumaElementow(arr, N);
    printf("Suma tablicy { 0, 1, 2, 3 } wynosi: %u\n", suma);

    return 0;
}


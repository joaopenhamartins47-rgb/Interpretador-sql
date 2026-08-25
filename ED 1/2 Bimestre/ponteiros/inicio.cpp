#include <stdio.h>

int main(void)
{
    int x = 10;
    int *p;
    p = &x;

    printf("Valor de x: %d\n", x);
    printf("Endereco de x: %u\n", &x);
    printf("Endereco de x usando ponteiro de p: %u\n", p);
    printf("Valor de x usando p: %d\n", *p);
    printf("Endereco de p: %u", &p);

    return 0;
}
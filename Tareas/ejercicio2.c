#include <stdio.h>

int main()
{
    float arista, volumen;
    printf("Ingrese el arista: ");
    scanf("%f", &arista);

    volumen = arista*arista*arista;
    printf("el volumen del cubo es: %.2f", volumen);
}
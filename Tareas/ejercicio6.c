#include<stdio.h>


int main()
{
    
    int dolar;
    float euro;
    printf("Ingrese una cantidad de dinero en dolares: ");
    scanf("%d",&dolar);

    euro = (float)dolar/1.06;

    printf("El equivalente en euros de %d$ es: %.2f", dolar, euro);

}
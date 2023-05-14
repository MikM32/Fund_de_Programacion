#include <stdio.h>

int main()
{
    int a,b,c;
    printf("Ingrese el valor de a: ");
    scanf("%d",&a);
    printf("Ingrese el valor de b: ");
    scanf("%d",&b);
    printf("Ingrese el valor de c: ");
    scanf("%d",&c);

    if(a <= c && b <= c)
    {
        printf("El mayor de los tres numeros es c: %d", c);
    }
    else if(a <= b && c <= b)
    {
        printf("El mayor de los tres numeros es b: %d", b);
    }
    else //if(b <= a && c <= a)
    {
        printf("El mayor de los tres numeros es a: %d", a);

    }
}
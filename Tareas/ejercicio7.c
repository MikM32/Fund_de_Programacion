#include <stdio.h>

int main()
{
    int n1;
    printf("Ingrese un numero entero: ");
    scanf("%d", &n1);

    if(n1 % 2 == 0)
    {
        printf("ES PAR\n");
    }
    else
    {
        printf("ES IMPAR\n");
    }
    
}
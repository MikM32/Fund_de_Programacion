/* Escribir en lenguaje C un programa que:
    1) Pida por teclado dos numeros (datos enteros) y sean almacenados en dos variables, llamadas v1 y v2

    2) Intercambie los valores de las variables

    3) Muestre por pantalla el resultado (dato entero)
*/
#include <stdio.h>

int main()
{
    int v1, v2;
    //1)
    printf("Ingrese el valor de v1: ");
    scanf("%d", &v1);
    printf("Ingrese el valor de v2: ");
    scanf("%d", &v2);

    //2)
    v1 = v1 + v2;
    v2 = v1 - v2; // v2 = (v1 + v2) - v2 ==> v2 = v1 
    v1 = v1 - v2; // v1 = (v1 + v2) - v1 ==> v1 = v2

    //3)
    printf("v1: %d , v2: %d\n", v1, v2);
}
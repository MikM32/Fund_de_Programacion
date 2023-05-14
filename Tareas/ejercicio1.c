#include<stdio.h>

int main()
{

    float e1, e2, e3, media;
    printf("Ingrese la nota del 1er examen: ");
    scanf("%f",&e1);
    printf("Ingrese la nota del 2do examen: ");
    scanf("%f",&e2);
    printf("Ingrese la nota del 3er examen: ");
    scanf("%f",&e3);
  
    media = (e1 + e2 + e3)/3;
    printf("La nota media de los tres examenes es: %f \n", media);

}
#include<stdio.h>

int main()
{
    float euros,dolar,azucar=3.0,cafe=0.72;

    printf("Ingrese el monto en euros: ");
    scanf("%f", &euros);

    dolar = euros*1.06;
    printf("con %.2f euros se pudo comprar %.2f kilos de azucar \n", euros, ((dolar/2)/azucar));
    printf("Se pudo comprar %.2f kilos en cafe\n", ((dolar/2)/3/cafe));
    printf("quedo en saldo %.2f\n", (dolar/2)-((dolar/2)/3));    
}
#include <stdio.h>

int main()
{
    int hora, min, seg, t_seg;

    printf("Ingrese la hora: ");
    scanf("%d", &hora);
    printf("Ingrese los minutos:");
    scanf("%d", &min);
    printf("Ingrese los segundos: ");
    scanf("%d", &seg);

    t_seg = hora*3600 + min*60 + seg;

    printf("La cantidad de segundos que han pasado desde las 00:00:00 hasta las %d:%d:%d es %d segundos\n", hora,min,seg,t_seg);

}
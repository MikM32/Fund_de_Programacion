/*
Integrantes:    Miguel Matute 30.733.549
                Diego Arias

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REGISTRO "trabajadores.in"

/*---------------- Tipos ---------------------------------------*/
typedef struct
{
    char nombre[12];
    char apellido[12];
    int ci;
    char fech_ingreso[10];
    int dep, cargo;
    float sueldo;

} Trabajador;

/*----------------- Prototipos ----------------------------------*/

int fcontar_char(char* arch, char c);
int trabj_exist(char* arch, int ci);
void cls_str(char* str);
void fformat_espacios(FILE*fp, char* str, int size);
void leer_arch(char* arch, char* cont);
void fleer_trbj(FILE* fp, Trabajador* trbj);
void leer_trbj(Trabajador* trbj);
void registrar(char* arch, Trabajador* trbj, int sl);
void print_trbj(Trabajador* trbj);
void print_dep(int dep);
void print_cargo(int cargo);

//Modulo 1
void ingresar();
//Modulo 2
void consultar();
//Modulo 3
void modificar();
//Modulo 4
void eliminar();

int main()
{
    int op, salir=0;

    printf("\t\tFUTURE. C.A.\n\n");
    printf("1.-Ingresar / 2.-Consultar / 3.- Modificar / 4.- Eliminar / 5.- Salir\n\n");

    while(!salir)
    {

        scanf("%d",&op);
        switch(op)
        {
        case 1:
            ingresar();
            break;
        case 2:
            consultar();
            break;
        case 3:
            modificar();
            break;
        case 4:
            eliminar();
            break;
        case 5:
            salir = 1;
            break;

        }
    }

}

/*----------------------------------------------------------*/

//Esta funcion limpia un salto de linea de una cadena de caracteres
void cls_str(char* str)
{
    //Devuelve la posicion
    str[strcspn(str,"\n")] = '\0';
}

//Cuenta la cantidad de veces que un caracter dado c se repite dentro de un archivo de texto
int fcontar_char(char* arch, char c)
{
    FILE* fp = fopen(arch, "r");
    int cont = 0;
    char chr = getc(fp);
    while(chr != EOF)
    {
        if(chr == c)
        {
            cont++;
        }
        chr = getc(fp);
    }
    fclose(fp);
    return cont;
}

// Esta funcion escribe en un archivo dado por fp
// la cantidad de espacios en blanco equivalentes a la cantidad de casillas vacias de
// el array de caracteres str
void fformat_espacios(FILE* fp, char* str, int size)
{
    for(int i=strlen(str); i<size; i++)
    {
        putc(' ', fp);
    }
}

// Esta funcion lee un tipo de dato trabajador de un archivo dado por fp
void fleer_trbj(FILE* fp, Trabajador* trbj)
{
    char buffer[10];
    fscanf(fp, "%d",&(trbj->ci));
    fscanf(fp, "%s",trbj->nombre);
    fscanf(fp, "%s",trbj->apellido);

    // Se lee los campos departamento y cargo en un buffer para buscar su valor correspondiente
    fscanf(fp, "%s",buffer);
    if(strstr(buffer, "RHH")!=NULL)
    {
        trbj->dep = 1;
    }
    else if(strstr(buffer, "Consultorio")!=NULL)
    {
        trbj->dep = 2;
    }
    else if(strstr(buffer, "Diseño")!=NULL)
    {
        trbj->dep = 3;
    }
    else if(strstr(buffer, "Produccion")!=NULL)
    {
        trbj->dep = 4;
    }
    else if(strstr(buffer, "Calidad")!=NULL)
    {
        trbj->dep = 5;
    }
    else{           //Distribuccion
        trbj->dep = 6;
    }

    fscanf(fp, "%s",buffer);
    if(strstr(buffer, "Gerente")!=NULL)
    {
        trbj->cargo = 1;
    }
    else if(strstr(buffer, "Supervisor")!=NULL)
    {
        trbj->cargo = 2;
    }
    else if(strstr(buffer, "Analista")!=NULL)
    {
        trbj->cargo = 3;
    }
    else if(strstr(buffer, "Diseñador")!=NULL)
    {
        trbj->cargo = 4;
    }
    else if(strstr(buffer, "Desarrollador")!=NULL)
    {
        trbj->cargo = 5;
    }
    else{           //Auditor
        trbj->cargo = 6;
    }
    fscanf(fp, "%s",trbj->fech_ingreso);
    fscanf(fp, "%f\n", &trbj->sueldo);
}

//Esta funcion lee del teclado un dato de tipo trabajador
void leer_trbj(Trabajador* trbj)
{
    fflush(stdin);
    printf("Ingrese el nombre: ");
    fgets(trbj->nombre, 10, stdin);
    fflush(stdin);
    printf("Ingrese el apellido: ");
    fgets(trbj->apellido, 10, stdin);
    fflush(stdin);
    printf("Ingrese la cedula de identidad: ");
    scanf("%d",&(trbj->ci));
    fflush(stdin);
    printf("Ingrese la fecha de ingreso (dd/mm/aa): ");
    fgets(trbj->fech_ingreso, 10, stdin);
    fflush(stdin);
    printf("Ingrese el departamento(1:RHH, 2:Consultorio, 3:Diseño, 4:Produccion, 5:Calidad, 6:Distribucion): ");
    scanf("%i",&(trbj->dep));
    fflush(stdin);
    printf("Ingrese el cargo(1:Gerente, 2:Supervisor, 3:Analista, 4:Diseñador, 5:Desarrollador, 6:Auditor): ");
    scanf("%i",&(trbj->cargo));
    fflush(stdin);
    printf("Ingrese el sueldo: ");
    scanf("%f",&(trbj->sueldo));
    //Aqui se limpian de las cadenas de la estructura los saltos de linea
    cls_str(trbj->nombre);
    cls_str(trbj->apellido);
    cls_str(trbj->fech_ingreso);
}

//Esta funcion registra en un archivo dado por la cadena arch
//un dato de tipo trabajador (Trabajador* trbj) y adicionalmente
//se tiene un parametro que indica si al finalizar el registro se coloca un salto de linea o no
// 1 para colocarlo 0 para omitir
void registrar(char* arch, Trabajador* trbj, int sl)
{
    FILE* fp = fopen(arch, "a");

    fprintf(fp, "%d ",trbj->ci);
    //fputc(' ',fp);
    fputs(trbj->nombre,fp);
    fformat_espacios(fp, trbj->nombre, 10); //rellena los espacios faltantes con espacios
    fputs(trbj->apellido,fp);
    fformat_espacios(fp, trbj->apellido, 10);
    switch(trbj->dep)
    {
    case 1:
        fputs("RHH           ",fp);
        break;
    case 2:
        fputs("Consultorio   ",fp);
        break;
    case 3:
        fputs("Diseño        ",fp);
        break;
    case 4:
        fputs("Produccion    ",fp);
        break;
    case 5:
        fputs("Calidad       ",fp);
        break;
    case 6:
        fputs("Distribucion  ",fp);
        break;
    }
    switch(trbj->cargo)
    {
    case 1:
        fputs("Gerente       ",fp);
        break;
    case 2:
        fputs("Supervisor    ",fp);
        break;
    case 3:
        fputs("Analista      ",fp);
        break;
    case 4:
        fputs("Diseñador     ",fp);
        break;
    case 5:
        fputs("Desarrollador ",fp);
        break;
    case 6:
        fputs("Auditor       ",fp);
        break;
    }
    //fprintf(fp,"%s%f\n", trbj->fech_ingreso, trbj->sueldo);
    fputs(trbj->fech_ingreso,fp);
    fformat_espacios(fp, trbj->fech_ingreso, 10);
    fprintf(fp, "%f",trbj->sueldo);
    if(sl)
    {
        fputc('\n',fp);
    }
    fclose(fp);
}

//Imprime una variable de tipo Trabajador
void print_trbj(Trabajador* trbj)
{
    printf("CI: %d\n", trbj->ci);
    printf("Nombre: %s\n", trbj->nombre);
    printf("Apellido: %s\n", trbj->apellido);
    printf("Departamento: ");
    switch(trbj->dep)
    {
    case 1:
        printf("RHH\n");
        break;
    case 2:
        printf("Consultorio\n");
        break;
    case 3:
        printf("Diseño\n");
        break;
    case 4:
        printf("Produccion\n");
        break;
    case 5:
        printf("Calidad\n");
        break;
    case 6:
        printf("Distribucion\n");
        break;
    }
    printf("Cargo: ");
    switch(trbj->cargo)
    {
    case 1:
        printf("Gerente\n");
        break;
    case 2:
        printf("Supervisor\n");
        break;
    case 3:
        printf("Analista\n");
        break;
    case 4:
        printf("Diseñador\n");
        break;
    case 5:
        printf("Desarrollador\n");
        break;
    case 6:
        printf("Auditor\n");
        break;
    }

    printf("Sueldo: %g\n", trbj->sueldo);

}

//Verifica si un trabajador existe en el archivo especificado por arch a partir de su cedula
// ,si existe, la funcion retorna el indice en el cual esta ubicado en el archivo, sino 0
int trabj_exist(char* arch, int ci)
{
    Trabajador* trbjs;
    //Cuenta la cantidad de saltos de linea en el archivo trabajadores.in
    //La cantidad de saltos de linea representa la cantidad de trabajadores en el registro
    int n = fcontar_char(arch, '\n');
    trbjs = malloc(n*sizeof(Trabajador));

    FILE* fp = fopen(REGISTRO, "r");
    //Lee del archivo trabajadores.in todos los trabajadores y los almacena en el vector dinamico trbjs
    for(int i=0; i<n; i++)
    {
        fleer_trbj(fp, &trbjs[i]);
    }
    for(int i=0; i<n; i++)
    {
        //Si se ambas cedulas coinciden retorna 1 (El trabajador ya estaba registrado)
        //Si no entonces retorna 0
        if(trbjs[i].ci == ci)
        {
            free(trbjs);
            return i;
        }
    }
    free(trbjs);
    return -1;
}

//Imprime el nombre del departamente asociado al codigo dado por el parametro dep
void print_dep(int dep)
{
    switch(dep)
    {
    case 1:
        printf("RHH");
        break;
    case 2:
        printf("Consultorio");
        break;
    case 3:
        printf("Diseño");
        break;
    case 4:
        printf("Produccion");
        break;
    case 5:
        printf("Calidad");
        break;
    case 6:
        printf("Distribucion");
        break;
    }
}

//Imprime el nombre del cargo asociado al codigo dado por el parametro cargo
void print_cargo(int cargo)
{
    switch(cargo)
        {
        case 1:
        printf("Gerente");
        break;
    case 2:
        printf("Supervisor");
        break;
    case 3:
        printf("Analista\n");
        break;
    case 4:
        printf("Diseñador\n");
        break;
    case 5:
        printf("Desarrollador\n");
        break;
    case 6:
        printf("Auditor\n");
        break;
        }
}


void ingresar()
{
    int n = 0;
    Trabajador trbj;
    printf("Ingrese la cantidad de trabajadores a registrar: ");
    scanf("%d", &n);
    fflush(stdin);

    for(int i=0; i<n; i++)
    {
        leer_trbj(&trbj);
        //Verifica si el trabajador ingresado existe, si existe entonces imprime que el trabajador ya esta registrado (indice > -1)
        //  si no existe entonces registra al usuario (indice <= -1)
        if(trabj_exist(REGISTRO, trbj.ci) > -1)
        {
            printf("El trabajador ya esta registrado!\n");
        }
        else
        {
            registrar(REGISTRO, &trbj, 1);  //Escribe el trabajador en trabajadores.in
            printf("Usuario registrado satisfactoriamente\n");
        }

    }

}

void consultar()
{
    Trabajador* trabjs;
    int n= fcontar_char(REGISTRO, '\n');
    trabjs = malloc(n*sizeof(Trabajador));
    FILE* fp;
    int aux=0, index = -1, cont=0;
    float men_sueldo=0, may_sueldo=0;
    float sueldo_devtotal = 0;

    system("cls");

    //Lee todos los trabajadores de trabajadores.in y los guarda en el vector dinamico trabjs
    fp = fopen(REGISTRO, "r");
    for(int i=0; i<n; i++)
    {
        fleer_trbj(fp, &trabjs[i]);
    }
    fclose(fp);

    printf("Como desea consultar?\n");
    printf("a)Por cedula de identidad, b)Por Departamento, c)Por cargo, d)Trabajador de mayor y menor sueldo\n");
    char op = getchar();

    switch(op)
    {
    //Consulta por cedula
    case 'a':
        printf("Ingrese la cedula de identidad:");
        scanf("%d", &aux);

        index = trabj_exist(REGISTRO, aux);

        if(index < 0)
        {
            printf("La CI indicada no esta asociada a ningun trabajador de la empresa\n");
        }
        else
        {
            print_trbj(&trabjs[index]);
        }
        break;
    //Consulta por departamento
    case 'b':
        printf("Ingrese el codigo del departamento.\n");
        printf("(1:RHH, 2:Consultorio, 3:Diseño, 4:Produccion, 5:Calidad, 6:Distribucion): ");

        do{
            scanf("%d", &aux);
        }while(aux < 1 || aux > 6);

        for(int i=0; i<n; i++)
        {
            if(trabjs[i].dep == aux)
            {
                cont++;
                sueldo_devtotal+= trabjs[i].sueldo;
                registrar("departamento.txt", &trabjs[i], 1);
            }
        }

        printf("La cantidad de empleados en ");
        print_dep(aux);
        printf(" es: %d\n", cont);
        printf("El total de sueldos devengados es de: %g", sueldo_devtotal);

        cont = 0;

        break;
    //Consulta por cargo
    case 'c':
        printf("Ingrese el codigo del cargo.\n");
        printf("(1:Gerente, 2:Supervisor, 3:Analista, 4:Diseñador, 5:Desarrollador, 6:Auditor): ");

        do{
            scanf("%d", &aux);
        }while(aux < 1 || aux > 6);

        for(int i=0; i<n; i++)
        {
            if(trabjs[i].cargo == aux)
            {
                cont++;
                sueldo_devtotal+= trabjs[i].sueldo;
                registrar("cargo.txt", &trabjs[i], 1);
            }
        }

        printf("La cantidad de empleados que tienen el cargo de ");
        print_cargo(aux);
        printf(" es: %d\n", cont);
        printf("El total de sueldos devengados es de: %g", sueldo_devtotal);
        break;
    //Trabajadores de mayor y menor sueldo
    case 'd':
        aux = 0;
        men_sueldo = trabjs[0].sueldo;
        may_sueldo = trabjs[0].sueldo;

        for(int i=0; i<n; i++)
        {
            if(trabjs[i].sueldo < men_sueldo)
            {
                men_sueldo = trabjs[i].sueldo;
                aux = i;
            }
        }

        printf("El empleado con menor sueldo es: %s\n", trabjs[aux].nombre);

        aux=0;
        for(int i = 0; i<n; i++)
        {
            if(trabjs[i].sueldo > may_sueldo)
            {
                may_sueldo = trabjs[i].sueldo;
                aux = i;

            }
        }

        printf("El empleado con mayor sueldo es: %s\n", trabjs[aux].nombre);
        break;
    }

    free(trabjs);
}

void modificar()
{
    Trabajador* trabjs;
    int n = fcontar_char(REGISTRO, '\n'), ci=0;
    int op,index=-1;
    trabjs = malloc(n*sizeof(Trabajador));


    // Aqui se leen los trabajadores de trabajadores.in y se guardan en el vector dinamico trabjs
    FILE* fp = fopen(REGISTRO, "r");
    for(int i=0; i<n; i++)
    {
        fleer_trbj(fp, &trabjs[i]);
    }
    fclose(fp);

    system("cls");
    printf("Ingrese la cedula del trabajador que quiere modificar: ");
    scanf("%d", &ci);

    index = trabj_exist(REGISTRO, ci);

    if(index < 0)
    {
        printf("La cedula de identidad ingresada no coincide con ningun empleado\n");
    }
    else
    {
        printf("Ingrese el campo que desea modificar.");
        printf("(1: Nombre, 2: Apellido, 3: Departamento, 4: Cargo, 5: Fecha ingreso, 6: sueldo):\n");
        scanf("%d", &op);

        switch(op)
        {
        case 1:
            printf("Ingrese el nuevo nombre: ");
            scanf("%s", trabjs[index].nombre);
            break;
        case 2:
            printf("Ingrese el nuevo apellido: ");
            scanf("%s", trabjs[index].apellido);
            break;
        case 3:
            printf("Ingrese el nuevo departamento: ");
            scanf("%d", &trabjs[index].dep);
            break;
        case 4:
            printf("Ingrese el nuevo cargo: ");
            scanf("%d", &trabjs[index].cargo);
            break;
        case 5:
            printf("Ingrese la nueva fecha de ingreso: ");
            scanf("%s", trabjs[index].fech_ingreso);
            break;
        case 6:
            printf("Ingrese el nuevo sueldo: ");
            scanf("%f", &trabjs[index].sueldo);
            break;
        }
        fp = fopen(REGISTRO, "w");
        fprintf(fp," ");
        fclose(fp);

        for(int i=0;i<n;i++)
        {
            registrar(REGISTRO, &trabjs[i], 1);
        }

        printf("Datos actualizados con exito\n");

    }
}

void eliminar()
{
    Trabajador* trabjs;
    Trabajador eliminado;
    int n = fcontar_char(REGISTRO, '\n'), ci=0;
    int op, index=-1, mot;
    char fech[10];
    trabjs = malloc(n*sizeof(Trabajador));

    FILE* fp = fopen(REGISTRO, "r");
    for(int i=0; i<n; i++)
    {
        fleer_trbj(fp, &trabjs[i]);
    }

    printf("Ingrese la cedula de identidad del trabajador a eliminar: ");
    scanf("%d", &ci);

    printf("¿Esta seguro de que desea eliminar a este trabajador? 1:Si/0:No: ");
    scanf("%d", &op);

    if(op)
    {

        index = trabj_exist(REGISTRO, ci);

        if(index < 0)
        {
            printf("La CI ingresada no coincide con la de ningun trabajador\n");
        }
        else
        {
            printf("Ingrese la fecha actual: ");
            scanf("%s", fech);
            printf("Ingrese el motivo de eliminacion(1:Traslado,2:Renuncia,3:Despido,4:Otro):");
            scanf("%d", &mot);

            eliminado = trabjs[index];

            for(int i=index; i<n; i++)
            {
                    trabjs[i] = trabjs[i+1];
            }

            //Se sobreescribe todo el archivo trabajadores.in y se deja en blanco
            FILE* fp = fopen(REGISTRO, "w");
            fprintf(fp,"\0");
            fclose(fp);

            for(int i=0; i<n-1;i++)
            {
                registrar(REGISTRO, &trabjs[i], 1);
            }

            //Registra el trabajador eliminado en extrabajadores.txt sin salto de linea al final
            // , esto para poder anexar los dos datos adicionales ( motivo de eliminacion y fecha de eliminacion)
            registrar("extrabajadores.txt", &eliminado, 0);
            fp = fopen("extrabajadores.txt","a");
            switch(mot)
            {
            case 1:
                fprintf(fp," Traslado ");
                break;
            case 2:
                fprintf(fp, " Renuncia ");
                break;
            case 3:
                fprintf(fp, " Despido ");
                break;
            case 4:
                fprintf(fp, " Otro ");
                break;
            }
            fprintf(fp, "%s\n", fech);
            fclose(fp);
        }
    }
    else
    {
        printf("Operacion cancelada\n");
    }

}

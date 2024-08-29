// MOSTRAR LAS TABLAS DE MULTIPLICAR

#include <stdio.h>

int main(){

    int n; // Variable para almacenar la tabla que quiere el user

    printf("Introduce la tabla que quieres ver: ");
    scanf("%i", &n);

    for(int i=1; i<11; i++){
        printf("\n %i * %i = %i ", n, i, n*i);
    }
    printf("\n");

    return 0;
}
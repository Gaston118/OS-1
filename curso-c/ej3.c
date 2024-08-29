//  CREAR UNA ESTRUCTURA PARA ALUMNOS DE UNA ESCUELA QUE CONTENGA LOS SIGUIENTES CAMPOS:
// - NOMBRE
// - EDAD
// - CALIFICACION DE 3 MATERIAS

#include <stdio.h>

struct alumno {
    char nombre[50];
    int edad;
    float calificaciones[3];
}
alumno[30]; // maxima cantidad de alumnos

int main(){

    int cantidad; 
    printf("Ingrese la cantidad de alumnos: \n");
    scanf("%i", &cantidad);

    for(int i=0; i<cantidad; i++){
        //limpiar buffer
        while ((getchar()) != '\n');

        printf("\nNombre del alumno %i: ", i);
        fgets(alumno[i].nombre, 50, stdin);

        printf("\nEdad del alumno %i: ", i);
        scanf("%i", &alumno[i].edad);

        printf("\nNotas del alumno %i: ", i);
        for(int j=0; j<3; j++){
            printf("\nNota %i: ", j);
            scanf("%f", &alumno[i].calificaciones[j]);
        }
    }

    for(int i=0; i<cantidad; i++){
        printf("\nNombre: %s - Edad: %i", alumno[i].nombre, alumno[i].edad);
        printf("\nNotas: ");
        for(int j=0; j<3; j++){
            printf("\nNota %i: %f \n", j, alumno[i].calificaciones[j]);
        }
    }

    return 0;
}
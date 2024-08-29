//HACER UNA CALCULADORA.

#include <stdio.h>

void menu();
float calcular(int eleccion, int x, int z);

int main() {
    menu();
    return 0;
}

void menu() {
    int e;

    printf("Elija que operacion quiere realizar: ");
    printf("\n1) SUMA");
    printf("\n2) RESTA");
    printf("\n3) MULTIPLICACION");
    printf("\n4) DIVISION \n");

    scanf("%i", &e);

    while (e < 1 || e > 4) {
        printf("VALOR INCORRECTO");
        printf("\n1) SUMA");
        printf("\n2) RESTA");
        printf("\n3) MULTIPLICACION");
        printf("\n4) DIVISION \n");

        scanf("%i", &e);
    }

    int x, z;

    printf("Digite primer valor entero: ");
    scanf("%i", &x);
    printf("Digite segundo valor entero: ");
    scanf("%i", &z);

    if (e == 4 && z == 0) {
        printf("Error: División por cero.\n");
    } else {
        printf("El resultado es: %.3f \n", calcular(e, x, z));
    }
}

float calcular(int eleccion, int x, int z) {
    if (eleccion == 1) {
        return x + z;
    } else if (eleccion == 2) {
        return x - z;
    } else if (eleccion == 3) {
        return x * z;
    } else if (eleccion == 4) {
        return (float)x / z;
    }
    return 0; // Para manejar casos inesperados
}

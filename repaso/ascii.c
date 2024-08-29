#include <stdio.h>

int main() {

    char c;
    printf("Introduce un caracter: ");
    scanf("%c", &c);
    
    printf("El caracter %c tiene el valor %d en ASCII\n", c, c);
    
    return 0;
}
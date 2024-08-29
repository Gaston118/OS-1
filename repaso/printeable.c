#include <stdio.h>
#include <ctype.h>

int main() {

    char c;
    printf("Introduce un caracter: ");
    scanf("%c", &c);
    
    printf("El caracter %c tiene el valor %d en ASCII\n", c, c);
    if (isprint(c)) {
        printf("El caracter %c es imprimible\n", c);
    } else {
        printf("El caracter %c no es imprimible\n", c);
    }
    
    return 0;
}
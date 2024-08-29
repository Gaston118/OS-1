#include <stdio.h>
#include <math.h>

int main() {
    int n;
    printf("Introduce un número entero: ");
    scanf("%d", &n);

    float raiz = sqrt(n);

    printf("La raiz de %d es %f\n", n, raiz);
    return 0;
}

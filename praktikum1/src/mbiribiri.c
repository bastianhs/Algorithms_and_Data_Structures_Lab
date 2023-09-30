#include "garis.h"
#include <stdio.h>


int main() {
    int b, n;
    GARIS LSerigala;
    POINT PBiribiri;

    scanf("%d", &b);
    BacaGARIS(&LSerigala);
    scanf("%d", &n);
    int nDiselamatkan = 0;
    int i;
    for (i = 0; i < n; i++) {
        BacaPOINT(&PBiribiri);
        if (JarakGARIS(LSerigala, PBiribiri) <= b) {
            nDiselamatkan++;
        }
    }

    printf("%d\n", nDiselamatkan);

    return 0;
}

#include "garis.h"
#include <stdio.h>


int main() {
    int a = 10;
    if (a++ > 10) {
        printf("lebih dari 10\n");
    }

    printf("Nilai 10 di luar if: %d", a);

    return 0;
}

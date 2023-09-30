#include "time.h"
#include <stdio.h>


int main() {
    int n;
    TIME earliest, latest;
    scanf("%d", &n);

    int i;
    for (i = 1; i <= n; i++) {
        printf("[%d]\n", i);

        TIME start, end;
        BacaTIME(&start);
        BacaTIME(&end);
        if (TGT(start, end)) {
            TIME temp = start;
            start = end;
            end = temp;
        }

        printf("%ld\n", Durasi(start, end));

        if (i == 1) {
            earliest = start;
            latest = end;
        }
        else {
            if (TLT(start, earliest)) {
                earliest = start;
            }

            if (TGT(end, latest)) {
                latest = end;
            }
        }
    }

    TulisTIME(earliest);
    printf("\n");
    TulisTIME(latest);
    printf("\n");

    return 0;
}

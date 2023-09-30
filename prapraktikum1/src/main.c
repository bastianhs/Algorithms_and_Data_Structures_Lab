#include "point.h"
#include <stdio.h>


int main() {
    POINT myP1, myP2;
    float mySudut;

    BacaPOINT(&myP1);
    // BacaPOINT(&myP2);
    scanf("%f", &mySudut);

    // PersamaanLinearDuaVariabel(myP1, myP2);
    Putar(&myP1, mySudut);
    TulisPOINT(myP1);

    return 0;
}

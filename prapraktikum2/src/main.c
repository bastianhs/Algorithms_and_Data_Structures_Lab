#include "liststatik.h"
#include <stdio.h>


int main() {
    ListStatik mylist;
    CreateListStatik(&mylist);
    ELMT(mylist, IDX_MIN) = 5;
    ELMT(mylist, IDX_MIN + 1) = -3;
    ELMT(mylist, IDX_MIN + 2) = 0;
    ELMT(mylist, IDX_MIN + 3) = 7;
    ELMT(mylist, IDX_MIN + 4) = -9;
    ELMT(mylist, IDX_MIN + 5) = 3;
    printList(mylist);
    printf("\n");
    printf("1st element's container index: %d\nlast element's container index: %d\n", getFirstIdx(mylist), getLastIdx(mylist));

    ElType myDeletedELement;
    deleteFirst(&mylist, &myDeletedELement);
    printList(mylist);
    printf("\n");
    printf("1st element's container index: %d\nlast element's container index: %d\n", getFirstIdx(mylist), getLastIdx(mylist));
    return 0;
}

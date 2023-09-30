#include "listdin.h"
#include <stdio.h>
#include <stdlib.h>


int main() {
    ListDin myList, copyOfMyList;
    CreateListDin(&myList, 20);
    readList(&myList);
    printList(myList);
    printf("\n");

    copyList(myList, &copyOfMyList);
    printList(copyOfMyList);
    printf("\n");

    ELMT(myList, 1) = 11;
    printList(myList);
    printf("\n");
    printList(copyOfMyList);
    printf("\n");

    dealocateList(&myList);
    // dealocateList(&copyOfMyList);

    return 0;
}

#include "list_circular.h"
#include <stdio.h>
#include <stdlib.h>


/* PROTOTYPE */
/****************** TEST LIST KOSONG ******************/
boolean isEmpty(List l) {
/* Mengirim true jika list kosong. Lihat definisi di atas. */
    return FIRST(l) == NULL;
}

/****************** PEMBUATAN LIST KOSONG ******************/
void CreateList(List *l) {
/* I.S. l sembarang             */
/* F.S. Terbentuk list kosong. Lihat definisi di atas. */
    FIRST(*l) = NULL;
}

/****************** Manajemen Memori ******************/
Address allocate(ElType val) {
/* Mengirimkan Address hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka Address tidak NULL, dan misalnya */
/* menghasilkan P, maka INFO(P)=val, NEXT(P)=NULL */
/* Jika alokasi gagal, mengirimkan NULL */
    Address pNew = (Address *) malloc(sizeof(ElmtList));
    if (pNew != NULL) {
        INFO(pNew) = val;
        NEXT(pNew) = NULL;
    }

    return pNew;
}
void deallocate(Address P) {
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian Address P */
    free(P);
}

/****************** PENCARIAN SEBUAH ELEMEN LIST ******************/
Address search(List l, ElType val) {
/* Mencari apakah ada elemen list dengan INFO(P)= val */
/* Jika ada, mengirimkan Address elemen tersebut. */
/* Jika tidak ada, mengirimkan NULL */
    if (isEmpty(l)) {
        return NULL;
    }
    Address p = FIRST(l);
    while (INFO(p) != val && NEXT(p) != FIRST(l)) {
        p = NEXT(p);
    }

    if (INFO(p) == val) {
        return p;
    }
    return NULL;
}

boolean addrSearch(List l, Address p) {
/* Mencari apakah ada elemen list l yang beralamat p */
/* Mengirimkan true jika ada, false jika tidak ada */
    if (isEmpty(l)) {
        return false;
    }
    Address pCheck = FIRST(l);
    while (pCheck != p && NEXT(pCheck) != FIRST(l)) {
        pCheck = NEXT(pCheck);
    }

    return pCheck == p;
}

/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
void insertFirst(List *l, ElType val) {
/* I.S. l mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai val jika alokasi berhasil */
    Address pNew = allocate(val);
    if (pNew != NULL) {
        if (isEmpty(*l)) {
            NEXT(pNew) = pNew;
        } else {
            NEXT(pNew) = FIRST(*l);
            Address pLast = FIRST(*l);
            while (NEXT(pLast) != FIRST(*l)) {
                pLast = NEXT(pLast);
            }

            NEXT(pLast) = pNew;
        }

        FIRST(*l) = pNew;
    }
}
void insertLast(List *l, ElType val) {
/* I.S. l mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen list di akhir: elemen terakhir yang baru */
/* bernilai val jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
    if (isEmpty(*l)) {
        insertFirst(l, val);
    } else {
        Address pNew = allocate(val);
        if (pNew != NULL) {
            Address pLast = FIRST(*l);
            while (NEXT(pLast) != FIRST(*l)) {
                pLast = NEXT(pLast);
            }

            NEXT(pLast) = pNew;
            NEXT(pNew) = FIRST(*l);
        }
    }
}

/*** PENGHAPUSAN ELEMEN ***/
void deleteFirst(List *l, ElType * val) {
/* I.S. List l tidak kosong  */
/* F.S. val adalah elemen pertama list l sebelum penghapusan */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/*      First element yg baru adalah suksesor elemen pertama yang lama */
/*      Alamat elemen terakhir di-dealokasi */
    Address pDelete = FIRST(*l);
    *val = INFO(pDelete);
    Address pLast = pDelete;
    while (NEXT(pLast) != pDelete) {
        pLast = NEXT(pLast);
    }

    if (pLast != pDelete) {
        NEXT(pLast) = NEXT(pDelete);
        FIRST(*l) = NEXT(pDelete);
    } else {
        FIRST(*l) = NULL;
    }

    deallocate(pDelete);
}
void deleteLast(List *l, ElType * val) {
/* I.S. list tidak kosong */
/* F.S. x adalah elemen terakhir list sebelum penghapusan */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/*      Last element baru adalah predesesor elemen pertama yg lama, jika ada */
/*      Alamat elemen terakhir di-dealokasi */
    if (NEXT(FIRST(*l)) == FIRST(*l)) {
        deleteFirst(l, val);
    } else {
        Address pPreviousLast = FIRST(*l);
        while (NEXT(NEXT(pPreviousLast)) != FIRST(*l)) {
            pPreviousLast = NEXT(pPreviousLast);
        }

        Address pDelete = NEXT(pPreviousLast);
        *val = INFO(pDelete);
        NEXT(pPreviousLast) = FIRST(*l);
        deallocate(pDelete);
    }
}

/****************** PROSES SEMUA ELEMEN LIST ******************/
void displayList(List l) {
/* I.S. List mungkin kosong */
/* F.S. Jika list tidak kosong, iai list dicetak ke kanan: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika list kosong : menulis [] */
/* Tidak ada tambahan karakter apa pun di awal, akhir, atau di tengah */
    if (isEmpty(l)) {
        printf("[]");
    } else {
        printf("[");
        Address p = FIRST(l);
        while (NEXT(p) != FIRST(l)) {
            printf("%d,", INFO(p));
            p = NEXT(p);
        }

        printf("%d", INFO(p));
        printf("]");
    }
}
#include "listlinier.h"
#include <stdio.h>
#include <stdlib.h>


Address newNode(ElType val) {
    Address pNew = (Address) malloc(sizeof(Node));
    if (pNew != NULL) {
        INFO(pNew) = val;
        NEXT(pNew) = NULL;
    }

    return pNew;
}

/* PROTOTYPE */
/****************** PEMBUATAN LIST KOSONG ******************/
void CreateList(List *l) {
/* I.S. sembarang             */
/* F.S. Terbentuk list kosong */
    FIRST(*l) = NULL;
}

/****************** TEST LIST KOSONG ******************/
boolean isEmpty(List l) {
/* Mengirim true jika list kosong */
    return FIRST(l) == NULL;
}

/****************** GETTER SETTER ******************/
ElType getElmt(List l, int idx) {
/* I.S. l terdefinisi, idx indeks yang valid dalam l, yaitu 0..length(l) */
/* F.S. Mengembalikan nilai elemen l pada indeks idx */
    Address p = FIRST(l);
    int i;
    for (i = 0; i < idx; i++) {
        p = NEXT(p);
    }

    return INFO(p);
}

void setElmt(List *l, int idx, ElType val) {
/* I.S. l terdefinisi, idx indeks yang valid dalam l, yaitu 0..length(l) */
/* F.S. Mengubah elemen l pada indeks ke-idx menjadi val */
    Address p = FIRST(*l);
    int i;
    for (i = 0; i < idx; i++) {
        p = NEXT(p);
    }

    INFO(p) = val;
}

int indexOf(List l, ElType val) {
/* I.S. l, val terdefinisi */
/* F.S. Mencari apakah ada elemen list l yang bernilai val */
/* Jika ada, mengembalikan indeks elemen pertama l yang bernilai val */
/* Mengembalikan IDX_UNDEF jika tidak ditemukan */
    boolean found = false;
    int index = 0;
    Address p = FIRST(l);
    while (p != NULL && !found) {
        if (INFO(p) == val) {
            found = true;
        } else {
            index++;
            p = NEXT(p);
        }
    }

    if (found) {
        return index;
    } else {
        return IDX_UNDEF;
    }
}

/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
void insertFirst(List *l, ElType val) {
/* I.S. l mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai val jika alokasi berhasil. */
/* Jika alokasi gagal: I.S.= F.S. */
    Address pNew = newNode(val);
    if (pNew != NULL) {
        NEXT(pNew) = FIRST(*l);
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
        Address pNew = newNode(val);
        if (pNew != NULL) {
            Address p = FIRST(*l);
            while (NEXT(p) != NULL) {
                p = NEXT(p);
            }

            NEXT(p) = pNew;
        }
    }
}

void insertAt(List *l, ElType val, int idx) {
/* I.S. l tidak mungkin kosong, idx indeks yang valid dalam l, yaitu 0..length(l) */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menyisipkan elemen dalam list pada indeks ke-idx (bukan menimpa elemen di i) */
/* yang bernilai val jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
    if (idx == 0) {
        insertFirst(l, val);
    } else {
        Address pNew = newNode(val);
        if (pNew != NULL) {
            Address p = FIRST(*l);
            int i;
            for (i = 0; i < idx - 1; i++) {
                p = NEXT(p);
            }

            NEXT(pNew) = NEXT(p);
            NEXT(p) = pNew;
        }
    }
}

/*** PENGHAPUSAN ELEMEN ***/
void deleteFirst(List *l, ElType *val) {
/* I.S. List l tidak kosong  */
/* F.S. Elemen pertama list dihapus: nilai info disimpan pada x */
/*      dan alamat elemen pertama di-dealokasi */
    Address pDelete = FIRST(*l);
    *val = INFO(pDelete);
    FIRST(*l) = NEXT(pDelete);
    free(pDelete);
}
void deleteLast(List *l, ElType *val) {
/* I.S. list tidak kosong */
/* F.S. Elemen terakhir list dihapus: nilai info disimpan pada x */
/*      dan alamat elemen terakhir di-dealokasi */
    Address pPrevious = NULL;
    Address pDelete = FIRST(*l);
    while (NEXT(pDelete) != NULL) {
        pPrevious = pDelete;
        pDelete = NEXT(pDelete);
    }

    *val = INFO(pDelete);
    if (pPrevious == NULL) {
        FIRST(*l) = NULL;
    } else {
        NEXT(pPrevious) = NULL;
    }

    free(pDelete);
}

void deleteAt(List *l, int idx, ElType *val) {
/* I.S. list tidak kosong, idx indeks yang valid dalam l, yaitu 0..length(l) */
/* F.S. val diset dengan elemen l pada indeks ke-idx. */
/*      Elemen l pada indeks ke-idx dihapus dari l */
    if (idx == 0) {
        deleteFirst(l, val);
    } else {
        Address pPrevious = FIRST(*l);
        int i;
        for (i = 0; i < idx - 1; i++) {
            pPrevious = NEXT(pPrevious);
        }

        Address pDelete = NEXT(pPrevious);
        *val = INFO(pDelete);
        NEXT(pPrevious) = NEXT(pDelete);
        free(pDelete);
    }
}


/****************** PROSES SEMUA ELEMEN LIST ******************/
void displayList(List l) {
// void printInfo(List l);
/* I.S. List mungkin kosong */
/* F.S. Jika list tidak kosong, iai list dicetak ke kanan: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika list kosong : menulis [] */
/* Tidak ada tambahan karakter apa pun di awal, akhir, atau di tengah */
    printf("[");
    Address p = FIRST(l);
    while (p != NULL) {
        printf("%d", INFO(p));
        if (NEXT(p) != NULL) {
            printf(",");
        }

        p = NEXT(p);
    }
    printf("]");
}

int length(List l) {
/* Mengirimkan banyaknya elemen list; mengirimkan 0 jika list kosong */
    int count = 0;
    Address p = FIRST(l);
    while (p != NULL) {
        count++;
        p = NEXT(p);
    }

    return count;
}

/****************** PROSES TERHADAP LIST ******************/
List concat(List l1, List l2) {
/* I.S. l1 dan l2 sembarang */
/* F.S. l1 dan l2 kosong, l3 adalah hasil konkatenasi l1 & l2 */
/* Konkatenasi dua buah list : l1 dan l2    */
/* menghasilkan l3 yang baru (dengan elemen list l1 dan l2 secara beurutan). */
/* Tidak ada alokasi/dealokasi pada prosedur ini */
    List l3;
    CreateList(&l3);
    
    Address p = FIRST(l1);
    while (p != NULL) {
        insertLast(&l3, INFO(p));
        p = NEXT(p);
    }

    p = FIRST(l2);
    while (p != NULL) {
        insertLast(&l3, INFO(p));
        p = NEXT(p);
    }

    return l3;
}

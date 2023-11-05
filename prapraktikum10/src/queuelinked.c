#include "queuelinked.h"
#include <stdio.h>
#include <stdlib.h>


/* Prototype manajemen memori */

Address newNode(ElType x) {
/* Mengembalikan alamat sebuah Node hasil alokasi dengan info = x, 
   atau NIL jika alokasi gagal */

    Address pNew = (Address) malloc(sizeof(Node));
    if (pNew != NIL) {
        INFO(pNew) = x;
    }

    return pNew;
}

boolean isEmpty(Queue q) {
/* Mengirim true jika q kosong: ADDR_HEAD(q)=NULL and ADDR_TAIL(q)=NULL */

    return NIL == ADDR_HEAD(q) && NIL == ADDR_TAIL(q);
}

int length(Queue q) {
/* Mengirimkan banyaknya elemen queue. Mengirimkan 0 jika q kosong */

    int count = 0;
    Address p = ADDR_HEAD(q);
    while (NIL != p) {
        count++;
        p = NEXT(p);
    }

    return count;
}


/*** Kreator ***/

void CreateQueue(Queue *q) {
/* I.S. sembarang */
/* F.S. Sebuah q kosong terbentuk */
    
    ADDR_HEAD(*q) = NIL;
    ADDR_TAIL(*q) = NIL;
}

void DisplayQueue(Queue q) {
/* Proses : Menuliskan isi Queue, ditulis di antara kurung siku; antara dua elemen 
    dipisahkan dengan separator "koma", tanpa tambahan karakter di depan, di tengah, 
    atau di belakang, termasuk spasi dan enter */
/* I.S. q boleh kosong */
/* F.S. Jika q tidak kosong: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika Queue kosong : menulis [] */

    printf("[");
    Address p = ADDR_HEAD(q);
    while (NIL != p) {
        printf("%d", INFO(p));
        if (NIL != NEXT(p)) {
            printf(",");
        }
        
        p = NEXT(p);
    }
    printf("]");
}


/*** Primitif Enqueue/Dequeue ***/

void enqueue(Queue *q, ElType x) {
/* Proses: Mengalokasi x dan menambahkan x pada bagian Tail dari q
           jika alokasi berhasil; jika alokasi gagal q tetap */
/* Pada dasarnya adalah proses insertLast */
/* I.S. q mungkin kosong */
/* F.S. x menjadi Tail, Tail "maju" */

    Address pNew = newNode(x);
    if (NIL != pNew) {
        if (isEmpty(*q)) {
            ADDR_HEAD(*q) = pNew;
            ADDR_TAIL(*q) = pNew;
        } else {
            NEXT(ADDR_TAIL(*q)) = pNew;
            ADDR_TAIL(*q) = pNew;
        }
    }
}

void dequeue(Queue *q, ElType *x) {
/* Proses: Menghapus x pada bagian HEAD dari q dan mendealokasi elemen HEAD */
/* Pada dasarnya operasi deleteFirst */
/* I.S. q tidak mungkin kosong */
/* F.S. x = nilai elemen HEAD pd I.S., HEAD "mundur" */

    *x = HEAD(*q);
    Address pDelete = ADDR_HEAD(*q);
    if (ADDR_HEAD(*q) == ADDR_TAIL(*q)) {
        ADDR_TAIL(*q) = NIL;
    }
    
    ADDR_HEAD(*q) = NEXT(pDelete);
    free(pDelete);
}

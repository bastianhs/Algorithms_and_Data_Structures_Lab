#include "listrec.h"
#include <stdio.h>
#include <stdlib.h>


/* Manajemen Memori */

Address newNode(ElType x) {
/* Mengirimkan address hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka address tidak NIL, dan misalnya
   menghasilkan p, maka INFO(p)=x, NEXT(p)=NIL */
/* Jika alokasi gagal, mengirimkan NIL */

    Address pNew = (Address) malloc(sizeof(Node));
    if (pNew != NIL) {
        INFO(pNew) = x;
        // NEXT(pNew) = NIL;
    }

    return pNew;
}


/* Pemeriksaan Kondisi List */

boolean isEmpty(List l) {
/* Mengirimkan true jika l kosong dan false jika l tidak kosong */

    return NIL == l;
}

boolean isOneElmt(List l) {
/* Mengirimkan true jika l berisi 1 elemen dan false jika > 1 elemen atau kosong */

    if (isEmpty(l)) {
        return false;
    }

    return NIL == NEXT(l);
}


/* Primitif-Primitif Pemrosesan List */

ElType head(List l) {
/* Mengirimkan elemen pertama sebuah list l yang tidak kosong */

    return INFO(l);
}

List tail(List l) {
/* Mengirimkan list l tanpa elemen pertamanya, mungkin mengirimkan list kosong */

    return NEXT(l);
}

List konso(List l, ElType e) {
/* Mengirimkan list l dengan tambahan e sebagai elemen pertamanya. e dialokasi terlebih dahulu. 
   Jika alokasi gagal, mengirimkan l */

    Address pNew = newNode(e);
    if (NIL == pNew) {
        return l;
    }
    
    NEXT(pNew) = l;
    return pNew;
}

List konsb(List l, ElType e) {
/* Mengirimkan list l dengan tambahan e sebagai elemen terakhirnya */
/* e harus dialokasi terlebih dahulu */
/* Jika alokasi e gagal, mengirimkan l */ 

    if (isEmpty(l)) {
        return newNode(e);
    }

    NEXT(l) = konsb(tail(l), e);
    return l;
}

List copy(List l) {
/* Mengirimkan salinan list Ll (menjadi list baru) */
/* Jika ada alokasi gagal, mengirimkan l */ 

    if (isEmpty(l)) {
        return NIL;
    }

    return konso(copy(tail(l)), head(l));
}

List concat(List l1, List l2) {
/* Mengirimkan salinan hasil konkatenasi list l1 dan l2 (menjadi list baru) */
/* Jika ada alokasi gagal, menghasilkan NIL */

    if (isEmpty(l1)) {
        return copy(l2);
    }

    return konso(concat(tail(l1), l2), head(l1));
}


/* Fungsi dan Prosedur Lain */

int length(List l) {
/* Mengirimkan banyaknya elemen list l, mengembalikan 0 jika l kosong */

    if (isEmpty(l)) {
        return 0;
    }

    return 1 + length(tail(l));
}

boolean isMember(List l, ElType x) {
/* Mengirimkan true jika x adalah anggota list l dan false jika tidak */

    if (isEmpty(l)) {
        return false;
    } else if (head(l) == x) {
        return true;
    }

    return isMember(tail(l), x);
}

void displayList(List l) {
/* I.S. List l mungkin kosong */
/* F.S. Jika list tidak kosong, nilai list dicetak ke bawah */
/*      Dipisahkan dengan newline (\n) dan diakhiri dengan newline */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak:
  1
  20
  30
 */
/* Jika list kosong, tidak menuliskan apa-apa  */

    if (!isEmpty(l)) {
        printf("%d\n", head(l));
        displayList(tail(l));
    }
}

#include "listdin.h"
#include <stdlib.h>
#include <stdio.h>


/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create list kosong  */
void CreateListDin(ListDin *l, int capacity) {
    /* I.S. l sembarang, capacity > 0 */
    /* F.S. Terbentuk list dinamis l kosong dengan kapasitas capacity */
    BUFFER(*l) = (ElType *) malloc(capacity * sizeof(ElType));
    NEFF(*l) = 0;
    CAPACITY(*l) = capacity;
}

void dealocateList(ListDin *l) {
    /* I.S. l terdefinisi; */
    /* F.S. (l) dikembalikan ke system, CAPACITY(l)=0; NEFF(l)=0 */
    free(BUFFER(*l));
    NEFF(*l) = 0;
    CAPACITY(*l) = 0;
}

/* ********** SELEKTOR (TAMBAHAN) ********** */
/* *** Banyaknya elemen *** */
int listLength(ListDin l) {
    /* Mengirimkan banyaknya elemen efektif list */
    /* Mengirimkan nol jika list l kosong */
    return NEFF(l);
}
/* *** Daya tampung container *** */

/* *** Selektor INDEKS *** */
IdxType getFirstIdx(ListDin l) {
    /* Prekondisi : List l tidak kosong */
    /* Mengirimkan indeks elemen l pertama */
    return IDX_MIN;
}
IdxType getLastIdx(ListDin l) {
    /* Prekondisi : List l tidak kosong */
    /* Mengirimkan indeks elemen l terakhir */
    return listLength(l) - 1;
}

/* ********** Test Indeks yang valid ********** */
boolean isIdxValid(ListDin l, IdxType i) {
    /* Mengirimkan true jika i adalah indeks yang valid utk kapasitas list l */
    /* yaitu antara indeks yang terdefinisi utk container*/
    return IDX_MIN <= i && i <= CAPACITY(l) - 1;
}
boolean isIdxEff(ListDin l, IdxType i) {
    /* Mengirimkan true jika i adalah indeks yang terdefinisi utk list */
    /* yaitu antara 0..NEFF(l) */
    return IDX_MIN <= i && i <= NEFF(l) - 1;
}

/* ********** TEST KOSONG/PENUH ********** */
/* *** Test list kosong *** */
boolean isEmpty(ListDin l) {
    /* Mengirimkan true jika list l kosong, mengirimkan false jika tidak */
    return listLength(l) == 0;
}
/* *** Test list penuh *** */
boolean isFull(ListDin l) {
    /* Mengirimkan true jika list l penuh, mengirimkan false jika tidak */
    return listLength(l) == CAPACITY(l);
}

/* ********** BACA dan TULIS dengan INPUT/OUTPUT device ********** */
/* *** Mendefinisikan isi list dari pembacaan *** */
void readList(ListDin *l) {
    /* I.S. l sembarang dan sudah dialokasikan sebelumnya */
    /* F.S. List l terdefinisi */
    /* Proses : membaca banyaknya elemen l dan mengisi nilainya */
    /* 1. Baca banyaknya elemen diakhiri enter, misalnya N */
    /*    Pembacaan diulangi sampai didapat N yang benar yaitu 0 <= N <= CAPACITY(l) */
    /*    Jika N tidak valid, tidak diberikan pesan kesalahan */
    /* 2. Jika 0 < N <= CAPACITY(l); Lakukan N kali: Baca elemen mulai dari indeks
          0 satu per satu diakhiri enter */
    /*    Jika N = 0; hanya terbentuk l kosong */
    int n;
    do {
        scanf("%d", &n);
    } while (n < 0 || n > CAPACITY(*l));

    NEFF(*l) = n;
    IdxType i;
    for (i = IDX_MIN; i < n; i++) {
        scanf("%d", BUFFER(*l) + i);
    }
}
void printList(ListDin l) {
    /* Proses : Menuliskan isi list dengan traversal, list ditulis di antara kurung siku;
       antara dua elemen dipisahkan dengan separator "koma", tanpa tambahan karakter di depan,
       di tengah, atau di belakang, termasuk spasi dan enter */
    /* I.S. l boleh kosong */
    /* F.S. Jika l tidak kosong: [e1,e2,...,en] */
    /* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
    /* Jika list kosong : menulis [] */
    printf("[");
    IdxType i;
    if (listLength(l) != 0) {
        for (i = getFirstIdx(l); i < getLastIdx(l); i++) {
            printf("%d,", ELMT(l, i));
        }

        printf("%d", ELMT(l, i));
    }

    printf("]");
}

/* ********** OPERATOR ARITMATIKA ********** */
/* *** Aritmatika list : Penjumlahan, pengurangan, perkalian, ... *** */
ListDin plusMinusList(ListDin l1, ListDin l2, boolean plus) {
    /* Prekondisi : l1 dan l2 memiliki Neff sama dan tidak kosong */
    /* Jika plus = true, mengirimkan  l1+l2, yaitu setiap elemen l1 dan l2 pada indeks yang sama dijumlahkan */
    /* Jika plus = false, mengirimkan l1-l2, yaitu setiap elemen l1 dikurangi elemen l2 pada indeks yang sama */
    ListDin listResult;
    CreateListDin(&listResult, CAPACITY(l1));
    NEFF(listResult) = NEFF(l1);

    IdxType i;
    for (i = getFirstIdx(l1); i <= getLastIdx(l1); i++) {
        if (plus) {
            ELMT(listResult, i) = ELMT(l1, i) + ELMT(l2, i);
        }
        else {
            ELMT(listResult, i) = ELMT(l1, i) - ELMT(l2, i);
        }
    }

    return listResult;
}

/* ********** OPERATOR RELASIONAL ********** */
/* *** Operasi pembandingan list : < =, > *** */
boolean isListEqual(ListDin l1, ListDin l2) {
    /* Mengirimkan true jika l1 sama dengan l2 yaitu jika nEff l1 = l2 dan semua elemennya sama */
    if (listLength(l1) != listLength(l2)) {
        return false;
    }
    else if (listLength(l1) == 0) {
        return true;
    }
    IdxType i = getFirstIdx(l1);
    while (i < getLastIdx(l1) && ELMT(l1, i) == ELMT(l2, i)) {
        i++;
    }

    return ELMT(l1, i) == ELMT(l2, i);
}

/* ********** SEARCHING ********** */
/* ***  Perhatian : list boleh kosong!! *** */
IdxType indexOf(ListDin l, ElType val) {
    /* Search apakah ada elemen List l yang bernilai val */
    /* Jika ada, menghasilkan indeks i terkecil, dengan elemen ke-i = val */
    /* Jika tidak ada, mengirimkan IDX_UNDEF */
    /* Menghasilkan indeks tak terdefinisi (IDX_UNDEF) jika List l kosong */
    /* Skema Searching yang digunakan bebas */
    if (listLength(l) == 0) {
        return IDX_UNDEF;
    }
    IdxType i = getFirstIdx(l);
    while (i < getLastIdx(l) && ELMT(l, i) != val) {
        i++;
    }

    if (ELMT(l, i) == val) {
        return i;
    }
    return IDX_UNDEF;
}

/* ********** NILAI EKSTREM ********** */
void extremeValues(ListDin l, ElType *max, ElType *min) {
    /* I.S. List l tidak kosong */
    /* F.S. max berisi nilai maksimum l;
            min berisi nilai minimum l */
    *max = ELMT(l, getFirstIdx(l));
    *min = ELMT(l, getFirstIdx(l));
    IdxType i;
    for (i = getFirstIdx(l) + 1; i <= getLastIdx(l); i++) {
        if (ELMT(l, i) > *max) {
            *max = ELMT(l, i);
        }
        else if (ELMT(l, i) < *min) {
            *min = ELMT(l, i);
        }
    }
} // sampe sini tadi

/* ********** OPERASI LAIN ********** */
void copyList(ListDin lIn, ListDin *lOut) {
    /* I.S. lIn terdefinisi tidak kosong, lOut sembarang */
    /* F.S. lOut berisi salinan dari lIn (identik, nEff dan capacity sama) */
    /* Proses : Menyalin isi lIn ke lOut */ 
    CreateListDin(lOut, CAPACITY(lIn));
    NEFF(*lOut) = NEFF(lIn);

    IdxType i;
    for (i = getFirstIdx(lIn); i <= getLastIdx(lIn); i++) {
        ELMT(*lOut, i) = ELMT(lIn, i);
    }
}
ElType sumList(ListDin l) {
    /* Menghasilkan hasil penjumlahan semua elemen l */
    /* Jika l kosong menghasilkan 0 */
    ElType sum = 0;
    IdxType i;
    for (i = IDX_MIN; i < listLength(l); i++) {
        sum += ELMT(l, i);
    }

    return sum;
}
int countVal(ListDin l, ElType val) {
    /* Menghasilkan berapa banyak kemunculan val di l */
    /* Jika l kosong menghasilkan 0 */
    int count = 0;
    IdxType i;
    for (i = IDX_MIN; i < listLength(l); i++) {
        if (ELMT(l, i) == val) {
            count++;
        }
    }

    return count;
}

/* ********** SORTING ********** */
void sort(ListDin *l, boolean asc) {
    /* I.S. l boleh kosong */
    /* F.S. Jika asc = true, l terurut membesar */
    /*      Jika asc = false, l terurut mengecil */
    /* Proses : Mengurutkan l dengan salah satu algoritma sorting,
       algoritma bebas */
    if (listLength(*l) > 1) {
        IdxType i;
        for (i = getFirstIdx(*l); i < getLastIdx(*l); i++) {
            IdxType indexExtremeValue = i;
            IdxType j;
            for (j = i + 1; j <= getLastIdx(*l); j++) {
                if (asc && ELMT(*l, j) < ELMT(*l, indexExtremeValue)) {
                    indexExtremeValue = j;
                }
                else if (!asc && ELMT(*l, j) > ELMT(*l, indexExtremeValue)) {
                    indexExtremeValue = j;
                }
            }

            if (indexExtremeValue != i) {
                ElType temp = ELMT(*l, i);
                ELMT(*l, i) = ELMT(*l, indexExtremeValue);
                ELMT(*l, indexExtremeValue) = temp;
            }
        }
    }
}

/* ********** MENAMBAH DAN MENGHAPUS ELEMEN DI AKHIR ********** */
/* *** Menambahkan elemen terakhir *** */
void insertLast(ListDin *l, ElType val) {
    /* Proses: Menambahkan val sebagai elemen terakhir list */
    /* I.S. List l boleh kosong, tetapi tidak penuh */
    /* F.S. val adalah elemen terakhir l yang baru */
    ELMT(*l, getLastIdx(*l) + 1) = val;
    NEFF(*l)++;
}
/* ********** MENGHAPUS ELEMEN ********** */
void deleteLast(ListDin *l, ElType *val) {
    /* Proses : Menghapus elemen terakhir list */
    /* I.S. List tidak kosong */
    /* F.S. val adalah nilai elemen terakhir l sebelum penghapusan, */
    /*      Banyaknya elemen list berkurang satu */
    /*      List l mungkin menjadi kosong */
    *val = ELMT(*l, getLastIdx(*l));
    NEFF(*l)--;
} // sampe sini dulu

/* ********* MENGUBAH UKURAN ARRAY ********* */
void expandList(ListDin *l, int num) {
    /* Proses : Menambahkan capacity l sebanyak num */
    /* I.S. List sudah terdefinisi */
    /* F.S. Ukuran list bertambah sebanyak num */
    BUFFER(*l) = (ElType *) realloc(BUFFER(*l), (CAPACITY(*l) + num) * sizeof(ElType));
    CAPACITY(*l) += num;
}

void shrinkList(ListDin *l, int num) {
    /* Proses : Mengurangi capacity sebanyak num */
    /* I.S. List sudah terdefinisi, ukuran capacity > num, dan nEff < capacity - num. */
    /* F.S. Ukuran list berkurang sebanyak num. */
    BUFFER(*l) = (ElType *) realloc(BUFFER(*l), (CAPACITY(*l) - num) * sizeof(ElType));
    CAPACITY(*l) -= num;
}

void compressList(ListDin *l) {
    /* Proses : Mengubah capacity sehingga capacity = nEff */
    /* I.S. List tidak kosong */
    /* F.S. Ukuran capacity = nEff */
    BUFFER(*l) = (ElType *) realloc(BUFFER(*l), NEFF(*l) * sizeof(ElType));
    CAPACITY(*l) = NEFF(*l);
} // sampe sini akhirnya

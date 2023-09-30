#include "liststatik.h"
#include <stdio.h>


/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create List kosong  */
void CreateListStatik(ListStatik *l) {
    /* I.S. l sembarang */
    /* F.S. Terbentuk List l kosong dengan kapasitas CAPACITY */
    /* Proses: Inisialisasi semua elemen List l dengan MARK */
    IdxType i;
    for (i = IDX_MIN; i < CAPACITY; i++) {
        ELMT(*l, i) = MARK;
    }
}

/* ********** SELEKTOR (TAMBAHAN) ********** */
/* *** Banyaknya elemen *** */
int listLength(ListStatik l) {
    /* Mengirimkan banyaknya elemen efektif List */
    /* Mengirimkan nol jika List kosong */  
    int length = 0;
    IdxType i;
    for (i = IDX_MIN; i < CAPACITY; i++) {
        if (ELMT(l, i) != MARK) {
            length++;
        }
    }

    return length;
}

/* *** Selektor INDEKS *** */
IdxType getFirstIdx(ListStatik l) {
    /* Prekondisi : List l tidak kosong */
    /* Mengirimkan indeks elemen l pertama */
    IdxType i = IDX_MIN;
    while (ELMT(l, i) == MARK) {
        i++;
    }

    return i;
}
IdxType getLastIdx(ListStatik l) {
    /* Prekondisi : List l tidak kosong */
    /* Mengirimkan indeks elemen l terakhir */
    IdxType i = CAPACITY - 1;
    while (ELMT(l, i) == MARK) {
        i--;
    }

    return i;
}

/* ********** Test Indeks yang valid ********** */
boolean isIdxValid(ListStatik l, IdxType i) {
    /* Mengirimkan true jika i adalah indeks yang valid utk kapasitas List l */
    /* yaitu antara indeks yang terdefinisi utk container*/
    return IDX_MIN <= i && i <= CAPACITY - 1;
}
boolean isIdxEff(ListStatik l, IdxType i) {
    /* Mengirimkan true jika i adalah indeks yang terdefinisi utk List l */
    /* yaitu antara 0..length(l)-1 */
    return getFirstIdx(l) <= i && i <= getLastIdx(l);
}

/* ********** TEST KOSONG/PENUH ********** */
/* *** Test List kosong *** */
boolean isEmpty(ListStatik l) {
    /* Mengirimkan true jika List l kosong, mengirimkan false jika tidak */
    IdxType i = IDX_MIN;
    while (i < CAPACITY - 1 && ELMT(l, i) == MARK) {
        i++;
    }

    return ELMT(l, i) == MARK;
}
/* *** Test List penuh *** */
boolean isFull(ListStatik l) {
    /* Mengirimkan true jika List l penuh, mengirimkan false jika tidak */
    IdxType i = IDX_MIN;
    while (i < CAPACITY - 1 && ELMT(l, i) != MARK) {
        i++;
    }

    return ELMT(l, i) != MARK;
}

/* ********** BACA dan TULIS dengan INPUT/OUTPUT device ********** */
/* *** Mendefinisikan isi List dari pembacaan *** */
void readList(ListStatik *l) {
    /* I.S. l sembarang */
    /* F.S. List l terdefinisi */
    /* Proses: membaca banyaknya elemen l dan mengisi nilainya */
    /* 1. Baca banyaknya elemen diakhiri enter, misalnya n */
    /*    Pembacaan diulangi sampai didapat n yang benar yaitu 0 <= n <= CAPACITY */
    /*    Jika n tidak valid, tidak diberikan pesan kesalahan */
    /* 2. Jika 0 < n <= CAPACITY; Lakukan n kali: 
            Baca elemen mulai dari indeks 0 satu per satu diakhiri enter */
    /*    Jika n = 0; hanya terbentuk List kosong */
    IdxType n;
    do {
        scanf("%d", &n);
    } while (n < 0 || n > CAPACITY);

    CreateListStatik(l);
    IdxType i;
    for (i = IDX_MIN; i < n; i++) {
        ElType inputElement;
        scanf("%d", &inputElement);
        ELMT(*l, i) = inputElement;
    }
}
void printList(ListStatik l) {
    /* Proses : Menuliskan isi List dengan traversal, List ditulis di antara kurung 
       siku; antara dua elemen dipisahkan dengan separator "koma", tanpa tambahan 
       karakter di depan, di tengah, atau di belakang, termasuk spasi dan enter */
    /* I.S. l boleh kosong */
    /* F.S. Jika l tidak kosong: [e1,e2,...,en] */
    /* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
    /* Jika List kosong : menulis [] */
    printf("[");
    if (!isEmpty(l)) {
        IdxType i;
        IdxType lastIndex = getLastIdx(l);
        for (i = getFirstIdx(l); i < lastIndex; i++) {
            printf("%d", ELMT(l, i));
            printf(",");
        }

        printf("%d", ELMT(l, i));
    }

    printf("]");
}

/* ********** OPERATOR ARITMATIKA ********** */
/* *** Aritmatika List : Penjumlahan, pengurangan, perkalian, ... *** */
ListStatik plusMinusList(ListStatik l1, ListStatik l2, boolean plus) {
    /* Prekondisi : l1 dan l2 berukuran sama dan tidak kosong */
    /* Jika plus = true, mengirimkan  l1+l2, yaitu setiap elemen l1 dan l2 pada 
           indeks yang sama dijumlahkan */
    /* Jika plus = false, mengirimkan l1-l2, yaitu setiap elemen l1 dikurangi 
           elemen l2 pada indeks yang sama */
    ListStatik resultList;
    CreateListStatik(&resultList);
    IdxType firstIndexl1 = getFirstIdx(l1);
    IdxType lastIndexl1 = getLastIdx(l1);
    IdxType firstIndexl2 = getFirstIdx(l2);
    IdxType lastIndexl2 = getLastIdx(l2);
    IdxType i;
    if (plus) {
        for (i = 0; i < listLength(l1); i++) {
            ELMT(resultList, i) = ELMT(l1, firstIndexl1 + i) + ELMT(l2, firstIndexl2 + i);
        }

        return resultList;
    }
    for (i = 0; i < listLength(l1); i++) {
        ELMT(resultList, i) = ELMT(l1, firstIndexl1 + i) - ELMT(l2, firstIndexl2 + i);
    }

    return resultList;
}

/* ********** OPERATOR RELASIONAL ********** */
/* *** Operasi pembandingan List: *** */
boolean isListEqual(ListStatik l1, ListStatik l2) {
    /* Mengirimkan true jika l1 sama dengan l2 yaitu jika ukuran l1 = l2 dan semua 
       elemennya sama */
    if (listLength(l1) != listLength(l2)) {
        return false;
    }
    
    IdxType firstIndexl1 = getFirstIdx(l1);
    IdxType firstIndexl2 = getFirstIdx(l2);
    IdxType i = 0;
    while (i < listLength(l1) - 1 && ELMT(l1, firstIndexl1 + i) == ELMT(l2, firstIndexl2 + i)) {
        i++;
    }

    return ELMT(l1, firstIndexl1 + i) == ELMT(l2, firstIndexl2 + i);
}

/* ********** SEARCHING ********** */
/* ***  Perhatian : List boleh kosong!! *** */
int indexOf(ListStatik l, ElType val) {
    /* Search apakah ada elemen List l yang bernilai val */
    /* Jika ada, menghasilkan indeks i terkecil, dengan ELMT(l,i) = val */
    /* Jika tidak ada atau jika l kosong, mengirimkan IDX_UNDEF */
    /* Skema Searching yang digunakan bebas */
    if (isEmpty(l)) {
        return IDX_UNDEF;
    }
    IdxType i = getFirstIdx(l);
    IdxType lastIndex = getLastIdx(l);
    while (i < lastIndex && ELMT(l, i) != val) {
        i++;
    }

    if (ELMT(l, i) == val) {
        return i;
    }
    return IDX_UNDEF;
}

/* ********** NILAI EKSTREM ********** */
void extremeValues(ListStatik l, ElType *max, ElType *min) {
    /* I.S. List l tidak kosong */
    /* F.S. Max berisi nilai terbesar dalam l;
            Min berisi nilai terkecil dalam l */
    IdxType firstIndex = getFirstIdx(l);
    IdxType lastIndex = getLastIdx(l);
    *max = ELMT(l, firstIndex);
    *min = *max;
    IdxType i;
    for (i = firstIndex; i <= lastIndex; i++) {
        if (ELMT(l, i) > *max) {
            *max = ELMT(l, i);
        }
        else if (ELMT(l, i) < *min) {
            *min = ELMT(l, i);
        }
    }
}

/* ********** MENAMBAH ELEMEN ********** */
/* *** Menambahkan elemen terakhir *** */
void insertFirst(ListStatik *l, ElType val) {
    /* Proses: Menambahkan val sebagai elemen pertama List */
    /* I.S. List l boleh kosong, tetapi tidak penuh */
    /* F.S. val adalah elemen pertama l yang baru */
    if (isEmpty(*l)) {
        ELMT(*l, IDX_MIN) = val;
    }
    else {
        IdxType firstIndex = getFirstIdx(*l);
        IdxType lastIndex = getLastIdx(*l);
        if (lastIndex == CAPACITY - 1) {
            ELMT(*l, firstIndex - 1) = val;
        }
        else {
            IdxType i;
            for (i = lastIndex; i >= firstIndex; i--) {
                ELMT(*l, i + 1) = ELMT(*l, i);
            }

            ELMT(*l, firstIndex) = val;
        }
    }
}
/* *** Menambahkan elemen pada index tertentu *** */
void insertAt(ListStatik *l, ElType val, IdxType idx) {
    /* Proses: Menambahkan val sebagai elemen pada index idx List */
    /* I.S. List l tidak kosong dan tidak penuh, idx merupakan index yang valid di l */
    /* F.S. val adalah elemen yang disisipkan pada index idx l */
    IdxType firstIndex = getFirstIdx(*l);
    IdxType lastIndex = getLastIdx(*l);
    IdxType i;
    if (lastIndex != CAPACITY - 1) {
        for (i = lastIndex; i >= firstIndex + idx; i--) {
            ELMT(*l, i + 1) = ELMT(*l, i);
        }

        ELMT(*l, firstIndex + idx) = val;
    }
    else {
        for (i = firstIndex; i <= firstIndex + idx - 1; i++) {
            ELMT(*l, i - 1) = ELMT(*l, i);
        }

        ELMT(*l, firstIndex + idx - 1) = val;
    }
}
/* *** Menambahkan elemen terakhir *** */
void insertLast(ListStatik *l, ElType val) {
    /* Proses: Menambahkan val sebagai elemen terakhir List */
    /* I.S. List l boleh kosong, tetapi tidak penuh */
    /* F.S. val adalah elemen terakhir l yang baru */
    if (isEmpty(*l)) {
        ELMT(*l, IDX_MIN) = val;
    }
    else {
        IdxType lastIndex = getLastIdx(*l);
        if (lastIndex != CAPACITY - 1) {
            ELMT(*l, lastIndex + 1) = val;
        }
        else {
            IdxType i;
            for (i = getFirstIdx(*l); i <= lastIndex; i++) {
                ELMT(*l, i - 1) = ELMT(*l, i);
            }

            ELMT(*l, lastIndex) = val;
        }
    }
}

/* ********** MENGHAPUS ELEMEN ********** */
/* *** Menghapus elemen pertama *** */
void deleteFirst(ListStatik *l, ElType *val) {
    /* Proses : Menghapus elemen pertama List */
    /* I.S. List tidak kosong */
    /* F.S. val adalah nilai elemen pertama l sebelum penghapusan, */
    /*      Banyaknya elemen List berkurang satu */
    /*      List l mungkin menjadi kosong */
    IdxType firstIndex = getFirstIdx(*l);
    *val = ELMT(*l, firstIndex);
    IdxType lastIndex = getLastIdx(*l);
    IdxType i;
    for (i = firstIndex + 1; i <= lastIndex; i++) {
        ELMT(*l, i - 1) = ELMT(*l, i);
    }

    ELMT(*l, lastIndex) = MARK;
}
/* *** Menghapus elemen pada index tertentu *** */
void deleteAt(ListStatik *l, ElType *val, IdxType idx) {
    /* Proses : Menghapus elemen pada index idx List */
    /* I.S. List tidak kosong, idx adalah index yang valid di l */
    /* F.S. val adalah nilai elemen pada index idx l sebelum penghapusan, */
    /*      Banyaknya elemen List berkurang satu */
    /*      List l mungkin menjadi kosong */
    IdxType firstIndex = getFirstIdx(*l);
    *val = ELMT(*l, firstIndex + idx);
    IdxType lastIndex = getLastIdx(*l);
    IdxType i;
    for (i = firstIndex + idx + 1; i <= lastIndex; i++) {
        ELMT(*l, i - 1) = ELMT(*l, i);
    }

    ELMT(*l, lastIndex) = MARK;
}
/* *** Menghapus elemen terakhir *** */
void deleteLast(ListStatik *l, ElType *val) {
    /* Proses : Menghapus elemen terakhir List */
    /* I.S. List tidak kosong */
    /* F.S. val adalah nilai elemen terakhir l sebelum penghapusan, */
    /*      Banyaknya elemen List berkurang satu */
    /*      List l mungkin menjadi kosong */
    IdxType lastIndex = getLastIdx(*l);
    *val = ELMT(*l, lastIndex);
    ELMT(*l, lastIndex) = MARK;
}
/* ********** SORTING ********** */
void sortList(ListStatik *l, boolean asc) {
    /* I.S. l boleh kosong */
    /* F.S. Jika asc = true, l terurut membesar */
    /*      Jika asc = false, l terurut mengecil */
    /* Proses : Mengurutkan l dengan salah satu algoritma sorting,
    algoritma bebas */
    if (listLength(*l) > 1) {
        IdxType lastIndex = getLastIdx(*l);
        IdxType i;
        for (i = getFirstIdx(*l); i <= lastIndex - 1; i++) {
            IdxType idxExtreme = i;
            IdxType j;
            for (j = i + 1; j <= lastIndex; j++) {
                if (asc && ELMT(*l, j) < ELMT(*l, idxExtreme)) {
                    idxExtreme = j;
                }
                else if (!asc && ELMT(*l, j) > ELMT(*l, idxExtreme)) {
                    idxExtreme = j;
                }
            }

            if (idxExtreme != i) {
                ElType temp = ELMT(*l, idxExtreme);
                ELMT(*l, idxExtreme) = ELMT(*l, i);
                ELMT(*l, i) = temp;
            }
        }
    }
}

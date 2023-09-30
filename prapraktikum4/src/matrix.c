#include "matrix.h"
#include <stdio.h>
#include <math.h>


/* ********** DEFINISI PROTOTIPE PRIMITIF ********** */

/* *** Konstruktor membentuk Matrix *** */
void createMatrix(int nRows, int nCols, Matrix *m) {
    /* Membentuk sebuah Matrix "kosong" yang siap diisi berukuran nRow x nCol di "ujung kiri" memori */
    /* I.S. nRow dan nCol adalah valid untuk memori matriks yang dibuat */
    /* F.S. Matriks m sesuai dengan definisi di atas terbentuk */
    ROW_EFF(*m) = nRows;
    COL_EFF(*m) = nCols;
}

/* *** Selektor "Dunia Matrix" *** */
boolean isMatrixIdxValid(int i, int j) {
    /* Mengirimkan true jika i, j adalah index yang valid untuk matriks apa pun */
    return 0 <= i && i <= ROW_CAP - 1 && 0 <= j && j <= COL_CAP - 1;
}

/* *** Selektor: Untuk sebuah matriks m yang terdefinisi: *** */
IdxType getLastIdxRow(Matrix m) {
    /* Mengirimkan Index baris terbesar m */
    return ROW_EFF(m) - 1;
}

IdxType getLastIdxCol(Matrix m) {
    /* Mengirimkan Index kolom terbesar m */
    return COL_EFF(m) - 1;
}

boolean isIdxEff(Matrix m, IdxType i, IdxType j) {
    /* Mengirimkan true jika i, j adalah Index efektif bagi m */
    return 0 <= i && i <= getLastIdxRow(m) && 0 <= j && j <= getLastIdxCol(m);
}

ElType getElmtDiagonal(Matrix m, IdxType i) {
    /* Mengirimkan elemen m(i,i) */
    return ELMT(m, i, i);
}


/* ********** Assignment  Matrix ********** */

void copyMatrix(Matrix mIn, Matrix *mOut) {
    /* Melakukan assignment mOut <- mIn */
    createMatrix(ROW_EFF(mIn), COL_EFF(mIn), mOut);
    IdxType i;
    for (i = 0; i <= getLastIdxRow(mIn); i++) {
        IdxType j;
        for (j = 0; j <= getLastIdxCol(mIn); j++) {
            ELMT(*mOut, i, j) = ELMT(mIn, i, j);
        }
    }

    ROW_EFF(*mOut) = ROW_EFF(mIn);
    COL_EFF(*mOut) = COL_EFF(mIn);
}


/* ********** KELOMPOK BACA/TULIS ********** */

void readMatrix(Matrix *m, int nRow, int nCol) {
    /* I.S. isIdxValid(nRow,nCol) */
    /* F.S. m terdefinisi nilai elemen efektifnya, berukuran nRow x nCol */
    /* Proses: Melakukan CreateMatrix(m,nRow,nCol) dan mengisi nilai efektifnya */
    /* Selanjutnya membaca nilai elemen per baris dan kolom */
    /* Contoh: Jika nRow = 3 dan nCol = 3, maka contoh cara membaca isi matriks :
    1 2 3
    4 5 6
    8 9 10 
    */
    createMatrix(nRow, nCol, m);
    IdxType i;
    for (i = 0; i <= getLastIdxRow(*m); i++) {
        IdxType j;
        for (j = 0; j <= getLastIdxCol(*m); j++) {
            scanf("%d", &ELMT(*m, i, j));
        }
    }
}

void displayMatrix(Matrix m) {
    /* I.S. m terdefinisi */
    /* F.S. Nilai m(i,j) ditulis ke layar per baris per kolom, masing-masing elemen per baris 
    dipisahkan sebuah spasi. Baris terakhir tidak diakhiri dengan newline */
    // Revisi sendiri: harusnya semua baris diakhiri dengan newline
    /* Proses: Menulis nilai setiap elemen m ke layar dengan traversal per baris dan per kolom */
    /* Contoh: menulis matriks 3x3 (ingat di akhir tiap baris, tidak ada spasi)
    1 2 3
    4 5 6
    8 9 10
    */
    IdxType i;
    for (i = 0; i <= getLastIdxRow(m); i++) {
        IdxType j;
        for (j = 0; j <= getLastIdxCol(m); j++) {
            printf("%d", ELMT(m, i, j));
            if (j < getLastIdxCol(m)) {
                printf(" ");
            }
        }

        printf("\n");
    }
}


/* ********** KELOMPOK OPERASI ARITMATIKA TERHADAP TYPE ********** */

Matrix addMatrix(Matrix m1, Matrix m2) {
    /* Prekondisi : m1 berukuran sama dengan m2 */
    /* Mengirim hasil penjumlahan matriks: m1 + m2 */
    Matrix resultMatrix;
    createMatrix(ROW_EFF(m1), COL_EFF(m1), &resultMatrix);
    IdxType i;
    for (i = 0; i <= getLastIdxRow(m1); i++) {
        IdxType j;
        for (j = 0; j <= getLastIdxCol(m1); j++) {
            ELMT(resultMatrix, i, j) = ELMT(m1, i, j) + ELMT(m2, i, j); 
        }
    }

    return resultMatrix;
}

Matrix subtractMatrix(Matrix m1, Matrix m2) {
    /* Prekondisi : m1 berukuran sama dengan m2 */
    /* Mengirim hasil pengurangan matriks: salinan m1 – m2 */
    Matrix resultMatrix;
    createMatrix(ROW_EFF(m1), COL_EFF(m1), &resultMatrix);
    IdxType i;
    for (i = 0; i <= getLastIdxRow(m1); i++) {
        IdxType j;
        for (j = 0; j <= getLastIdxCol(m1); j++) {
            ELMT(resultMatrix, i, j) = ELMT(m1, i, j) - ELMT(m2, i, j); 
        }
    }

    return resultMatrix;
}

Matrix multiplyMatrix(Matrix m1, Matrix m2) {
    /* Prekondisi : Ukuran kolom efektif m1 = ukuran baris efektif m2 */
    /* Mengirim hasil perkalian matriks: salinan m1 * m2 */
    Matrix resultMatrix;
    createMatrix(ROW_EFF(m1), COL_EFF(m2), &resultMatrix);
    IdxType i;
    for (i = 0; i <= getLastIdxRow(m1); i++) {
        IdxType j;
        for (j = 0; j <= getLastIdxCol(m2); j++) {
            ElType sum = 0;
            IdxType k;
            for (k = 0; k < COL_EFF(m1); k++) {
                sum += ELMT(m1, i, k) * ELMT(m2, k, j);
            }

            ELMT(resultMatrix, i, j) = sum;
        }
    }

    return resultMatrix;
}

Matrix multiplyMatrixWithMod(Matrix m1,Matrix m2,int mod) {
    /* Prekondisi : Ukuran kolom efektif m1 = ukuran baris efektif m2 */
    /* Mengirim hasil perkalian matriks: salinan (m1 * m2)%mod, artinya setiap elemen matrix hasil perkalian m1 * m2 dilakukan modulo terhadap mod */
    Matrix resultMatrix = multiplyMatrix(m1, m2);
    IdxType i;
    for (i = 0; i <= getLastIdxRow(resultMatrix); i++) {
        IdxType j;
        for (j = 0; j <= getLastIdxCol(resultMatrix); j++) {
            while (ELMT(resultMatrix, i, j) < 0) {
                ELMT(resultMatrix, i, j) += mod;
            }

            ELMT(resultMatrix, i, j) %= mod;
        }
    }

    return resultMatrix;
}

Matrix multiplyByConst(Matrix m, ElType x) {
    /* Mengirim hasil perkalian setiap elemen m dengan x */
    Matrix resultMatrix;
    createMatrix(ROW_EFF(m), COL_EFF(m), &resultMatrix);
    IdxType i;
    for (i = 0; i <= getLastIdxRow(m); i++) {
        IdxType j;
        for (j = 0; j <= getLastIdxCol(m); j++) {
            ELMT(resultMatrix, i, j) = ELMT(m, i, j) * x; 
        }
    }

    return resultMatrix;
}

void pMultiplyByConst(Matrix *m, ElType k) {
    /* I.S. m terdefinisi, k terdefinisi */
    /* F.S. Mengalikan setiap elemen m dengan k */
    IdxType i;
    for (i = 0; i <= getLastIdxRow(*m); i++) {
        IdxType j;
        for (j = 0; j <= getLastIdxCol(*m); j++) {
            ELMT(*m, i, j) *= k; 
        }
    }
}


/* ********** KELOMPOK OPERASI RELASIONAL TERHADAP Matrix ********** */

boolean isMatrixEqual(Matrix m1, Matrix m2) {
    /* Mengirimkan true jika m1 = m2, yaitu count(m1) = count(m2) dan */
    /* untuk setiap i,j yang merupakan Index baris dan kolom m1(i,j) = m2(i,j) */
    /* Juga merupakan strong eq karena getLastIdxCol(m1) = getLastIdxCol(m2) */
    if (ROW_EFF(m1) != ROW_EFF(m2) || COL_EFF(m1) != COL_EFF(m2)) {
        return false;
    }
    boolean equal = true;
    IdxType i = 0;
    while (equal && i <= getLastIdxRow(m1)) {
        IdxType j = 0;
        while (equal && j <= getLastIdxCol(m1)) {
            if (ELMT(m1, i, j) != ELMT(m2, i, j)) {
                equal = false;
            }
            else {
                j++;
            }
        }

        if (equal) {
            i++;
        }
    }

    return equal;
}

boolean isMatrixNotEqual(Matrix m1, Matrix m2) {
    /* Mengirimkan true jika m1 tidak sama dengan m2 */
    return !isMatrixEqual(m1, m2);
}

boolean isMatrixSizeEqual(Matrix m1, Matrix m2) {
    /* Mengirimkan true jika ukuran efektif matriks m1 sama dengan ukuran efektif m2 */
    /* yaitu RowEff(m1) = RowEff (m2) dan ColEff (m1) = ColEff (m2) */
    return ROW_EFF(m1) == ROW_EFF(m2) && COL_EFF(m1) == COL_EFF(m2);
}


/* ********** Operasi lain ********** */

int countElmt(Matrix m) {
    /* Mengirimkan banyaknya elemen m */
    return ROW_EFF(m) * COL_EFF(m);
}


/* ********** KELOMPOK TEST TERHADAP Matrix ********** */

boolean isSquare(Matrix m) {
    /* Mengirimkan true jika m adalah matriks dg ukuran baris dan kolom sama */
    return ROW_EFF(m) == COL_EFF(m);
}

boolean isSymmetric(Matrix m) {
    /* Mengirimkan true jika m adalah matriks simetri : isSquare(m) 
    dan untuk setiap elemen m, m(i,j)=m(j,i) */
    if (!isSquare(m)) {
        return false;
    }
    boolean symmetric = true;
    IdxType i = 0;
    while (symmetric && i <= getLastIdxRow(m)) {
        IdxType j = i + 1;
        while (symmetric && j <= getLastIdxCol(m)) {
            if (ELMT(m, i, j) != ELMT(m, j, i)) {
                symmetric = false;
            }
            else {
                j++;
            }
        }

        if (symmetric) {
            i++;
        }
    }

    return symmetric;
}

boolean isIdentity(Matrix m) {
    /* Mengirimkan true jika m adalah matriks satuan: isSquare(m) dan 
    setiap elemen diagonal m bernilai 1 dan elemen yang bukan diagonal bernilai 0 */
    if (!isSquare(m)) {
        return false;
    }
    boolean identity = true;
    IdxType i = 0;
    while (identity && i <= getLastIdxRow(m)) {
        IdxType j = 0;
        while (identity && j <=  getLastIdxCol(m)) {
            if (i == j && ELMT(m, i, j) != 1) {
                identity = false;
            }
            else if (i != j && ELMT(m, i, j) != 0) {
                identity = false;
            }
            else {
                j++;
            }
        }

        if (identity) {
            i++;
        }
    }
    
    return identity;
}

boolean isSparse(Matrix m) {
    /* Mengirimkan true jika m adalah matriks sparse: matriks “jarang” dengan definisi: 
       hanya maksimal 5% dari memori matriks yang efektif bukan bernilai 0 */
    int countNot0 = 0;
    IdxType i;
    for (i = 0; i <= getLastIdxRow(m); i++) {
        IdxType j;
        for (j = 0; j <= getLastIdxCol(m); j++) {
            if (ELMT(m, i, j) != 0) {
                countNot0++;
            }
        }
    }

    return countNot0 <= countElmt(m) / 20;
}

Matrix negation(Matrix m) {
    /* Menghasilkan salinan m dengan setiap elemen dinegasikan (dikalikan -1) */
    return multiplyByConst(m, -1);
}

void pNegation(Matrix *m) {
    /* I.S. m terdefinisi */
    /* F.S. m di-invers, yaitu setiap elemennya dinegasikan (dikalikan -1) */
    pMultiplyByConst(m, -1);
}


// Helper function untuk determinant
float minor(Matrix matrix, IdxType indexRow, IdxType indexColumn) {
    // Precondition: matrix adalah matriks persegi dan matrix berukuran minimum 2x2
    Matrix result;
    createMatrix(ROW_EFF(matrix) - 1, COL_EFF(matrix) - 1, &result);
    
    // Mengambil elemen-elemen baris sebelum baris yang dihapus
    IdxType i;
    for (i = 0; i < indexRow; i++) {
        // Mengambil elemen-elemen kolom sebelum kolom yang dihapus
        IdxType j;
        for (j = 0; j < indexColumn; j++) {
            ELMT(result, i, j) = ELMT(matrix, i, j);
        }

        // Mengambil elemen-elemen kolom setelah kolom yang dihapus
        for (j = indexColumn + 1; j <= getLastIdxCol(matrix); j++) {
            ELMT(result, i, j - 1) = ELMT(matrix, i, j);
        }
    }

    // Mengambil elemen-elemen baris setelah baris yang dihapus
    for (i = indexRow + 1; i <= getLastIdxRow(matrix); i++) {
        // Mengambil elemen-elemen kolom sebelum kolom yang dihapus
        IdxType j;
        for (j = 0; j < indexColumn; j++) {
            ELMT(result, i - 1, j) = ELMT(matrix, i, j);
        }

        // Mengambil elemen-elemen kolom setelah kolom yang dihapus
        for (j = indexColumn + 1; j <= getLastIdxCol(matrix); j++) {
            ELMT(result, i - 1, j - 1) = ELMT(matrix, i, j);
        }
    }

    return determinant(result);
}


float determinant(Matrix m) {
    /* Prekondisi: isSquare(m) */
    /* Menghitung nilai determinan m */
    if (ROW_EFF(m) == 1) {
        return ELMT(m, 0, 0);
    }
    const IdxType indexRow = 0;
    float sum = 0;
    IdxType i;
    for (i = 0; i <= getLastIdxCol(m); i++) {
        sum += ELMT(m, indexRow, i) * powf(-1, indexRow + i) * minor(m, indexRow, i);
    }

    return sum;
}

Matrix transpose(Matrix m) {
    /* I.S. m terdefinisi dan IsSquare(m) */
    /* F.S. menghasilkan salinan transpose dari m, yaitu setiap elemen m(i,j) ditukar nilainya dengan elemen m(j,i) */
    Matrix resultMatrix;
    createMatrix(COL_EFF(m), ROW_EFF(m), &resultMatrix);
    IdxType i;
    for (i = 0; i <= getLastIdxRow(m); i++) {
        IdxType j;
        for (j = 0; j <= getLastIdxCol(m); j++) {
            ELMT(resultMatrix, j, i) = ELMT(m, i, j);
        }
    }

    return resultMatrix;
}

void pTranspose(Matrix *m) {
    /* I.S. m terdefinisi dan IsSquare(m) */
    /* F.S. m "di-transpose", yaitu setiap elemen m(i,j) ditukar nilainya dengan elemen m(j,i) */
    copyMatrix(transpose(*m), m);
}

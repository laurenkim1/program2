#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int** makematrix(int n){
    int i, j;
    int **matrix = malloc(sizeof(int *) * n);
    for (i = 0; i < n; i++){
        matrix[i] = (int *) malloc(sizeof(int) * n);
    }
    for (i=0; i<n; i++){
        for (j=0; j<n; j++){
            matrix[i][j]=0;
        }
    }
    return matrix;
}

void matrixmult(int n, int** A, int** B, int** C){
    int rowtrav;
    int coltrav;
    int trav;
    int val = 0;
    for (rowtrav = 0; rowtrav < n; rowtrav++){
        for (coltrav = 0; coltrav < n; coltrav ++){
            for (trav = 0; trav < n; trav ++){
                val = val + A[rowtrav][trav] * B[trav][coltrav];
            }
            C[rowtrav][coltrav] = val;
            val = 0;
        }
    }
}

int** matrixadd(int n, int** A, int** B){
    int **C = makematrix(n);
    int sum = 0;

    int rowtrav;
    int coltrav;
    for (rowtrav = 0; rowtrav < n; rowtrav++){
        for (coltrav = 0; coltrav < n; coltrav++){
            C[rowtrav][coltrav] = A[rowtrav][coltrav] + B[rowtrav][coltrav];
        }
    }
    return C;
}

int** matrixsubtract(int n, int** A, int** B){
    int** C = makematrix(n);

    int rowtrav;
    int coltrav;
    for (rowtrav = 0; rowtrav < n; rowtrav++){
        for (coltrav = 0; coltrav < n; coltrav++){
            C[rowtrav][coltrav] = A[rowtrav][coltrav] - B[rowtrav][coltrav];
        }
    }
    return C;
}

void split1(int n, int** m, int** m1){
    int d = n/2;
    int rows, cols;
    for (rows = 0; rows < d; rows++){
        for (cols = 0; cols < d; cols++){
            m1[rows][cols] = m[rows][cols];
        }
    }
}

void split2(int n, int** m, int** m2){
    int d = n/2;
    int rows, cols;
    for (rows = 0; rows < d; rows++){
        for (cols = 0; cols < d; cols++){
            m2[rows][cols] = m[rows][cols+d];
        }
    }
}

void split3(int n, int** m, int** m3){
    int d = n/2;
    int rows, cols;
    for (rows = 0; rows < d; rows++){
        for (cols = 0; cols < d; cols++){
            m3[rows][cols] = m[rows+d][cols];
        }
    }
}

void split4(int n, int** m, int** m4){
    int d = n/2;
    int rows, cols;
    for (rows = 0; rows < d; rows++){
        for (cols = 0; cols < d; cols++){
            m4[rows][cols] = m[rows+d][cols+d];
        }
    }
}

void join(int n, int** m, int** m1, int** m2, int** m3, int** m4){
    int d = n/2;
    int rows, cols;
    for (rows = 0; rows < d; rows++){
        for (cols = 0; cols < d; cols++){
            m[rows][cols] = m1[rows][cols];
            m[rows][cols+d] = m2[rows][cols];
            m[rows+d][cols] = m3[rows][cols];
            m[rows+d][cols+d] = m4[rows][cols];
        }
    }
}

int** strassen(int n, int** A, int** B){
    int** C = makematrix(n);

    // cutoff
    if (n == 2){
        matrixmult(n, A, B, C);
        return C;
    }

    int d = n/2;

    int** A1 = makematrix(d);
    int** A2 = makematrix(d);
    int** A3 = makematrix(d);
    int** A4 = makematrix(d);

    int** B1 = makematrix(d);
    int** B2 = makematrix(d);
    int** B3 = makematrix(d);
    int** B4 = makematrix(d);

    split1(n, A, A1);
    split2(n, A, A2);
    split3(n, A, A3);
    split4(n, A, A4);

    split1(n, B, B1);
    split2(n, B, B2);
    split3(n, B, B3);
    split4(n, B, B4);

    int** p1 = makematrix(d);
    int** p2 = makematrix(d);
    int** p3 = makematrix(d);
    int** p4 = makematrix(d);
    int** p5 = makematrix(d);
    int** p6 = makematrix(d);
    int** p7 = makematrix(d);

    p1 = strassen(d, A1, matrixsubtract(d, B2, B4));
    p2 = strassen(d, matrixadd(d, A1, A2), B4);
    p3 = strassen(d, matrixadd(d, A3, A4), B1);
    p4 = strassen(d, A4, matrixsubtract(d, B3, B1));
    p5 = strassen(d, matrixadd(d, A1, A4), matrixadd(d, B1, B4));
    p6 = strassen(d, matrixsubtract(d, A2, A4), matrixadd(d, B3, B4));
    p7 = strassen(d, matrixsubtract(d, A1, A3), matrixadd(d, B1, B2));

    int** C1 = makematrix(d);
    int** C2 = makematrix(d);
    int** C3 = makematrix(d);
    int** C4 = makematrix(d);

    C1 = matrixadd(d, p5, matrixsubtract(d, p4, matrixadd(d, p2, p6)));
    C2 = matrixadd(d, p1, p2);
    C3 = matrixadd(d, p3, p4);
    C4 = matrixadd(d, p5, matrixsubtract(d, p1, matrixsubtract(d, p3, p7)));

    join(n, C, C1, C2, C3, C4);

    free(A);
    free(B);

    free(p1);
    free(p2);
    free(p3);
    free(p4);
    free(p5);
    free(p6);
    free(p7);

    free(A1);
    free(A2);
    free(A3);
    free(A4);

    free(B1);
    free(B2);
    free(B3);
    free(B4);

    free(C1);
    free(C2);
    free(C3);
    free(C4);

    return C;
}


int main(int argc, char *argv[]){
    int *input = argv[1];

    FILE *matrices = fopen(input, "r");
    if (matrices == NULL){
      fprintf(stderr, "Could not open file");
      exit(1);
    }

    int rowcount, colcount;
    rowcount = colcount = 0;

    while ((ch = getc(matrices)) != EOF)
    {
      if (ch == "\n"){
        rowcount++;
        colcount++
      }
    }

    fseek(matrices, 0, SEEK_SET);

    // Matrices are arrays of rows
    int **matrixA = malloc(sizeof(int *) * rowcount);
    int **matrixB = malloc(sizeof(int *) * rowcount);

    if (rowcount % 2 = 0){
      n = rowcount;
      for (int i = 0; i < rowcount; i++){
        int *newrowA = malloc(sizeof(int)*colcount);
        int *newrowB = malloc(sizeof(int)*colcount);

        // should be character size of thing
        fread(newrowA, sizeof(int), colcount, matrices);
        matrixA[i] = newrowA;

        fread(newrowB, sizeof(int), colcount, matrices);
        matrixB[i] = newrowB;

        free(newrowA);
        free(newrowB);
      }
    }

    else {
      n = rowcount+1;
      for (int i = 0; i < rowcount; i++){
        int *newrowA = malloc(sizeof(int)*colcount+1);
        int *newrowB = malloc(sizeof(int)*colcount+1);

        // should be character size of thing
        fread(newrowA, sizeof(int), colcount, matrices);
        newrowA[colcount] = 0;
        matrixA[i] = newrowA;

        fread(newrowB, sizeof(int), colcount, matrices);
        newrowB[colcount] = 0;
        matrixB[i] = newrowB;

        free(newrowA);
        free(newrowB);
      }

      // padding
      int *newrowA = malloc(sizeof(int)*colcount);
      int *newrowB = malloc(sizeof(int)*colcount);

      for (int j = 0; j < colcount; j++){
        newrowA[j] = 0;
        newrowB[j] = 0;
      }

      matrixA[rowcount] = newrowA;
      matrixB[rowcount] = newrowB;

      free(newrowA);
      free(newrowB);
    }

    int** C = makematrix(n);
    C = strassen(n, matrixA, matrixB);

    for(int t = 0; t < n; t++){
        for(int s = 0; s < n; s++){
            printf("%i \n", C[t][s]);
        }
    }
  }


    /*

  int main(void){
      int n = 4;

      int** A = makematrix(n);
      int** B = makematrix(n);

      A[0][0] = 1;
      A[0][1] = 2;
      A[0][2] = 3;
      A[0][3] = 4;
      A[1][0] = 5;
      A[1][1] = 6;
      A[1][2] = 7;
      A[1][3] = 8;
      A[2][0] = 1;
      A[2][1] = 2;
      A[2][2] = 3;
      A[2][3] = 4;
      A[3][0] = 5;
      A[3][1] = 6;
      A[3][2] = 7;
      A[3][3] = 8;

      B[0][0] = 1;
      B[0][1] = 2;
      B[0][2] = 3;
      B[0][3] = 4;
      B[1][0] = 5;
      B[1][1] = 6;
      B[1][2] = 7;
      B[1][3] = 8;
      B[2][0] = 1;
      B[2][1] = 2;
      B[2][2] = 3;
      B[2][3] = 4;
      B[3][0] = 5;
      B[3][1] = 6;
      B[3][2] = 7;
      B[3][3] = 8;

      int** C = makematrix(n);
      C = strassen(n, A, B);

      for(int t = 0; t < n; t++){
          for(int s = 0; s < n; s++){
              printf("%i \n", C[t][s]);
          }
      }
  }

  */

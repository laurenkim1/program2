#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
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

/*
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

void matrixmult(int n, int** A, int** B, int** C){
    int rowtravA;
    int rowtravB;
    int coltravB;
    for (rowtravA = 0; rowtravA < n; rowtravA++){
        C[rowtravA][coltravB] = 0;
        for (rowtravB = 0; rowtravB < n; rowtravB++){
            for (coltravB = 0; coltravB < n; coltravB ++){
                C[rowtravA][coltravB] = C[rowtravA][coltravB] + A[rowtravA][rowtravB] * B[rowtravB][coltravB];
            }
        }
    }
}

*/

void matrixmult(int n, int** A, int** B, int** C){
    int rowtravB;
    int coltravB;
    int rowtravA;
    int trav;
    int temp;

    int Bcol[n];

    for (coltravB = 0; coltravB < n; coltravB++){
        for (rowtravB = 0; rowtravB < n; rowtravB++){
            Bcol[rowtravB] = B[rowtravB][coltravB];
        }
        for (trav = 0; trav < n; trav++){
            temp = 0;
            for (rowtravA = 0; rowtravA < n; rowtravA++){
                temp += A[trav][rowtravA]*Bcol[rowtravA];
            }
            C[trav][coltravB] = temp;
        }
    }
}


void matrixadd(int n, int** A, int** B, int** sum){

    int rowtrav;
    int coltrav;
    for (rowtrav = 0; rowtrav < n; rowtrav++){
        for (coltrav = 0; coltrav < n; coltrav++){
            sum[rowtrav][coltrav] = A[rowtrav][coltrav] + B[rowtrav][coltrav];
        }
    }
}

void matrixsubtract(int n, int** A, int** B, int** diff){

    int rowtrav;
    int coltrav;
    for (rowtrav = 0; rowtrav < n; rowtrav++){
        for (coltrav = 0; coltrav < n; coltrav++){
            diff[rowtrav][coltrav] = A[rowtrav][coltrav] - B[rowtrav][coltrav];
        }
    }
}

void split1(int d, int** m, int** m1){
    int rows, cols;
    for (rows = 0; rows < d; rows++){
        for (cols = 0; cols < d; cols++){
            m1[rows][cols] = m[rows][cols];
        }
    }
}

void split2(int d, int pad, int** m, int** m2){
    int rows, cols;
    if (pad == 0){
        for (rows = 0; rows < d; rows++){
            for (cols = 0; cols < d; cols++){
                m2[rows][cols] = m[rows][cols+d];
            }
        }
    }
    else {
        for (rows = 0; rows < d; rows++){
            for (cols = 0; cols < d-1; cols++){
                m2[rows][cols] = m[rows][cols+d];
            }
            m2[rows][d-1] = 0;
        }
    }
}

void split3(int d, int pad, int** m, int** m3){
    int rows, cols;
    if (pad == 0){
        for (rows = 0; rows < d; rows++){
            for (cols = 0; cols < d; cols++){
                m3[rows][cols] = m[rows+d][cols];
            }
        }
    }
    else {
        for (rows = 0; rows < d-1; rows++){
            for (cols = 0; cols < d; cols++){
                m3[rows][cols] = m[rows+d][cols];
                m3[d-1][cols] = 0;
            }
        }
    }
}

void split4(int d, int pad, int** m, int** m4){
    int rows, cols;
    if (pad == 0){
        for (rows = 0; rows < d; rows++){
            for (cols = 0; cols < d; cols++){
                m4[rows][cols] = m[rows+d][cols+d];
            }
        }
    }
    else {
        for (rows = 0; rows < d-1; rows++){
            for (cols = 0; cols < d-1; cols++){
                m4[rows][cols] = m[rows+d][cols+d];
            }
            m4[rows][d-1] = 0;
        }
        for (cols = 0; cols < d; cols++){
            m4[d-1][cols] = 0;
        }
    }
}

void join(int d, int pad, int quad, int** m, int** mquad){
    int n;
    int rows, cols, help;
    int mhelp[d];

    if (pad == 0){
        n = 2*d;
        for (rows = 0; rows < d; rows++){
            for (help = 0; help < d; help++){
                mhelp[help] = mquad[rows][help];
            }
            for (cols = 0; cols < d; cols++){
                if (quad == 1){
                    m[rows][cols] = mhelp[cols];
                }
                else if (quad == 2){
                    m[rows][cols+d] = mhelp[cols];
                }
                else if (quad == 3){
                    m[rows+d][cols] = mhelp[cols];
                }
                else {
                    m[rows+d][cols+d] = mhelp[cols];
                }
            }
        }
    }
    else {
        n = 2*d - 1;
        if (quad == 1){
            for (rows = 0; rows < d; rows++){
                for (cols = 0; cols < d; cols++){
                    m[rows][cols] = mquad[rows][cols];
                }
            }
        }
        else if (quad == 2){
            for (rows = 0; rows < d; rows++){
                for (cols = d; cols < n; cols++){
                    m[rows][cols] = mquad[rows][cols - d];
                }
            }
        }
        else if (quad == 3){
            for (rows = d; rows < n; rows++){
                for (cols = 0; cols < d; cols ++){
                    m[rows][cols] = mquad[rows - d][cols];
                }
            }
        }
        else {
            for (rows = d; rows < n; rows++){
                for (cols = d; cols < n; cols++){
                    m[rows][cols] = mquad[rows - d][cols - d];
                }
            }
        }
    }
}

int** strassen(int n, int** A, int** B, int** Cquad){
    int** C = makematrix(n);
    int pad;
    int d;

    // cutoff
    if (n <= 400){
        matrixmult(n, A, B, C);
        return C;
    }

    if (n % 2 == 1) {
        d = (n+1)/2;
        pad = 1;
    }

    if (n % 2 == 0){
        d = n/2;
        pad = 0;
    }

    int** A1 = makematrix(d);
    int** A2 = makematrix(d);
    int** A3 = makematrix(d);
    int** A4 = makematrix(d);

    int** B1 = makematrix(d);
    int** B2 = makematrix(d);
    int** B3 = makematrix(d);
    int** B4 = makematrix(d);

    split1(d, A, A1);
    split2(d, pad, A, A2);
    split3(d, pad, A, A3);
    split4(d, pad, A, A4);

    split1(d, B, B1);
    split2(d, pad, B, B2);
    split3(d, pad, B, B3);
    split4(d, pad, B, B4);

    int** p1 = makematrix(d);
    int** p2 = makematrix(d);
    int** p3 = makematrix(d);
    int** p4 = makematrix(d);
    int** p5 = makematrix(d);
    int** p6 = makematrix(d);
    int** p7 = makematrix(d);
    int** phelp = makematrix(d);
    
    matrixsubtract(d, B2, B4, p1);
    p1 = strassen(d, A1, p1, Cquad);
    
    matrixadd(d, A1, A2, p2);
    p2 = strassen(d, p2, B4, Cquad);
    
    matrixadd(d, A3, A4, p3);
    p3 = strassen(d, p3, B1, Cquad);
    
    matrixsubtract(d, B3, B1, p4);
    p4 = strassen(d, A4, p4, Cquad);
    
    matrixadd(d, A1, A4, p5);
    matrixadd(d, B1, B4, phelp);
    p5 = strassen(d, p5, phelp, Cquad);
    
    matrixsubtract(d, A2, A4, p6);
    matrixadd(d, B3, B4, phelp);
    p6 = strassen(d, p6, phelp, Cquad);
    
    matrixsubtract(d, A1, A3, p7);
    matrixadd(d, B1, B2, phelp);
    p7 = strassen(d, p7, phelp, Cquad);

    matrixsubtract(d, p4, p2, Cquad);
    matrixadd(d, p6, Cquad, p6);
    matrixadd(d, p5, p6, Cquad);
    join(d, pad, 1, C, Cquad);
    
    matrixadd(d, p1, p2, Cquad);
    join(d, pad, 2, C, Cquad);
    
    matrixadd(d, p3, p4, Cquad);
    join(d, pad, 3, C, Cquad);
    
    matrixadd(d, p5, p1, p5);
    matrixadd(d, p3, p7, p7);
    matrixsubtract(d, p5, p7, Cquad);
    join(d, pad, 4, C, Cquad);

    free(p1);
    free(p2);
    free(p3);
    free(p4);
    free(p5);
    free(p6);
    free(p7);
    free(phelp);

    free(A1);
    free(A2);
    free(A3);
    free(A4);

    free(B1);
    free(B2);
    free(B3);
    free(B4);

    return C;
}

int main(int argc, char *argv[]){
    int n = atoi(argv[2]);

    FILE *nums = fopen(argv[3], "r");
    if (nums == NULL){
        fprintf(stderr, "Could not open file");
        exit(1);
    }

    char line[100];
    int length = 0;
    while (fgets(line, sizeof(line), nums) != NULL){
        length++;
    }
    fseek(nums, 0, SEEK_SET);

    int matgen[length];
    int trav = 0;
    while (fgets(line, sizeof(line), nums) != NULL){
        int new = atoi(line);
        matgen[trav] = new;
        trav++;
    }

    // Matrices are arrays of rows
    int** matrixA = makematrix(n);
    int** matrixB = makematrix(n);

    int** C = makematrix(n);
    int** Cquad = makematrix(n);

    if (atoi(argv[1]) == 1){
        // seed for random index generator for generating random matrix from list
        time_t seconds;
        time(&seconds);
        srand((unsigned int) seconds);

        int randindex = 0;
        for (int rows = 0; rows < n; rows ++){
            for (int cols = 0; cols < n; cols++){
                randindex = rand() % length;
                matrixA[rows][cols] = matgen[randindex];
                randindex = rand() % length;
                matrixB[rows][cols] = matgen[randindex];
            }
        }

        clock_t start, finish;
        double strasstime;
        double conventime;
        int compare;

        printf("dim \t strassen \t conventional \t strasfaster\n");
        for (int dim = n-20; dim <= n; dim++){
            start = clock();
            C = strassen(dim, matrixA, matrixB, Cquad);
            finish = clock();
            strasstime = (double)(finish - start) / CLOCKS_PER_SEC;

            start = clock();
            matrixmult(dim, matrixA, matrixB, C);
            finish = clock();
            conventime = (double)(finish - start) / CLOCKS_PER_SEC;
            
            if (strasstime > conventime){
                compare = 1;
            }
            else{
                compare = 0;
            }

            printf("%i \t %f \t %f \t %i \n", dim, strasstime, conventime, compare);
      }
    }
    // print diagonal entries with newlines
    else {
        for (int rows = 0; rows < n; rows ++){
            for (int cols = 0; cols < n; cols++){
                matrixA[rows][cols] = matgen[rows * n + cols];
                matrixB[rows][cols] = matgen[n * n + rows * n + cols];
            }
        }
        C = strassen(n, matrixA, matrixB, C);
        for (int i = 0; i < n; i ++) {
            int val = C[i][i];
            printf("%i\n", val);
        }
    }

    free(matrixA);
    free(matrixB);
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
      matrixmult(n, A, B, C);

      for(int t = 0; t < n; t++){
          for(int s = 0; s < n; s++){
              printf("%i \n", C[t][s]);
          }
      }
  }
  */

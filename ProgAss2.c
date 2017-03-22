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
    int **sum = makematrix(n);
    
    int rowtrav;
    int coltrav;
    for (rowtrav = 0; rowtrav < n; rowtrav++){
        for (coltrav = 0; coltrav < n; coltrav++){
            sum[rowtrav][coltrav] = A[rowtrav][coltrav] + B[rowtrav][coltrav];
        }
    }
    return sum;
}

int** matrixsubtract(int n, int** A, int** B){
    int** diff = makematrix(n);
    
    int rowtrav;
    int coltrav;
    for (rowtrav = 0; rowtrav < n; rowtrav++){
        for (coltrav = 0; coltrav < n; coltrav++){
            diff[rowtrav][coltrav] = A[rowtrav][coltrav] - B[rowtrav][coltrav];
        }
    }
    return diff;
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

void join(int d, int pad, int** m, int** m1, int** m2, int** m3, int** m4){
    int n;
    int rows, cols;
    
    if (pad == 0){
        n = 2*d;
        for (rows = 0; rows < d; rows++){
            for (cols = 0; cols < d; cols++){
                m[rows][cols] = m1[rows][cols];
                m[rows][cols+d] = m2[rows][cols];
                m[rows+d][cols] = m3[rows][cols];
                m[rows+d][cols+d] = m4[rows][cols];
            }
        }
    }
    else {
        n = 2*d - 1;
        for (rows = 0; rows < d; rows++){
            for (cols = 0; cols < d; cols++){
                m[rows][cols] = m1[rows][cols];
            }
            for (cols = d; cols < n; cols++){
                m[rows][cols] = m2[rows][cols - d];
            }
        }
        for (rows = d; rows < n; rows++){
            for (cols = 0; cols < d; cols ++){
                m[rows][cols] = m3[rows - d][cols];
            }
            for (cols = d; cols < n; cols++){
                m[rows][cols] = m4[rows - d][cols - d];
            }
        }
    }
}

int** strassen(int n, int** A, int** B){
    int** C = makematrix(n);
    int pad;
    int d;
    
    // cutoff
    if (n == 1){
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
    
    C1 = matrixadd(d, p5, matrixadd(d, p6, matrixsubtract(d, p4, p2)));
    C2 = matrixadd(d, p1, p2);
    C3 = matrixadd(d, p3, p4);
    C4 = matrixsubtract(d, matrixadd(d, p5, p1), matrixadd(d, p3, p7));
    
    join(d, pad, C, C1, C2, C3, C4);
    
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
    int n = atoi(argv[2]);
    
    int *input = argv[3];
    
    FILE *nums = fopen(input, "r");
    if (nums == NULL){
        fprintf(stderr, "Could not open file");
        exit(1);
    }
    
    int length = 0;
    for (int c = fgetc(nums); c != EOF; c = fgetc(fp)){
        if (isdigit(c)){
            length ++;
        }
        else {
            length = length;
        }
    }
    
    fseek(nums, 0, SEEK_SET);
    
    int matgen[length];
    int trav = 0;
    for (int num = fgetc(nums); num != EOF; num = fgetc(fp)){
        if (isdigit(num)){
            matgen[trav] = atoi(num);
            trav++;
        }
        else {
            trav = trav;
        }
    }
    
    // Matrices are arrays of rows
    int** matrixA = makematrix(n);
    int** matrixB = makematrix(n);
    
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
    
    int** C = makematrix(n);
    
    clock_t start, finish;
    double strasstime;
    double conventime;
    
    start = clock();
    C = strassen(n, matrixA, matrixB);
    finish = clock();
    
    strasstime = (double)(finish - start) / CLOCKS_PER_SEC;
    
    start = clock()
    matrixmult(n, matrixA, matrixB, C);
    finish = clock()
    
    conventime = (double)(finish - start) / CLOCKS_PER_SEC;
    
    printf("dim \t strassen \t conventional \n");
    for (int dim = 1, dim <= n, dim *= 2){
        start = clock();
        C = strassen(dim, matrixA, matrixB);
        finish = clock();
        strasstime = (double)(finish - start) / CLOCKS_PER_SEC;
        
        start = clock()
        matrixmult(dim, matrixA, matrixB, C);
        finish = clock()
        conventime = (double)(finish - start) / CLOCKS_PER_SEC;
        
        printf("%i \t %i \t %i \n", dim, strasstime, conventime);
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

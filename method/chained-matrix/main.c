#include <stdio.h>
#include <stdlib.h>
#define min(x,y) (((x) < (y)) ? (x) : (y))
#define INF 99999
#define MAX 6

void printOrder(int i,int j);
void printMatrix(void);
void chainMatrixMul(void);
// D[곱하려는 행렬 개수 + 1] = {A0.row, A0.column == A1.row, A1.column == A2.row ... }
// A0 = 10 * 4, A1 = 4 * 5
//int D[MAX + 1] = {10, 4, 5, 20, 2, 50};
int D[MAX + 1] = {5, 2, 3, 4, 6, 7, 8};

// M[곱하려는 행렬 개수][곱하려는 행렬 개수]
// M[i][j] = 주어진 행렬 중 i ~ j 까지의 곱셈시 필요한 최소 곱셈 연산 횟수
int M[MAX + 1][MAX + 1] = {0};
// P[i][j] = i ~ j까지의 곱셈시 최소곱이 되기위해 거쳐야 하는 중간 행렬 지점
int P[MAX + 1][MAX + 1] = {0};

int main(void) {
    printf("\t초기화 후: ");
    printMatrix();
    chainMatrixMul();
    printf("\t계산 후: ");
    printMatrix();
    printOrder(1,MAX);
    return 0;
}

void chainMatrixMul(void) {
    int i, j, diagonal, k, mul_count;
    for(diagonal = 1; diagonal <= MAX - 1; diagonal++)
        for(i = 1; i <= MAX - diagonal; i++) {
            j = i + diagonal;
            M[i][j] = INF;
            for(k = i; k <= j - 1; k++) {
                mul_count = M[i][k] + M[k+1][j] + D[i-1] * D[k] * D[j];
                if(mul_count < M[i][j]) {
                    P[i][j] = k;
                    M[i][j] = mul_count;
                }
            }
        }
}

void printMatrix(void) {
    printf("\n\tMatrix D:\n");
    for(int j = 0; j <= MAX; j++) {
               printf("\t%5d", D[j]);
           }
           printf("\n");
    printf("\n\tMatrix M:\n");
    for(int i = 0; i <= MAX; i++) {
        for(int j = 0; j <= MAX; j++) {
            printf("\t%5d", M[i][j]);
        }
        printf("\n");
    }
    printf("\n\tMatrix P:\n");
    for(int i = 0; i <= MAX; i++) {
        for(int j = 0; j <= MAX; j++) {
            printf("\t%5d", P[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void printOrder(int i,int j) {
    if(i == j)
        printf("%c", 'A' - 1 + i);
    else {
        int k = P[i][j];
        printf("(");
        printOrder(i,k);
        printOrder(k + 1,j);
        printf(")");
        
    }
}




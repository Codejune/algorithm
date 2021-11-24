#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

#define MAX 6
#define STRING_MAX 50
#define INF 999

// KEY = 주어진 Key값
char KEY[MAX + 1][STRING_MAX] = {"\0", "CASE", "ELSE", "END", "IF", "OF", "THEN"};
// P = 각 Key마다의 확률 값
float P[MAX + 1] = {INF, 0.05, 0.15, 0.05, 0.35, 0.05, 0.35};
// R = 주어진
int R[MAX + 1][MAX + 1] = {0};
float A[MAX + 1][MAX + 1] = {0};

typedef struct node {
    char key[STRING_MAX];
    struct node* left;
    struct node* right;
}node;

void printMatrix(void);
void initMatrix(void);
void search(node* root, char* keyin);
void optimalBST(void);
float sum(int start, int end);

node* tree(int i, int j)   // 이진트리 생성 함수
{
   int k;
   k = R[i][j];
   node* p = malloc(sizeof(node));
   
   if (k == 0)
      return NULL;
   else {
      strcpy(p->key, KEY[k]);
      p->left = tree(i, k - 1);
      p->right = tree(k + 1, j);
      return p;
   }
}

int main(void) {
    optimalBST();
    tree(1, MAX);
    return 0;
}

/*
    key를 찾을경우의 횟수 : 해당 key가 위치한 depth + 1 (root.depth = 0)
    평균 시행 횟수 중 가장 최소값이 나타나는 트리 구조를 구하기.
 */
void search(node* root, char* keyin) {
    int found;
    node* cursor;
    
    cursor = root;  // cursor = 현재 위치 노드
    found = FALSE;  // found = 원하는 key값을 찾았는지 여부
    while(found != TRUE) {
        // 원하는 key값을 못찾았을 경우
        if(cursor->key[0] == '\0')
            return;
        // 원하는 key값을 찾았을 경우
        else if(strcmp(cursor->key, keyin) == 0)
            found = TRUE;
        // 주어진 key값이 더 작을 경우
        else if (strcmp(cursor->key, keyin) == 1)
            cursor = cursor->left;
        // 주어진 key값이 더 클 경우
        else cursor = cursor->right;
    }
}

void optimalBST(void) {
    int i, j, k, diagonal;
    float comp_p;
    
    for(int i = 1; i <= MAX; i++) {
        A[i][i] = P[i];
        A[i][i-1] = 0;
        R[i][i] = i;
        R[i][i-1] = 0;
    }
    printMatrix();
    A[MAX][MAX-1] = 0;
    R[MAX][MAX-1] = 0;
    // diagonal = 행렬 대각선
    for(diagonal = 1; diagonal <= MAX; diagonal++) {
        printf("\tdiagonal = %d\n", diagonal);
        // i = 시작 위치
        for(i = 1; i <= MAX - diagonal; i++) {
            // j = 끝 위치
            j = i + diagonal;
            A[i][j] = INF;
            // k = 중간 위치
            for(k = i; k <= j; k++) {
                comp_p = A[i][k - 1] + A[k + 1][j] + sum(i, j);
                printf("\t\ti = %d, j = %d, k = %d, %s ~ %s = %.2f\n", i, j, k,  KEY[i], KEY[j], comp_p);
                if(comp_p < A[i][j]) {
                    printf("\t\tA[%d][%d] = %.2f, R[%d][%d] = %d\n", i, j, comp_p, i, j, k);
                    A[i][j] = comp_p;    // 최소 곱셈 연산 횟수 할당
                    R[i][j] = k;            // i ~ j까지의 최소곱을 하기 위한 중간 행렬 지점 지정
                }
            }
        }
    }
     
    printMatrix();
}

float sum(int start, int end) {
    float sum = 0;
    for(int i = start; i <= end; i++) {
        sum += P[i];
    }
    return sum;
}

void initMatrix(void) {
    for(int i = 0; i < MAX; i++) {
        A[i][i] = P[i];
        R[i][i] = i;
    }
}

void printMatrix(void) {
    printf("\n\tMatrix KEY:\n");
    for(int i = 1; i <= MAX + 1; i++) {
        printf("\t%s", KEY[i]);
    }
    printf("\n\tMatrix P:\n");
    for(int i = 1; i <= MAX + 1; i++) {
        printf("\t%.2f", P[i]);
    }
    printf("\n\tMatrix R:\n");
    for(int i = 1; i <= MAX + 1; i++) {
        for(int j = 0; j < MAX + 1; j++) {
            printf("\t%d", R[i][j]);
        }
        printf("\n");
    }
    printf("\n\tMatrix A:\n");
    for(int i = 1; i <= MAX + 1; i++) {
        for(int j = 0; j < MAX + 1; j++) {
            printf("\t%.2f", A[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

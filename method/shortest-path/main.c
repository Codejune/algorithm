/**
Floyd algorithm test code

Test case 1:
5
0 1 inf 1 5
9 0 3 2 inf
inf inf 0 4 inf
inf inf 2 0 3
3 inf inf inf 0

Test case 2:
5
0 4 inf inf inf
5 0 7 inf inf
inf inf 0 10 5
1 inf inf 0 2
9 2 inf 3 0

Test case 3
5
0 10 5 inf inf
inf 0 2 1 inf
inf 3 0 9 2
inf inf 0 inf 4
7 inf inf 5 0
**/
#include <stdio.h>
#define NUM 5
#define INF 9999
#define minimum(x, y) (((x) < (y)) ? (x) : (y))

void floyd(void);
void floyd2(void);
void path(int q, int r);
void printMatrix(void);
/*
int W[NUM][NUM] = {     // 가중치
    {0, 10, 5, INF, INF},
    {INF, 0, 2, 1, INF},
    {INF, 3, 0, 9, 2},
    {INF, INF, 0, INF, 4},
    {7, INF, INF, 5, 0}
};
int D[NUM][NUM] = {     // 최단 경로
    {0, 10, 5, INF, INF},
    {INF, 0, 2, 1, INF},
    {INF, 3, 0, 9, 2},
    {INF, INF, INF, 0, 4},
    {7, INF, INF, 5, 0}
};
*/

// int W[NUM][NUM] = { // 가중치
//     {0, 4, INF, INF, INF},
//     {5, 0, 7, INF, INF},
//     {INF, INF, 0, 10, 5},
//     {1, INF, INF, 0, 2},
//     {9, 2, INF, 3, 0}};
// int D[NUM][NUM] = { // 최단 경로
//     {0, 4, INF, INF, INF},
//     {5, 0, 7, INF, INF},
//     {INF, INF, 0, 10, 5},
//     {1, INF, INF, 0, 2},
//     {9, 2, INF, 3, 0}};

int W[NUM][NUM] = {
    {0, 1, INF, 1, 5},
    {9, 0, 3, 2, INF},
    {INF, INF, 0, 4, INF},
    {INF, INF, 2, 0, 3},
    {3, INF, INF, INF, 0}
};
int D[NUM][NUM] = {
    {0, 1, INF, 1, 5},
    {9, 0, 3, 2, INF},
    {INF, INF, 0, 4, INF},
    {INF, INF, 2, 0, 3},
    {3, INF, INF, INF, 0}
};


int P[NUM][NUM] = {0}; // P[i][j] = i부터 j까지의 최고차수 정점 (ex. [0][4] = 4)

int main(void)
{
    floyd2();
    return 0;
}

void path(int q, int r)
{
    printf("path(%d, %d) = %d\n", q, r, P[q][r]);
    if (P[q][r] != 0)
    {
        path(q, P[q][r]); // 시작점 ~ 최단거리중 최고차수
        printf("[v%d]\n", P[q][r]);
        path(P[q][r], r);
    }
    printf("path(%d, %d) return\n", q, r);
}

void printMatrix(void)
{
    for (int i = 0; i < NUM; i++)
    {
        for (int j = 0; j < NUM; j++)
        {
            printf("[%d] ", W[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    for (int i = 0; i < NUM; i++)
    {
        for (int j = 0; j < NUM; j++)
        {
            printf("[%d] ", D[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    for (int i = 0; i < NUM; i++)
    {
        for (int j = 0; j < NUM; j++)
        {
            printf("[%d] ", P[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void floyd(void)
{
    for (int k = 0; k < NUM; k++)
        for (int i = 0; i < NUM; i++)
            for (int j = 0; j < NUM; j++)
                D[i][j] = minimum(D[i][j], D[i][k] + D[k][j]);

    printMatrix();
    path(0, 4);
}

void floyd2(void)
{
    // W -> 가중치 행렬
    // D -> vi->vj까지 가는 최소 가중치 합
    // P -> vi->vj까지 가는데 중간에 거치는 정점중에 최고 차수 
    // v1 -> v2, v1, v4...-> v5  == v4
    // vi -> vk -> vj 까지의 가중치 계산 
    // i k j
    // 0 0 0
    // 0 0 1
    // 0 0 2
    // 0 0 3 
    // ...
    // 1 0 0
    // 1 0 1
    // 1 0 2
    // ..

    for (int k = 0; k < NUM; k++)
        for (int i = 0; i < NUM; i++)
            for (int j = 0; j < NUM; j++)
            // i = 0 j 4, v0->v4 = inf
            // i -> k -> j < i -> j
                if (D[i][k] + D[k][j] < D[i][j])
                {
                    P[i][j] = k; // 
                    D[i][j] = D[i][k] + D[k][j]; // i -> j까지 가는 최소 가중치 업데이트
                }
    printMatrix();
    path(1, 0);
}


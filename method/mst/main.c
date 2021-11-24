#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10          //노드의 개수
#define INF 987654321   //간선의 가중치가 없는 경우 무한대 표시
#define TRUE 1
#define FALSE -1

typedef struct Edge {
    int weight;
    int i, j;
} Edge;

void Prim(int start);
void Kruskal(void);
void print1DMatrix(int matrix[MAX]);
void print2DMatrix(int matrix[MAX][MAX]);
void Divide(Edge *edge, int left, int right, int n);
void Combine(Edge *edge, int left, int middle, int right, int n);
Edge* copyArray(Edge *array, int n);

// W = 이음선의 가중치(존재O=가중치, 존재X=INF, i==j = 0)
const int W[MAX][MAX] = {
    {0, 32, INF, 17, INF, INF, INF, INF, INF, INF},
    {32, 0, INF, INF, 45, INF, INF, INF, INF, INF},
    {INF, INF, 0, 18, INF, INF, 5, INF, INF, INF},
    {17, INF, 18, 0, 10, INF, INF, 3, INF, INF},
    {INF, 45, INF, 10, 0, 28, INF, INF, 25, INF},
    {INF, INF, INF, INF, 28, 0, INF, INF, INF, 6},
    {INF, INF, 5, INF, INF, INF, 0, 59, INF, INF},
    {INF, INF, INF, 3, INF, INF, 59, 0, 4, INF},
    {INF, INF, INF, INF, 25, INF, INF, 4, 0, 12},
    {INF, INF, INF, INF, INF, 6, INF, INF, 12, 0}
};

int main(void) {
    printf("\tPrim(0) :\n");
    Prim(0);
    printf("\tPrim(9) :\n");
    Prim(9);
    printf("\tKruskal :\n");
    Kruskal();
    return 0;
}

/*
 F = 그래프에 대한 최소비용 신장트리 안에 있는 이음선(Edge)의 집합
 Y = 최소비용 신장트리의 마디(Vertex) 집합
 nearest[i] = vi에 가장 가까운 Y에 속한 마디의 인덱스
 distance[i] = vi와 nearest[i]가 인덱스인 두 마디를 연결하는 이음선의 가중치
 */
void Prim(int start) {
    int nearest[MAX] = {0};
    int distance[MAX] = {0};
    int i, j;
    int min, vnear = 0; // distance[i]값이 최소가 되는 마디 인덱스
    
    for(i = 0; i < MAX; i++) {
        if(i == start) continue;    // 모든 마디에 대하여 Y에 속한 가장 가까운 마디
        nearest[i] = start;         // (nearest[i])는 v1으로 초기화하고,
        distance[i] = W[start][i];  // Y로부터 거리(distance[i])는 vi와 v1을
    }                               // 연결하는 이음선의 가중치로 초기화한다.
    
    distance[start] = FALSE;
    for(j = 1; j < MAX; j++) {  // MAX - 1번 반복
        // MAX - 1개의 마디를 Y에 추가한다.
        min = INF;
        for(i = 0; i < MAX; i++) {
            if(i == start) continue;
            if(0 <= distance[i] && distance[i] < min) { // 각 마디에 대하여 distance[i]를 검사하여
                min = distance[i];                      // Y에 가장 가까이 있는 마디(vnear)을 찾는다.
                vnear = i;
            }
        }
        
        distance[vnear] = FALSE;
        for(i = 0; i < MAX; i++) {
            if(i == start) continue;            // Y에 속하지 않은
            if(W[i][vnear] < distance[i]) {     // 각 마디에 대하여
                distance[i] = W[i][vnear];      // Y로부터의 거리(distance[i])를
                nearest[i] = vnear;             // 갱신한다.
            }
        }
    }
    
    printf("\tdistance: \n");
    print1DMatrix(distance);
    printf("\tnearest: \n");
    print1DMatrix(nearest);
    int tot = 0;
    for(i = 0; i < MAX; i++) {
        if(i == start) continue;
        printf("\t(%d, %d) %d\n", i, nearest[i], W[i][nearest[i]]);
        tot += W[i][nearest[i]];
    }
    printf("\tSum = %d", tot);
    printf("\n\n");
}

void Kruskal() {
    int i, j;
    int tmp, tmp2;
    int edge_count = 0;
    int sum = 0;
    int cycle = 0;
    int w[MAX][MAX];
    int V[MAX];
    Edge *edge = calloc(MAX*MAX, sizeof(Edge));
    memcpy(w, W, sizeof(W));
    
    for(i = 0; i < MAX; i++) {
        for(j = i; j < MAX; j++) {
            if(W[i][j] != INF && W[i][j] != 0) {
                edge[edge_count].i = i;
                edge[edge_count].j = j;
                edge[edge_count].weight = W[i][j];
                edge_count++;
            }
        }
    }
    
    // 가중치 오름차순 합병 정렬
    Divide(edge, 0, edge_count - 1, edge_count);
    
    memset(V, TRUE, sizeof(V));
    
    for(tmp = 0; tmp < edge_count; tmp++) {
        cycle = 0;
        
        for(i = 0; i < MAX; i++) {
            if(w[edge[tmp].i][i] == -1 && w[i][edge[tmp].j] == -1) {
                w[edge[tmp].i][edge[tmp].j] = -1;
                w[edge[tmp].j][edge[tmp].i] = -1;
            }
        }
        
        if(V[edge[tmp].i] == -1 && V[edge[tmp].j] == -1)
            for(i = 0; i < MAX; i++) {
                if(w[edge[tmp].i][i] == -1 && w[i][edge[tmp].j] == -1) {
                    cycle = 1;
                    break;
                }
            }
        
        if(cycle == 0) {
            printf("\t(%d, %d) %d\n", edge[tmp].i, edge[tmp].j, edge[tmp].weight);
            V[edge[tmp].i] = -1;
            V[edge[tmp].j] = -1;
            w[edge[tmp].i][edge[tmp].j] = -1;
            w[edge[tmp].j][edge[tmp].i] = -1;
            sum += edge[tmp].weight;
        }
        
        for(i = 0; i < MAX; i++) {
            for(j = 0; j < MAX; j++) {
                for(tmp2 = 0; tmp2 < MAX; tmp2++) {
                    if(w[i][tmp2] == -1 && w[tmp2][j] == -1) {
                        w[i][j] = -1;
                        w[j][i] = -1;
                    }
                }
            }
        }
    }
    printf("\tSum = %d\n", sum);
}


void Divide(Edge *edge, int left, int right, int n) {
    int middle = (left + right) / 2;
    if (left < right) {
        Divide(edge, left, middle, n);
        Divide(edge, middle + 1, right, n);
        Combine(edge, left, middle, right, n);
    }
}

void Combine(Edge *edge, int left, int middle, int right, int n) {
    Edge* temp = copyArray(edge, n);
    int i = left;
    int j = middle + 1;
    int l;
    int position = left;
    
    /* 분할 정렬된 list의 합병 */
    while (i <= middle && j <= right) {
        if (edge[i].weight <= edge[j].weight)
            temp[position++] = edge[i++];
        else temp[position++] = edge[j++];
    }
    //남아 있는 값들을 일괄 복사
    if (i > middle)
        for (l = j; l <= right; l++)
            temp[position++] = edge[l];
    else
        for (int l = i; l <= middle; l++)
            temp[position++] = edge[l];
    for (int i = 0; i < n; i++)
        edge[i] = temp[i];
}

Edge* copyArray(Edge *edge, int n) {
    Edge* temp = calloc(n, sizeof(Edge));
    for (int i = 0; i < n; i++) {
        temp[i] = edge[i];
    }
    return temp;
}

void print1DMatrix(int matrix[MAX]) {
    int i;
    for(i = 0; i < MAX; i++) {
        printf("\t[%2d]", matrix[i]);
    }
    printf("\n\n");
}

void print2DMatrix(int matrix[MAX][MAX]) {
    int i, j;
    for(i = 0; i < MAX; i++) {
        for(j = 0; j < MAX; j++) {
            printf("\t[%2d]", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Header
#include <stdio.h>
#include <stdbool.h>

// Macro
#define DEBUG
#define MAX_SIZE 100
#define INF 987654321

// Structure type
typedef struct nodetype
{
    int parent;
    int depth;
} nodetype;

typedef struct edgetype
{
    int weight;
    int i, j;
} edgetype;

// Global variable
const int N = 5; // Vertext count
const int W[MAX_SIZE][MAX_SIZE] = {
    {0, 9, 5, 6, INF},
    {INF, 0, 7, 4, 2},
    {INF, INF, 0, INF, 4},
    {INF, INF, INF, 0, 1},
    {INF, INF, INF, INF, 0}}; // Edge
// const int W[MAX_SIZE][MAX_SIZE] = {
//     {0, 1, 3, INF, INF},
//     {INF, 0, 3, 6, INF},
//     {INF, INF, 0, 4, 2},
//     {INF, INF, INF, 0, 5},
//     {INF, INF, INF, INF, 0}};   // Edge
edgetype E[MAX_SIZE]; // Edge set
int m = 0;            // Edge count
edgetype F[MAX_SIZE];
int k = 0;
nodetype U[MAX_SIZE];

// Function prototype
void kruskal(void);
void makeset(int i);
int find(int i);
void merge(int p, int q);
bool equal(int p, int q);
void initial(int n);

// Function implementation
int main(void)
{
    int i, j;

    kruskal();

    // Print minnimum spanning tree
    printf("\n==== F ====\n");
    for (i = 0; i < k; i++)
        printf("(v%d, v%d) %d\n", F[i].i + 1, F[i].j + 1, F[i].weight);

    return 0;
}

void kruskal(void)
{
    int i, j, p, q;

    // Export edge set E from W
    for (i = 0; i < N; i++)
        for (j = i + 1; j < N; j++)
            if (W[i][j] != INF && W[i][j] != 0)
            {
                E[m].i = i;
                E[m].j = j;
                E[m].weight = W[i][j];
                m++;
            }

    // Sort the m edges in E by weight in nondecreasing order
    for (i = m - 1; i >= 0; i--)
        for (j = i - 1; j >= 0; j--)
            if (E[i].weight < E[j].weight)
            {
                edgetype temp = E[i];
                E[i] = E[j];
                E[j] = temp;
            }

#ifdef DEBUG
    // Print sorted edges
    printf("====Edges sorted list====\n");
    for (i = 0; i < m; i++)
        printf("(v%d, v%d) %d\n", E[i].i + 1, E[i].j + 1, E[i].weight);
#endif
    initial(N);

    for (i = 0; i < m; i++)
    {
        p = find(E[i].i);
        q = find(E[i].j);
        if (!equal(p, q))
        {
            merge(p, q);
            F[k].i = E[i].i;
            F[k].j = E[i].j;
            F[k++].weight = E[i].weight;
        }
#ifdef DEBUG
        printf("U: ");
        for (j = 0; j < N; j++)
            printf("%d ", U[j].parent + 1);
        printf("\n");
#endif
    }
}

void makeset(int i)
{
    U[i].parent = i;
    U[i].depth = 0;
}

int find(int i)
{
    int j;

    j = i;
    while (U[j].parent != j)
        j = U[j].parent;

    return j;
}

void merge(int p, int q)
{
    if (U[p].depth == U[q].depth)
    {
        U[p].depth++;
        U[q].parent = p;
    }
    // 깊이가 작은 트리를 자식 마디로 만든다
    else if (U[p].depth < U[q].depth)
        U[p].parent = q;
    else
        U[q].parent = p;
}

bool equal(int p, int q)
{
    return p == q ? true : false;
}

void initial(int n)
{
    int i;

    for (i = 0; i < n; i++)
        makeset(i);
}

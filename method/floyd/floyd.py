# -*- coding: utf-8 -*-
"""
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
inf inf inf 0 4
7 inf inf 5 0
"""
import copy

# Infinite weight
INF = 9999


def print_matrix(N, matrix: list) -> None:
    for i in range(1, N+1):
        for j in range(1, N+1):
            print('{:10}'.format(matrix[i][j]), end='')
        print()
    print()


def floyd2(N: int, D: list, P: list):
    for k in range(1, N + 1):  # Middle vertex
        for i in range(1, N + 1):  # Start vertex
            for j in range(1, N + 1):  # End vertex
                # If Start->Middle->End weight < Start->End weight
                if (D[i][k] + D[k][j]) < D[i][j]:
                    # Set middle vertex
                    P[i][j] = k
                    # Set shortest path weight
                    D[i][j] = D[i][k] + D[k][j]
    return D, P


def path(P, q: int, r: int):
    # print(f"path({q + 1}, {r + 1}): {P[q][r] + 1}")
    if (P[q][r] != 0):
        path(P, q, P[q][r])
        print(f"[v{P[q][r]}]", end=" ")
        path(P, P[q][r], r)
    # print(f"path({q + 1}, {r + 1}): exit")


if __name__ == "__main__":
    # Get vertex count
    N = int(input("Vertex count: "))
    # Weighted matrix
    W = list([None])

    # Initialize weighted graph matrix
    for i in range(N):
        before_weight = input().split()
        after_weight = list([None])
        for weight in before_weight:
            try:
                after_weight.append(int(weight))
            except ValueError:
                after_weight.append(INF)
        W.append(after_weight)

    # Maximum vertex number matrix in v_i to v_j
    P = [[0] * (N + 1) for _ in range(N + 1)]
    # Initialize shortest path matrix
    D = copy.deepcopy(W)

    print("\n =============== Weighted matrix(W) ===============")
    print_matrix(N, W)

    # Before excute matrix status
    # print("\n ========= Before shortest path matrix(D) =========")
    # print_matrix(N, D)
    # print("\n ========= Before shortest path matrix(P) =========")
    # print_matrix(N, P)
    D, P = floyd2(N, D, P)
    # After excute matrix status
    print("\n ========= After shortest path matrix(D) =========")
    print_matrix(N, D)
    print("\n ========= After shortest path matrix(P) =========")
    print_matrix(N, P)

    for i in range(1, N+1):
        for j in range(1, N + 1):
            if i == j:
                continue
            print(f"v{i} -> v{j}: [v{i}]", end=" ")
            path(P, i, j)
            print(f"[v{j}] ")

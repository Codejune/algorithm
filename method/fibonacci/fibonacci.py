import sys


def recursive_fibonacci(n: int):
    if (n <= 1):
        return 1
    return recursive_fibonacci(n - 1) + recursive_fibonacci(n - 2)


def iterative_fibonacci(n: int):
    result = [0]
    if n > 0:
        result.append(1)
        for i in range(2, n + 1):
            result.append(result[i-1] + result[i-2])
    return result[n]


if __name__ == "__main__":
    # Extend recursion limitation
    sys.setrecursionlimit(10**7)

    n = 14
    print(recursive_fibonacci(n))
    print(iterative_fibonacci(n))

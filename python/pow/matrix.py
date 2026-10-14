# --- BEGIN SOURCE: https://github.com/HarutoKobayashi/cp-templates/python/pow/matrix.py ---

from copy import deepcopy
from typing import Callable, TypeVar

T = TypeVar("T")


def matmul_semiring(
    A: list[list[T]],
    B: list[list[T]],
    add: Callable[[T, T], T],
    mul: Callable[[T, T], T],
    zero: T,  # add の単位元
) -> list[list[T]]:
    N, K, M = len(A), len(A[0]), len(B[0])
    C = [[zero] * M for _ in range(N)]
    for i in range(N):
        for j in range(K):
            if A[i][j] == zero:
                continue
            for k in range(M):
                C[i][k] = add(C[i][k], mul(A[i][j], B[j][k]))
    return C


def pow_matrix_semiring(
    A: list[list[T]],
    p: int,
    add: Callable[[T, T], T],
    mul: Callable[[T, T], T],
    zero: T,  # add の単位元
    one: T,  # mul の単位元
) -> list[list[T]]:
    """AをN次元正方行列だとすると、計算量はO(N^3logK)"""
    n = len(A)
    A = deepcopy(A)
    C = [[one if i == j else zero for j in range(n)] for i in range(n)]
    while p > 0:
        if p & 1:
            C = matmul_semiring(C, A, add, mul, zero)
        A = matmul_semiring(A, A, add, mul, zero)
        p >>= 1
    return C


# --- END SOURCE: https://github.com/HarutoKobayashi/cp-templates/python/pow/matrix.py ---

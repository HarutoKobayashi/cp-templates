# --- BEGIN SOURCE: BEGIN SOURCE: https://github.com/HarutoKobayashi/cp-templates/python/templete.py ---
from __future__ import annotations

import sys
from bisect import bisect_left, bisect_right
from collections import Counter, defaultdict, deque
from functools import cache, cmp_to_key
from heapq import heapify, heappop, heappush
from itertools import accumulate, combinations, groupby, permutations, product
from math import acos, asin, atan, ceil, comb, cos, factorial, floor, gcd, isqrt, lcm, log2, perm, pi, sin, tan

sys.setrecursionlimit(10**9)
IS_ATCODER = bool(int(__import__("os").getenv("ATCODER", "0")))
_readline, debug = sys.stdin.readline, (lambda *args: None) if IS_ATCODER else (lambda *args: __import__("devtools").debug(*args))
input, getint, getints = lambda: _readline().rstrip("\n"), lambda: int(_readline()), lambda: list(map(int, _readline().split()))
# --- END SOURCE: BEGIN SOURCE: https://github.com/HarutoKobayashi/cp-templates/python/templete.py ---

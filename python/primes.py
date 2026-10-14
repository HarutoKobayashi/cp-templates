# --- BEGIN SOURCE: https://github.com/HarutoKobayashi/cp-templates/python/primes.py ---

from math import gcd, isqrt


# エラトステネスの篩
def all_primes_le_(limit: int) -> list[int]:
    """limit 以下の素数を、エラトステネスの篩を用いて全列挙する。
    n := limit として、時間計算量 O(n log log n)、空間計算量 O(n)。
    limit <= 10^7 で使用すること。limit = 10^7 で 140ms 程度。
    """

    if limit < 2:
        return []
    if limit == 2:
        return [2]

    n_odds = (limit - 3) // 2 + 1
    sieve = bytearray(b"\x01") * n_odds
    r = isqrt(limit)
    last_i_to_check = (r - 3) // 2

    for i in range(last_i_to_check + 1):
        if sieve[i]:
            p = 2 * i + 3
            start = (p * p - 3) // 2
            step = p
            if start < n_odds:
                sieve[start::step] = b"\x00" * ((n_odds - 1 - start) // step + 1)

    primes = [2]
    primes.extend(2 * i + 3 for i, v in enumerate(sieve) if v)
    return primes


def all_primes_in_(L: int, R: int) -> list[int]:
    """区間 [l, r) に含まれる素数を全列挙する。
    Args:
        l (int): 区間の左端。
        r (int): 区間の右端。

    計算量は M = max(R-L+1, √R) として、O(M log log M)。
    """

    if R <= 2:
        return []
    if L < 0:
        raise ValueError("L must be non-negative.")
    if L >= R:
        return []

    n = R - L
    is_prime = bytearray(b"\x01") * n

    if L == 0:
        if n >= 1:
            is_prime[0] = 0
        if n >= 2:
            is_prime[1] = 0
    elif L == 1:
        is_prime[0] = 0

    limit = isqrt(R - 1)
    base_primes = all_primes_le_(limit)

    for p in base_primes:
        pp = p * p
        if pp >= R:
            break

        start = ((L + p - 1) // p) * p
        if start < pp:
            start = pp

        idx = start - L
        step = p
        is_prime[idx:n:step] = b"\x00" * (((n - 1 - idx) // step) + 1)

    return [L + i for i in range(n) if is_prime[i]]


if False:
    _SMALL_PRIMES = all_primes_le_(10000)
    _SMALL_PRIME_SET = set(_SMALL_PRIMES)

    # Miller–Rabin
    _MR_BASES = (2, 325, 9375, 28178, 450775, 9780504, 1795265022)

    def _is_prime_64(n: int) -> bool:
        if n < 2:
            return False
        for p in _SMALL_PRIMES[:12]:
            if n % p == 0:
                return n == p
        d = n - 1
        s = (d & -d).bit_length() - 1
        while d % 2 == 0:
            d //= 2
        for a in _MR_BASES:
            if a % n == 0:
                return True
            x = pow(a, d, n)
            if x == 1 or x == n - 1:
                continue
            passed = False
            for _ in range(s - 1):
                x = (x * x) % n
                if x == n - 1:
                    passed = True
                    break
            if not passed:
                return False
        return True

    # Pollard–Rho (Brent, 決定的パラメータ列)
    _PR_SEEDS = (
        (2, 1),
        (2, 3),
        (2, 5),
        (2, 7),
        (2, 11),
        (3, 1),
        (5, 1),
        (7, 1),
        (11, 1),
        (13, 1),
    )

    def _f_brent(x: int, c: int, mod: int) -> int:
        return (x * x + c) % mod

    def _pollard_rho_brent(n: int) -> int:
        if n % 2 == 0:
            return 2
        if n % 3 == 0:
            return 3
        for x0, c in _PR_SEEDS:
            y, r, q = x0, 1, 1
            g = 1
            while g == 1:
                x = y
                for _ in range(r):
                    y = _f_brent(y, c, n)
                k = 0
                while k < r and g == 1:
                    ys = y
                    m = 128
                    for _ in range(min(m, r - k)):
                        y = _f_brent(y, c, n)
                        q = (q * (x - y) % n) % n
                    g = gcd(q, n)
                    k += m
                r <<= 1
            if g == n:
                g = 1
                while g == 1:
                    ys = _f_brent(ys, c, n)
                    g = gcd(abs(x - ys), n)
            if 1 < g < n:
                return g
        i = 5
        while i * i <= n:
            if n % i == 0:
                return i
            if n % (i + 2) == 0:
                return i + 2
            i += 6
        return n

    def factorize(n: int, out: list[int] | None = None) -> list[int]:
        """n の素因数を重複ありで全列挙する。（例：20 -> [2,2,5]）
        最悪時間計算量 O(n^(1/4))、空間計算量 O(因子数)。
        n <= 10^18 で使用すること。特に重い個体（10^9程度の素数同士の積）で 110ms 程度。
        重複ごとにまとめたい or 辞書型でほしい場合には pf() を使用する。
        """
        if out is None:
            out = []
        if n < 0:
            out.append(-1)
            n = -n
        if n in (0, 1):
            return out
        for p in _SMALL_PRIMES:
            if p * p > n:
                break
            if n % p == 0:
                cnt = 0
                while n % p == 0:
                    n //= p
                    cnt += 1
                out.extend([p] * cnt)
        if n == 1:
            return out
        if _is_prime_64(n):
            out.append(n)
        else:
            d = _pollard_rho_brent(n)
            if d == n:
                out.append(n)
            else:
                factorize(d, out)
                factorize(n // d, out)
        return out

    def pf(n: int) -> dict[int, int]:
        """n の素因数分解を {素数: 指数} 形式で返す。（例：20 -> {2:2, 5:1}）
        最悪時間計算量 O(n^(1/4))、空間計算量 O(因子数)。
        n <= 10^18 で使用すること。特に重い個体（10^9程度の素数同士の積）で 110ms 程度。
        list でほしい場合には factorize() を使用する。
        """
        fs = factorize(n)
        fs.sort()
        res: dict[int, int] = {}
        for p in fs:
            res[p] = res.get(p, 0) + 1
        return res

    def divisors_from_pf(pf: dict[int, int], need_sort: bool = True) -> list[int]:
        """素因数分解 dict から約数を全列挙する。（例：{2:2, 5:1} -> [1,2,4,5,10,20]）
        時間計算量 O(約数の個数 + ソート)、空間計算量 O(約数の個数)。
        <= 10^18 の範囲で使用すること。特に重い個体で 150ms 程度。"""
        divs = [1]
        for p, a in pf.items():
            base = divs[:]
            mul = 1
            for _ in range(a):
                mul *= p
                divs.extend(d * mul for d in base)
        if need_sort:
            divs.sort()
        return divs

# --- END SOURCE: https://github.com/HarutoKobayashi/cp-templates/python/primes.py ---

# --- BEGIN SOURCE: https://github.com/HarutoKobayashi/cp-templates/python/mint.py ---

MAX = 10**6

fac = [1, 1]  # fac[i] = i! % MOD
fac_inv = [1, 1]  # finv[i] = (i!)^{-1} % MOD
inv = [0, 1]  # inv[i] = i^{-1} % MOD

for i in range(2, MAX):
    fac += [fac[-1] * i % MOD]
    inv += [MOD - inv[MOD % i] * (MOD // i) % MOD]
    fac_inv += [fac_inv[-1] * inv[i] % MOD]


def comb(n: int, r: int) -> int:
    if not (0 <= r <= n):
        return 0
    return fac[n] * fac_inv[r] % MOD * fac_inv[n - r] % MOD


# --- END SOURCE: https://github.com/HarutoKobayashi/cp-templates/python/mint.py ---

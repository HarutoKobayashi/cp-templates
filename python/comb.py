# --- BEGIN SOURCE: https://github.com/HarutoKobayashi/cp-templates/python/comb.py ---

# 二項係数の前計算
# 事前に nCk (0 <= k <= n <= MAX_N) の前計算（MODは素数に限定しない）
# O(MAX_N ^2)

MAX_N = 5000
MOD = 10007  # 素数でなくても良い

comb = [[0] * (MAX_N + 1) for _ in range(MAX_N + 1)]
comb[0][0] = 1
for i in range(1, MAX_N + 1):
    comb[i][0] = 1
    for j in range(1, i + 1):
        comb[i][j] = (comb[i - 1][j - 1] + comb[i - 1][j]) % MOD

# --- END SOURCE: https://github.com/HarutoKobayashi/cp-templates/python/comb.py ---

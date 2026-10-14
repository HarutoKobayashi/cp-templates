```python
# --- BEGIN SOURCE: https://github.com/HarutoKobayashi/cp-templates/python/snippets/doubling.md ---
# --- 適宜改変して使用する ---

dp = [list(i番目の要素は、最初に状態 i にいる場合に、1 回操作を行ったときの遷移先の番号(もちろんN以下))]
MAX = 10**9 # 最大遷移回数

# DP 構築
for _ in range(int(log2(MAX)) + 1):
    l = [0] * N
    dp.append(l)

# 漸化式に則ってDPを埋めていく
for step in range(1, int(log2(MAX)) + 2):
    for n in range(N):
        dp[step][n] = dp[step - 1][dp[step - 1][n]]

# 例：複数のクエリが飛んでくる場合
for _ in range(Q):
    t, n = getints() # 初期状態 n の t 回遷移した後の状態は？
    n -= 1 # n が 1-indexed だった場合
    
    # t を 2^k へと分解する
    a = []
    for i in range(int(log2(t)) + 1):
        if t >> i & 1:
            a.append(i)

    now = n # 初期状態
    for i in a:
        now = dp[i][now] # 2^k ごとに遷移

    print(now) # 時刻 t における状態を出力

# --- END SOURCE: https://github.com/HarutoKobayashi/cp-templates/python/snippets/doubling.md ---
```
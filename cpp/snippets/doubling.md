```cpp
// --- BEGIN SOURCE: https://github.com/HarutoKobayashi/cp-templates/cpp/snippets/doubling.md ---
// 適宜改変して使用する

int N, Q;
cin >> N >> Q;

ll MAX = 1e9; // 最大遷移回数

// dp[k][i]
// = 最初に状態 i にいるとき、2^k 回操作した後の遷移先
//
// dp[0][i]
// = 状態 i から 1 回操作したときの遷移先

int LOG = 0;
while ((1LL << LOG) <= MAX) LOG++; // int LOG = bit_length(MAX); でも OK

vector<vector<int>> dp(LOG, vector<int>(N));

// 1回遷移したときの遷移先を入力
for (int i = 0; i < N; i++) {
    cin >> dp[0][i];

    // 入力が 1-indexed なら 0-indexed に直す
    dp[0][i]--;
}


// 漸化式に則って DP を埋めていく
//
// 2^step 回進む
// = 2^(step-1) 回進んだあと、
//   さらに 2^(step-1) 回進む
for (int step: range(1, LOG)) {
    for (int n: range(N)) {
        dp[step][n]
            = dp[step - 1][dp[step - 1][n]];
    }
}


// 例：複数のクエリが飛んでくる場合
for (int q = 0; q < Q; q++) {
    ll t;
    int n;
    cin >> t >> n;
    // 初期状態 n の t 回遷移した後の状態は？

    n--; // n が 1-indexed だった場合

    int now = n; // 初期状態

    // t を 2^k の和に分解して、
    // ビットが立っているところだけ遷移する
    for (int i: range(LOG)) {
        if ((t >> i) & 1LL) {
            now = dp[i][now];
        }
    }

    // 問題の答えが 1-indexed なら +1
    cout << now + 1 << '\n';
}

// --- END SOURCE: https://github.com/HarutoKobayashi/cp-templates/cpp/snippets/doubling.md ---
```
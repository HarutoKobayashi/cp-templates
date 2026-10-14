```cpp
// --- BEGIN SOURCE: https://github.com/HarutoKobayashi/cp-templates/cpp/snippets/rotate-grid.md ---

    int H, W;
    cin >> H >> W;
    bool f = false;
    if (H < W) {
        f = true;
        swap(H, W);
    }

    vector<string> S(H, string(W, ' '));
    if (f) {
        vector<string> _S(W, string(H, ' '));
        getvec(_S);
        for (int i : range(H)) {
            for (int j : range(W)) {
                S[i][j] = _S[j][i];
            }
        }
    } else {
        getvec(S);
    }
    debug(S);

// --- END SOURCE: https://github.com/HarutoKobayashi/cp-templates/cpp/snippets/rotate-grid.md ---
```
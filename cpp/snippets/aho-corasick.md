```cpp
// --- BEGIN SOURCE: https://github.com/HarutoKobayashi/cp-templates/cpp/snippets/aho-corasick.md ---

    getints(N, L);
    vector<string> S(N);
    getvec(S);
    vector<vector<ll>> nexts;
    vector<ll> fail;
    vector<ll> bad;
    nexts.pb(vector<ll>(26, -1));
    fail.pb(0);
    bad.pb(0);

    for (int i : range(N)) {
        string s = S[i];
        ll v = 0;
        for (char c : s) {
            ll cv = ord(c) - ord('a');
            if (nexts[v][cv] == -1) {
                nexts[v][cv] = nexts.size();
                nexts.pb(vector<ll>(26, -1));
                fail.pb(0);
                bad.pb(0);
            }
            v = nexts[v][cv];
        }
        bad[v] = bad[v] | (1 << i);
    }

    auto go = [&](ll v, ll c) -> ll {
        while (true) {
            if (nexts[v][c] != -1) {
                return nexts[v][c];
            }
            if (v == 0) {
                return 0;
            }
            v = fail[v];
        }
    };

    dq<ll> q;
    for (int i : range(26)) {
        if (nexts[0][i] == -1) {
            continue;
        }
        ll v = nexts[0][i];
        fail[v] = 0;
        q.append(v);
    }
    while (not q.empty()) {
        ll v = q.popleft();
        bad[v] = bad[v] | bad[fail[v]];
        for (int i : range(26)) {
            if (nexts[v][i] == -1) {
                continue;
            }
            ll nv = nexts[v][i];
            fail[nv] = go(fail[v], i);
            q.append(nv);
        }
    }

// --- END SOURCE: https://github.com/HarutoKobayashi/cp-templates/cpp/snippets/aho-corasick.md ---
```
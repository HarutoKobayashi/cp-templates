# cp-templates

## C++ (`cpp/`)

| ファイル | 内容 |
| --- | --- |
| [`all-in-one.cpp`](cpp/all-in-one.cpp) | 諸々をすべてまとめた約 1500 行のファイル。普段はこれをベースに使用 |
| [`snippets/doubling.md`](cpp/snippets/doubling.md) | ダブリング用のテンプレート |
| [`snippets/aho-corasick.md`](cpp/snippets/aho-corasick.md) | Aho-Corasick 法 |
| [`snippets/rotate-grid.md`](cpp/snippets/rotate-grid.md) | 配列（グリッド）を 90 度回転する |

## Python (`python/`)

### 汎用

| ファイル | 内容 |
| --- | --- |
| [`templete.py`](python/templete.py) | 共通ヘッダ（入力まわりの関数、よく使うライブラリのインポートなど） |

### データ構造

| ファイル | 内容 |
| --- | --- |
| [`segtree.py`](python/segtree.py) | セグメント木 |
| [`sparse-table.py`](python/sparse-table.py) | スパーステーブル |
| [`cumulative-sum.py`](python/cumulative-sum.py) | 多次元累積和 |
| [`coord-compress.py`](python/coord-compress.py) | 座標圧縮 |

### 数学

| ファイル | 内容 |
| --- | --- |
| [`mint.py`](python/mint.py) | MOD のもとでの逆元の前計算。`comb(a, b) % MOD` も含む |
| [`comb.py`](python/comb.py) | `comb(a, b) % M` の前計算。M が素数でなくても適用可能 |
| [`primes.py`](python/primes.py) | 素因数分解・エラトステネスの篩など、素数関連 |
| [`pow/matrix.py`](python/pow/matrix.py) | 行列の高速累乗 |

### 文字列

| ファイル | 内容 |
| --- | --- |
| [`rolling-hash.py`](python/rolling-hash.py) | ローリングハッシュ |

### グラフ (`graph/`)

| ファイル | 内容 |
| --- | --- |
| [`dijkstra.py`](python/graph/dijkstra.py) | ダイクストラ法（最短路） |
| [`kraskal.py`](python/graph/kraskal.py) | クラスカル法（最小全域木） |
| [`warshall-floyd.py`](python/graph/warshall-floyd.py) | ワーシャル–フロイド法（最短路） |
| [`three-color.py`](python/graph/three-color.py) | 深さ優先探索（三色法）による有向グラフのサイクル検出 |
| [`tree-toporogical-sort.py`](python/graph/tree-toporogical-sort.py) | 木のトポロジカルソート |

### その他

| ファイル | 内容 |
| --- | --- |
| [`arg-sort.py`](python/arg-sort.py) | 偏角ソート用の比較関数（`functools.cmp_to_key` に渡して使用） |
| [`diag-traverse.py`](python/diag-traverse.py) | グリッドを斜め方向に走査するジェネレータ |

### スニペット (`snippets/`)

| ファイル | 内容 |
| --- | --- |
| [`doubling.md`](python/snippets/doubling.md) | ダブリング用のテンプレート |

## 補足

- `snippets/` 以下の Markdown ファイルはコード片です。問題に応じて中身を埋める必要があり、そのままでは動作しません。
  - その他のファイルも、`inf`, `MOD`, `MAX` など問題に応じて変えるべき部分は記述されていません。
- 各ファイルはコピーして提出コードに貼り付けて使う想定です。

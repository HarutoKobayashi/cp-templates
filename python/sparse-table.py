# --- BEGIN SOURCE: https://github.com/HarutoKobayashi/cp-templates/python/sparse-table.py ---


class SparseTable:
    def __init__(self, arr: list[int], op=lambda x, y: min(x, y)) -> None:
        """Sparse Table

        特徴：
        * arr のRMQなどを O(1) で取得できる。
            * st.query(l, r) = min(arr[l:r]) など。
        * ここで、集約関数 op は、x = op(x, x) を満たす必要がある。
            * min, max, and, or など、かなり限定的。

        初期化にかかる計算量：
        * 時間計算量 O(nlogn)
        * 空間計算量 O(nlogn)

        Args:
            arr (list[int]): 1次元のリスト。
            op: 集約に用いる関数。x = op(x, x) を満たす必要がある。default to min.
        """
        self.n = len(arr)
        self.K = self.n.bit_length()
        self.st = [arr[:]]  # st[0] = arr
        self.op = op
        for k in range(1, self.K):
            prev = self.st[k - 1]
            size = self.n - (1 << k) + 1
            cur = [op(prev[i], prev[i + (1 << (k - 1))]) for i in range(size)]
            self.st.append(cur)

    def query(self, l: int, r: int) -> int:
        """区間 [l, r) を op で集約した結果を計算する。

        計算量：
        * 時間計算量 O(1)

        Args:
            l (int): 区間 [l, r) の左端。0 以上。
            r (int): 区間 [l, r) の右端。len(arr) 以下。

        Returns:
            int: 集約結果。
                op = min であれば、min(A[l:r]) に一致。
        """

        k = (r - l).bit_length() - 1
        return self.op(self.st[k][l], self.st[k][r - (1 << k)])


# --- END SOURCE: https://github.com/HarutoKobayashi/cp-templates/python/sparse-table.py ---

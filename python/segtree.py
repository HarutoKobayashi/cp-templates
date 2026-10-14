# --- BEGIN SOURCE: https://github.com/HarutoKobayashi/cp-templates/python/segtree.py ---

## 参考 ##
# https://atcoder.github.io/ac-library/master/document_ja/segtree.html
# https://github.com/not522/ac-library-python

from typing import Any, Callable, Union


class SegTree:
    """モノイド (S,⋅: SxS → S, e ∈ S)、つまり以下を満たす代数構造に対し使用できるデータ構造です。
    * 結合律：(a・b)・c = a・(b・c) for all a,b,c ∈ S
    * 単位元の存在：a・e = e・a = a for all a ∈ S

    長さ n の S の配列に対し、O(log n) で以下の操作を行うことができます。
    * 要素の1点変更
    * 区間の要素の総積の取得

    また、このクラスはオラクルとして op, e の 2 種類を使用しますが、これらが定数時間で動くものと仮定したときの計算量を記述します。
    オラクル内部の計算量が O(f(n)) である場合には全ての計算量が O(f(n)) 倍になります。
    """

    def __init__(
        self,
        op: Callable[[Any, Any], Any],
        e: Any,
        v: int | list[Any],
    ) -> None:
        """次のように初期化します：
        * (v が int のとき) 長さ v の数列 a を作ります。初期値は全て e です。
        * (v が list[Any] のとき) 長さ len(v) の数列 a を作ります。v の内容が初期値となります。

        Args:
            op (Callable[[Any, Any], Any]): 二項演算。
            e (Any): 単位元。
            v (Union[int, List[Any]]): 配列長または初期配列。

        制約:
            0 <= n < 10^8。

        時間計算量:
            O(n)。
        """
        self._op = op
        self._e = e

        if isinstance(v, int):
            v = [e] * v

        self._n = len(v)
        if self._n:
            _x = 0
            while (1 << _x) < self._n:
                _x += 1
            self._log = _x
        else:
            self._log = 0
        self._size = 1 << self._log
        self._d = [e] * (2 * self._size)

        for i in range(self._n):
            self._d[self._size + i] = v[i]
        for i in range(self._size - 1, 0, -1):
            self._update(i)

    def set(self, p: int, x: Any) -> None:
        """a[p] に x を代入します。

        Args:
            p (int): 更新する配列要素の要素番号。
            x (Any): 新しい値。

        制約:
            0 <= p < n。

        時間計算量:
            O(log n)。
        """
        assert 0 <= p < self._n, f"0 <= p < {self._n} required, but p = {p}"

        p += self._size
        self._d[p] = x
        for i in range(1, self._log + 1):
            self._update(p >> i)

    def get(self, p: int) -> Any:
        """a[p] を返します。

        Args:
            p (int): 取得する配列要素の要素番号。

        Returns:
            Any: a[p]。

        制約:
            0 <= p < n。

        時間計算量:
            O(1)。
        """
        assert 0 <= p < self._n, f"0 <= p < {self._n} required, but p = {p}"

        return self._d[p + self._size]

    def prod(self, left: int, right: int) -> Any:
        """op(a[l], a[l + 1],..., a[r - 1]) を、モノイドの性質を満たしていると仮定して計算します。l = r のときは e を返します。

        Args:
            left: 左端。left <= right。
            right: 右端。left <= right。

        Returns:
            Any: op(a[l], a[l + 1],..., a[r - 1])。

        制約:
            0 <= l <= r <= n。

        時間計算量:
            O(log n)。
        """
        assert 0 <= left <= right <= self._n, f"0 <= left <= right <= {self._n} required, but (left, right) = ({left}, {right})"
        sml = self._e
        smr = self._e
        left += self._size
        right += self._size

        while left < right:
            if left & 1:
                sml = self._op(sml, self._d[left])
                left += 1
            if right & 1:
                right -= 1
                smr = self._op(self._d[right], smr)
            left >>= 1
            right >>= 1

        return self._op(sml, smr)

    def all_prod(self) -> Any:
        """op(a[0], a[1],..., a[n - 1]) を計算します。n = 0 のときは e を返します。

        Returns:
            Any: op(a[0], a[1],..., a[n - 1])。

        時間計算量:
            O(1)。
        """
        return self._d[1]

    def max_right(self, left: int, f: Callable[[Any], bool]) -> int:
        """以下の条件を両方満たす r を(いずれか1つ)返します。
        f が単調だとすれば、「 f(prod(l, r)) = True となる最大の r 」と解釈することが可能です。
        * r = l もしくは f(prod(l, r)) = True
        * r = n もしくは f(prod(l, r + 1)) = False

        Args:
            left (int): 探索を始める位置。(=l)
            f (Callable[[Any], bool]): S を引数にとり、 bool を返す関数。

        Returns:
            int: f(prod(l, r)) = True となる最大の r。

        制約:
        * f を同じ引数で呼んだ時、返り値は等しい(=副作用はない)。
        * f(e) = True。
        * 0 <= l <= n。

        時間計算量:
            O(log n)。
        """
        assert 0 <= left <= self._n, f"0 <= left < {self._n} required, but p = {left}"
        assert f(self._e), f"f({self._e}) should be True, but False"

        if left == self._n:
            return self._n

        left += self._size
        sm = self._e

        first = True
        while first or (left & -left) != left:
            first = False
            while left % 2 == 0:
                left >>= 1
            if not f(self._op(sm, self._d[left])):
                while left < self._size:
                    left *= 2
                    if f(self._op(sm, self._d[left])):
                        sm = self._op(sm, self._d[left])
                        left += 1
                return left - self._size
            sm = self._op(sm, self._d[left])
            left += 1

        return self._n

    def min_left(self, right: int, f: Callable[[Any], bool]) -> int:
        """以下の条件を両方満たす l を(いずれか1つ)返します。
        f が単調だとすれば、「 f(prod(l, r)) = True となる最小の l 」と解釈することが可能です。
        * l = r もしくは f(prod(l, r)) = True
        * l = 0 もしくは f(prod(l - 1, r)) = False

        Args:
            right (int): 探索を始める位置。(=r)
            f (Callable[[Any], bool]): S を引数にとり、 bool を返す関数。

        Returns:
            int: f(prod(l, r)) = True となる最小の l。

        制約:
        * f を同じ引数で呼んだとき、返り値は等しい(=副作用はない)。
        * f(e) = True。
        * 0 <= r <= n。

        時間計算量:
            O(log n)。
        """
        assert 0 <= right <= self._n, f"0 <= right <= {self._n} required, but right = {right}"
        assert f(self._e), f"f({self._e}) should be True, but False"

        if right == 0:
            return 0

        right += self._size
        sm = self._e

        first = True
        while first or (right & -right) != right:
            first = False
            right -= 1
            while right > 1 and right % 2:
                right >>= 1
            if not f(self._op(self._d[right], sm)):
                while right < self._size:
                    right = 2 * right + 1
                    if f(self._op(self._d[right], sm)):
                        sm = self._op(self._d[right], sm)
                        right -= 1
                return right + 1 - self._size
            sm = self._op(self._d[right], sm)

        return 0

    def _update(self, k: int) -> None:
        self._d[k] = self._op(self._d[2 * k], self._d[2 * k + 1])


# --- END SOURCE: https://github.com/HarutoKobayashi/cp-templates/python/segtree.py ---

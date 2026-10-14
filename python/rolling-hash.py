# --- BEGIN SOURCE: https://github.com/HarutoKobayashi/cp-templates/python/rolling-hash.py ---

import random
from typing import Iterable


def base_generator() -> int:
    """
    10^8〜10^9 の範囲で奇数の基数をランダムに生成する。

    Returns:
        int: 10^8〜10^9 の奇数。Rolling Hash の基数として使用。
    計算量:
        O(1)
    """
    rng = random.Random()
    ans = rng.randrange(10**8, 10**9)
    if ans % 2 == 0:
        return ans - 1
    return ans


class RollingHash61:
    """
    2^61-1（メルセンヌ素数）を法とするローリングハッシュ。
    ・前計算 O(N)、任意区間のハッシュ取得 O(1)

    参考：https://qiita.com/keymoon/items/11fac5627672a6d6a9f6
    """

    # 2^61 - 1
    _MOD: int = (1 << 61) - 1

    def __init__(
        self,
        s: str | Iterable[int] | bytes,
        base: int | None = None,
        mapper: callable | None = None,
    ) -> None:
        """
        Args:
            s (str | Iterable[int] | bytes):
                ハッシュ化対象の列。
                str の場合は ord(c)+1 に、bytes の場合は各バイト+1 に変換。
            base (int | None, optional):
                ハッシュの基数。None の場合は base_generator() で自動生成。
            mapper (callable | None, optional):
                各要素を int に写す関数。None の場合はデフォルト（ord+1）。

        計算量:
            O(len(s))
        """

        # 基数
        if base is None:
            base = base_generator()
        self.base: int = base

        # 入力列を整数化
        if mapper is None:
            if isinstance(s, (bytes, bytearray)):
                # 0 は避けたいので +1 しておく（先頭ゼロ問題の回避）
                a = [x + 1 for x in s]
            elif isinstance(s, str):
                a = [ord(c) + 1 for c in s]
            else:
                # 汎用：要素はすでに int だと仮定（必要なら +1 する）
                a = [int(x) + 1 for x in s]
        else:
            a = [int(mapper(x)) for x in s]

        self.n: int = len(a)

        # 累乗と prefix hash の前計算
        self._pow = [1] * (self.n + 1)
        self._hash = [0] * (self.n + 1)
        b = self.base
        for i, x in enumerate(a):
            self._pow[i + 1] = self._mul(self._pow[i], b)
            self._hash[i + 1] = self._mod(self._mul(self._hash[i], b) + x)

    # 内部：2^61-1 用の高速 mod / mul
    @classmethod
    def _mod(cls, x: int) -> int:
        """
        Mersenne mod（2^61-1）の高速還元
        """
        x = (x & cls._MOD) + (x >> 61)
        if x >= cls._MOD:
            x -= cls._MOD
        return x

    @classmethod
    def _mul(cls, a: int, b: int) -> int:
        """
        a*b を 128bit 相当で計算し、2^61-1 で還元
        """
        # (a * b) を 128bit とみなして分割
        au = a >> 31
        ad = a & ((1 << 31) - 1)
        bu = b >> 31
        bd = b & ((1 << 31) - 1)
        mid = ad * bu + au * bd
        midu = mid >> 30
        midd = mid & ((1 << 30) - 1)
        x = cls._mod(au * bu * 2 + midu + (midd << 31) + ad * bd)
        return x

    def get(self, l: int, r: int) -> int:
        """
        部分文字列 s[l:r) のハッシュ値を取得する。O(1).
        * l, r ともに 0-indexed.

        Args:
            l (int): 区間の左端インデックス（含む）。
            r (int): 区間の右端インデックス（含まない）。

        Returns:
            int: s[l:r) のハッシュ値。
        """
        # h[r] - h[l]*B^(r-l)
        res = self._hash[r] - self._mul(self._hash[l], self._pow[r - l])
        return self._mod(res)

    def concat(self, h1: int, h2: int, len2: int) -> int:
        """
        2つの部分文字列ハッシュを連結したハッシュを計算する。O(1).
        * 例： 'abc' と 'defg' それぞれのハッシュ値から、'abcdefg' のハッシュ値を得る。

        Args:
            h1 (int): 部分文字列 A のハッシュ値。
            len1 (int): A の長さ。
            h2 (int): 部分文字列 B のハッシュ値。
            len2 (int): B の長さ。

        Returns:
            int: 連結文字列 A||B のハッシュ値。
        """
        return self._mod(self._mul(h1, self._pow[len2]) + h2)

    def longest_common_prefix(self, i: int, j: int) -> int:
        """
        s[i:] と s[j:] の最長共通接頭辞長（LCP）を求める。O(logN).

        Args:
            i (int): 最初の開始位置。
            j (int): 2つ目の開始位置。

        Returns:
            int: LCP 長。
        """
        n = self.n
        hi = min(n - i, n - j)
        lo = 0
        # 上に寄せる二分探索（[lo, hi)）
        while lo < hi:
            mid = (lo + hi + 1) >> 1
            if self.get(i, i + mid) == self.get(j, j + mid):
                lo = mid
            else:
                hi = mid - 1
        return lo

    # 逆向き用（回文判定などに使う）
    @classmethod
    def for_reverse(cls, s: str | Iterable[int] | bytes, base: int | None = None) -> RollingHash61:
        """
        逆向き文字列で構築するショートカット。
        """
        if isinstance(s, (bytes, bytearray)):
            return cls(bytes(reversed(s)), base=base)
        elif isinstance(s, str):
            return cls(s[::-1], base=base)
        else:
            return cls(list(reversed(list(s))), base=base)


# --- END SOURCE: https://github.com/HarutoKobayashi/cp-templates/python/rolling-hash.py ---

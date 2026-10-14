# --- BEGIN SOURCE: https://github.com/HarutoKobayashi/cp-templates/python/cumulative-sum.py ---


class KDimCumulativeSum:
    """
    K次元の累積和を構築し、任意のK次元直方体領域の総和を高速に求めるためのクラス。

    各次元のサイズが lim = (lim[0], ..., lim[k-1]) の多次元配列を
    1次元の配列に変換して保持し、build() 実行後は各次元方向に
    累積和をとることで「原点から各座標までの和」を格納する。
    クエリ時は2^K個の頂点を、隣り合う頂点同士でちょうど1つの
    次元の値だけが変わるような順序で辿ることで、
    包除原理による差分計算だけで任意の直方体領域の和を求める。

    Args:
        k (int): 次元数。
        *lim (int): 各次元のサイズ（lim[0], lim[1], ..., lim[k-1]）。
            * 第 i 次元は [0, lim[i]) の範囲のみ扱う。
    """

    def __init__(self, k: int, *lim):
        self.k = k
        self.size = 1
        self.lim = lim
        for length in self.lim:
            self.size *= length

        # stride[i] : 次元iの座標を1増やすと、1次元配列上の
        #             インデックスがいくつ増えるか（重み）
        self.stride = [1] * self.k
        for i in range(1, self.k):
            self.stride[i] = self.stride[i - 1] * self.lim[i - 1]

        self.data = [0] * self.size
        self.is_built = False

        # --- 頂点を辿る順序の事前計算 ---
        # query_coords() で2^K個の頂点を包除原理で辿る際、
        # 1つ前の頂点から「どの次元の値が変わったか」と
        # 「増える方向・減る方向どちらの変化か」を
        # あらかじめ列挙しておくことで、
        # 各ステップの座標差分計算をO(1)で行えるようにする。
        self.step_dim = []  # このステップで値が変わる次元
        self.step_is_increase = []  # True: 増える方向の変化 / False: 減る方向の変化
        self.step_code = []  # このステップにおける各次元の状態を表すビット集合
        self.step_subtract = []  # True: このステップでは和から引く（包除原理の符号）

        prev_code = 0
        for i in range(1, 1 << self.k):
            curr_code = i ^ (i >> 1)
            changed_bits = prev_code ^ curr_code
            changed_dim = changed_bits.bit_length() - 1

            self.step_dim.append(changed_dim)
            self.step_is_increase.append(bool(curr_code & changed_bits))
            self.step_code.append(curr_code)
            self.step_subtract.append(bool(i & 1))
            prev_code = curr_code

    def to_index(self, *idxs) -> int:
        """
        各次元の座標を、内部で保持する1次元配列のインデックスに変換する。

        Args:
            *idxs (int): 各次元の座標（idxs[0], ..., idxs[k-1]）。

        Returns:
            int: 対応する1次元配列上のインデックス。
        """
        index = 0
        weight = 1
        for i in range(self.k):
            index += idxs[i] * weight
            weight *= self.lim[i]
        return index

    def get_coordinate(self, index: int, dim: int) -> int:
        """
        1次元配列のインデックスから、指定した次元の座標値を取り出す。

        Args:
            index (int): 1次元配列上のインデックス。
            dim (int): 取り出したい次元のインデックス。

        Returns:
            int: 指定次元における座標値。
        """
        return index // self.stride[dim] % self.lim[dim]

    def add_value(self, index: int, value) -> None:
        """
        指定したインデックスの位置に値を加算する。
        build() 実行前にのみ呼び出し可能。

        Args:
            index (int): 値を加算する位置のインデックス。
            value: 加算する値。

        Returns:
            None
        """
        assert not self.is_built
        self.data[index] += value

    def build(self) -> None:
        """
        各次元方向に累積和をとり、data を
        「原点から各座標までの和」に変換する。
        以後、add_value() は呼び出せなくなる。

        Returns:
            None
        """
        assert not self.is_built
        self.is_built = True
        data = self.data
        for dim in range(self.k):
            step = self.stride[dim]
            dim_len = self.lim[dim]
            period = step * dim_len
            for base in range(0, self.size, period):
                for x in range(base + step, base + period):
                    data[x] += data[x - step]

    def query(self, lower_index: int, upper_index: int):
        """
        インデックスで指定した2点 lower, upper について、
        各次元の座標が [lower[dim], upper[dim]] の範囲に収まる
        直方体領域の総和を求める。

        Args:
            lower_index (int): 領域の下限側の点のインデックス。
            upper_index (int): 領域の上限側の点のインデックス。

        Returns:
            各次元の座標が下限～上限の範囲に入る領域の総和。
        """
        lower_coords = [self.get_coordinate(lower_index, dim) for dim in range(self.k)]
        upper_coords = [self.get_coordinate(upper_index, dim) for dim in range(self.k)]
        return self.query_coords(lower_coords, upper_coords)

    def query_coords(self, lower_coords, upper_coords):
        """
        各次元ごとの下限座標・上限座標を指定して、
        直方体領域の総和を包除原理により求める。

        build() 済みの累積和 data に対し、2^K個の頂点を
        「隣り合う頂点同士でちょうど1つの次元だけが変わる」順序で
        辿りながら、その差分だけをインデックスに反映させることで、
        少ない計算量で結果を求める。

        Args:
            lower_coords (list[int]): 各次元の下限座標（長さk）。
            upper_coords (list[int]): 各次元の上限座標（長さk）。

        Returns:
            指定した直方体領域の総和。下限が上限を上回る次元が
            1つでもあれば 0 を返す。
        """
        assert self.is_built

        for dim in range(self.k):
            if lower_coords[dim] > upper_coords[dim]:
                return 0

        index = 0
        diff = [0] * self.k
        skip_dims = 0

        for dim in range(self.k):
            upper_term = upper_coords[dim] * self.stride[dim]
            index += upper_term
            if lower_coords[dim] == 0:
                skip_dims |= 1 << dim
            else:
                lower_term = (lower_coords[dim] - 1) * self.stride[dim]
                diff[dim] = lower_term - upper_term

        data = self.data
        result = data[index]

        step_dim = self.step_dim
        step_is_increase = self.step_is_increase
        step_code = self.step_code
        step_subtract = self.step_subtract

        for i in range(len(step_dim)):
            if step_is_increase[i]:
                index += diff[step_dim[i]]
            else:
                index -= diff[step_dim[i]]

            if step_code[i] & skip_dims:
                continue

            if step_subtract[i]:
                result -= data[index]
            else:
                result += data[index]

        return result


# --- END SOURCE: https://github.com/HarutoKobayashi/cp-templates/python/cumulative-sum.py ---

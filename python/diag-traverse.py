# --- BEGIN SOURCE: https://github.com/HarutoKobayashi/cp-templates/python/diag-traverse.py ---


def diag_traverse(H: int, W: int, reverse: bool = False) -> tuple[int, int]:
    """2次元配列を斜めに読んでいくジェネレータ。
    各対角線で右上→左下の順になるようにインデックスを返す。

    盤面例：
    * [1, 2, 3]
    * [4, 5, 6]
    * [7, 8, 9]

    このときのたどり順：
    * reverse=False： 1 | 2, 4 | 3, 5, 7 | 6, 8 | 9
    * reverse=True： 9 | 6, 8 | 3, 5, 7 | 2, 4 | 1
    """

    if not reverse:
        for s in range(H + W - 1):  # s = i + j
            i_start = max(0, s - (W - 1))  # その対角線の最上段の i
            i_end = min(H - 1, s)  # その対角線の最下段の i
            for i in range(i_start, i_end + 1):
                j = s - i
                yield (i, j)
    else:
        for s in range(H + W - 2, -1, -1):  # 右下(=最大s)→左上(=0)
            i_start = max(0, s - (W - 1))
            i_end = min(H - 1, s)
            for i in range(i_start, i_end + 1):
                j = s - i
                yield (i, j)


# --- END SOURCE: https://github.com/HarutoKobayashi/cp-templates/python/diag-traverse.py ---

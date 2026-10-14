# --- BEGIN SOURCE: https://github.com/HarutoKobayashi/cp-templates/python/coord-compress.py ---

from bisect import bisect_left


class CoordCompress:
    def __init__(self, vals):
        self.table = sorted(set(vals))
        self.to_idx = {v: i for i, v in enumerate(self.table)}

    def compress(self, x):
        if type(x) is not list:
            return self.to_idx[x]
        else:
            return [self.to_idx[y] for y in x]

    def compress_near(self, x):
        if type(x) is not list:
            return bisect_left(self.table, x)
        else:
            return [bisect_left(self.table, y) for y in x]

    def decompress(self, i):
        if type(i) is not list:
            return self.table[i]
        else:
            return [self.table[j] for j in i]


# --- END SOURCE: https://github.com/HarutoKobayashi/cp-templates/python/coord-compress.py ---

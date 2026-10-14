# --- BEGIN SOURCE: https://github.com/HarutoKobayashi/cp-templates/python/arg-sort.py ---


def arg_cmp(a, b):
    """偏角ソートを行う。同じ偏角の場合は長さが短いものほど手前にする。"""
    ax, ay = a
    bx, by = b
    assert a != (0, 0)
    assert b != (0, 0)

    ha = 0 if (ay > 0 or (ay == 0 and ax > 0)) else 1
    hb = 0 if (by > 0 or (by == 0 and bx > 0)) else 1
    if ha != hb:
        return -1 if ha < hb else 1

    cross = ax * by - ay * bx
    if cross != 0:
        return -1 if cross > 0 else 1

    na = ax * ax + ay * ay
    nb = bx * bx + by * by
    if na != nb:
        return -1 if na < nb else 1
    return 0


# --- END SOURCE: https://github.com/HarutoKobayashi/cp-templates/python/arg-sort.py ---

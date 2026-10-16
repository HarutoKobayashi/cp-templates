# --- BEGIN SOURCE: https://github.com/HarutoKobayashi/cp-templates/python/graph/tree-topological-sort.py ---


def tree_order(root: int, graph: list[list[int]]) -> tuple[list[int], list[int]]:
    """トポロジカルソートされた頂点列と、各頂点の親を表す配列を返す。
    i が j の祖先ならば、order.index(i) < order.index(j) である。
    i が j の親ならば、parent[j] = i である。

    * 根から処理する場合はこのまま使用する
    * 葉から処理する場合は reversed(order) を使用する
    """
    n = len(graph)
    parent = [-1] * n
    order = [root]
    for v in order:
        for nv in graph[v]:
            if nv == parent[v]:
                continue
            parent[nv] = v
            order.append(nv)
    return order, parent


# --- END SOURCE: https://github.com/HarutoKobayashi/cp-templates/python/graph/tree-topological-sort.py ---

# --- BEGIN SOURCE: https://github.com/HarutoKobayashi/cp-templates/python/graph/kruskal.py ---


def kruskal(graph: list[list[tuple[int, int]]]) -> tuple[int, list[tuple[int, int, int]]]:
    """クラスカル法を実行し最小全域木(MST)を求める関数。O(ElogE).

    Args:
        graph (list[list[tuple[int, int]]]): 辺の情報が格納されたリスト。
            始点番号 -> [(終点番号, コスト), ... ] の形式。

    Returns:
        total_cost (int): MST の重み総和（連結でない場合は最小全域森の総和）
        mst_edges (list[tuple[int, int, int]]): MST を構成する辺のリスト [(u, v, w), ...]
    """
    n = len(graph)
    dsu = DSU(n)

    edges: list[tuple[int, int, int]] = []
    for u in range(n):
        for v, w in graph[u]:
            if u < v:
                edges.append((w, u, v))

    edges.sort()

    total_cost = 0
    mst_edges: list[tuple[int, int, int]] = []
    for w, u, v in edges:
        if not dsu.same(u, v):
            dsu.merge(u, v)
            total_cost += w
            mst_edges.append((u, v, w))
            if len(mst_edges) == n - 1:
                break

    return total_cost, mst_edges


# --- END SOURCE: https://github.com/HarutoKobayashi/cp-templates/python/graph/kruskal.py ---

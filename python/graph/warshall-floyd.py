# --- BEGIN SOURCE: https://github.com/HarutoKobayashi/cp-templates/python/graph/warshall-floyd.py ---


def warshall_floyd(num_node: int, graph: list[list[tuple[int, int]]]) -> list[list[int]]:
    """ワーシャルフロイド法を実行する関数。（O(V^3)）。
    全頂点対最短路問題を解く。
    頂点番号はすべて 0-indexed で、[0, 1, ..., num_node - 1] のいずれか。

    Args:
        num_node (int): 頂点数。
        graph (list[list[tuple[int, int]]]): 辺の情報が格納されたリスト。
            始点番号 -> [(終点番号, コスト), ... ] の形式。

    Returns:
        list[list[int]]: 各頂点対間の最小コスト。
            dist[i][j] は、頂点 i から頂点 j へ移動する場合の最小コストを表す。
            到達不可能な場合は inf。
    """

    dist = [[inf] * num_node for _ in range(num_node)]

    for i in range(num_node):
        dist[i][i] = 0

    for u in range(num_node):
        for v, cost in graph[u]:
            if cost < dist[u][v]:
                dist[u][v] = cost

    for k in range(num_node):
        for i in range(num_node):
            dik = dist[i][k]
            if dik == inf:
                continue
            for j in range(num_node):
                if dist[k][j] < inf:
                    nd = dik + dist[k][j]
                    if nd < dist[i][j]:
                        dist[i][j] = nd

    return dist


# --- END SOURCE: https://github.com/HarutoKobayashi/cp-templates/python/graph/warshall-floyd.py ---

# --- BEGIN SOURCE: https://github.com/HarutoKobayashi/cp-templates/python/graph/dijkstra.py ---


def dijkstra(start_node: int, num_node: int, graph: list[list[tuple[int, int]]]) -> list[int]:
    """ダイクストラ法を実行する関数。（O(E*log(V))）。
    頂点番号はすべて 0-indexed で、[0, 1,..., num_node - 1] のいずれか。
    Args:
        start_node (int): 開始地点を表す頂点番号。
        num_node (int): 頂点数。
        graph (list[list[tuple[int, int]]]): 辺の情報が格納されたリスト。
            始点番号 -> [(終点番号, コスト), ... ] の形式。
    Returns:
        list[int]: 開始地点から各頂点へ移動する場合の最小コスト。終点番号 -> 最小コスト。
    """
    dist = [inf] * num_node
    dist[start_node] = 0
    finished = set()
    q = []
    heappush(q, (0, start_node))
    while len(q) > 0:
        _, min_point = heappop(q)
        if min_point in finished:
            continue

        finished.add(min_point)
        for goal, cost in graph[min_point]:
            new_cost = dist[min_point] + cost
            # 更新条件
            if new_cost < dist[goal]:
                dist[goal] = new_cost
                heappush(q, (new_cost, goal))
    return dist


# --- END SOURCE: https://github.com/HarutoKobayashi/cp-templates/python/graph/dijkstra.py ---

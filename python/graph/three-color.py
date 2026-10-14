# --- BEGIN SOURCE: https://github.com/HarutoKobayashi/cp-templates/python/graph/three-color.py ---

white, gray, black = 0, 1, 2
color = [white] * N


def dfs(cur):
    color[cur] = gray
    for nex in graph[cur]:
        if color[nex] == gray:
            return True
        if color[nex] == white and dfs(nex):
            return True
    color[cur] = black
    return False


any(dfs(cur) for cur in range(N) if color[cur] == white)  # これが True ならサイクルあり

# --- END SOURCE: https://github.com/HarutoKobayashi/cp-templates/python/graph/three-color.py ---

from collections import deque
#bfs
def bfs_search(graph, start, end):
    if start not in graph or end not in graph:
        return [] , -1#无效起始
    
    path = []
    #请在以下区域完成BFS算法的代码，求解路径path
    # parent[node] 表示节点的父节点
    parent = {}
    # visited 用于记录已经访问过的节点
    visited = {}
    for node in graph.keys():
        visited[node] = False
    # 初始化起始节点
    parent[start] = None
    visited[start] = True
    # BFS
    queue = deque([start])
    while queue:
        node = queue.popleft()
        for neighbor in graph[node]:
            if not visited[neighbor]:
                visited[neighbor] = True
                parent[neighbor] = node
                queue.append(neighbor)
    # 从终点回溯到起点
    node = end
    while node:
        path.insert(0, node)
        node = parent[node]
    
    return path, len(path)-1

#dfs
def dfs_search(graph, start, end):
    if start not in graph or end not in graph:
        return [], -1#无效起始
    path = []
    #请在以下区域完成DFS算法的代码，求解路径path
    
    path.append(start)
    visited = {}
    for node in graph.keys():
        visited[node] = False
    # DFS
    def dfs(node, visited, path):
        if node == end:
            return [path[:]]
        paths = []
        visited.add(node)
        for neighbor in graph[node]:
            if neighbor not in visited:
                path.append(neighbor)
                paths.extend(dfs(neighbor, visited, path))
                path.pop()
                
        visited.remove(node)
        return paths

    best_paths = dfs(start, set(), [start])
    print(best_paths)

    path = min(best_paths, key=len)
    
    return path, len(path)-1

# 含环图的邻接表
cyclic_graph = {
    'A': ['B', 'C'],
    'B': ['A', 'D'],  # A-B-A 形成环
    'C': ['A', 'D', 'F'],
    'D': ['B', 'C', 'E'],
    'E': ['D', 'F'],
    'F': ['C', 'E']
}

# 测试 BFS
path, dist = bfs_search(cyclic_graph, 'A', 'F')
print(f"路径: {path}, 距离: {dist}")
# 测试 DFS
path, dist = dfs_search(cyclic_graph, 'A', 'F')
print(f"路径: {path}, 距离: {dist}")

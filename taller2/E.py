def solve():
    n, m = map(int, input().split())
    
    edges = []
    for _ in range(m):
        a, b, c = map(int, input().split())
        edges.append((a, b, c))
    
    dist = [0] * (n + 1)
    parent = [-1] * (n + 1)
    
    for i in range(n - 1):
        for a, b, c in edges:
            if dist[a] + c < dist[b]:
                dist[b] = dist[a] + c
                parent[b] = a
    
    cycle_node = -1
    for a, b, c in edges:
        if dist[a] + c < dist[b]:
            dist[b] = dist[a] + c
            parent[b] = a
            cycle_node = b
    
    if cycle_node == -1:
        print("NO")
        return
    
    for _ in range(n):
        cycle_node = parent[cycle_node]
    
    cycle = []
    current = cycle_node
    while True:
        cycle.append(current)
        current = parent[current]
        if current == cycle_node:
            break
    
    cycle.reverse()
    cycle.append(cycle[0])
    print("YES")
    print(" ".join(map(str, cycle)))

solve()

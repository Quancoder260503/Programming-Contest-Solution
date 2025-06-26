n, m = map(int, input().split())
d = [] 
g = []
for i in range(n) : 
    x, y = map(int, input().split())
    g.append(x)
    d.append(y)
adj = [[] for i in range(n)]
for i in range(m): 
   u, v, w = map(int, input().split())
   adj[u - 1].append([v - 1, w])
   adj[v - 1].append([u - 1, w])
   
dp = [[-1 for i in range(1000)] for j in range(n)]
dp[0][0] = g[0]
for i in range(1, 1000): 
    for u in range(n): 
       for [v, w] in adj[u]: 
          if i >= w and dp[v][i - w] != -1: 
              dp[u][i] = max(dp[u][i], dp[v][i - w] + max(0, g[u] - i * d[u])) 
            
ret = -10000000000000
for i in range(1000):
    for j in range(n) : 
        ret = max(ret, dp[j][i])

print(ret)


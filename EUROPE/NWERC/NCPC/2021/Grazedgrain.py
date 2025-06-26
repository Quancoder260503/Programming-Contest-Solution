import random
n = int(input())
dx = []
dy = []
r = []
for i in range(n):
    x, y, z = map(int, input().split())
    dx.append(x)
    dy.append(y)
    r.append(z)
MAXN = 500000
ans = 0
for i in range(MAXN):
    inside = False
    x = random.uniform(-10, 20)
    y = random.uniform(-10, 20)
    for j in range(n):
        if (dx[j] - x)**2 + (dy[j] - y)**2 <= r[j]**2:
            inside = True
            break
    ans += int(inside)
print(float(ans) * 900.0 / MAXN)

x1, y1, x2, y2 = map(int, input().split())
corner = [(0, 0), (0, 2024), (2024, 0), (2024, 2024)]
ret = 2
for p in [(x1, y1), (x2, y2)] : 
  if p in corner : 
    ret = ret - 1
print(ret)   
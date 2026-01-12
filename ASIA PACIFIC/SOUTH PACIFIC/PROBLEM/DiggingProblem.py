from heapq import *
from collections import defaultdict

num_test = int(input()) 
oo = 1 << 30
for _ in range(num_test):
  R, C, f = map(int, input().split()) 
  g = [input() for i in range(R)]
  pq = []
  dp = defaultdict() 
  ret = oo
  cache = [[-1 for i in range(C)] for j in range(R)]
  def goDown(r : int, c : int): 
   if cache[r][c] != -1: 
     return cache[r][c] 
   currRow = r + 1
   while currRow < R and g[currRow][c] == '.' : 
    currRow += 1
   cache[r][c] = currRow - 1
   return currRow - 1 
  for row in range(R): 
    for col in range(C): 
      goDown(row, col)
  def check(c : int, dir : int): 
   if dir < 0 : 
     return c > 0 
   else : 
     return c + 1 < C
 
  heappush(pq, [0, (0, 0, 0, -1, -1)]) 
  while pq: 
    z, u = heappop(pq) 
    if u in dp : 
      continue 
    dp[u] = z 
    x, y, m, tl, tr = u 
    if x == R - 1: 
      if z > ret : 
        break 
      ret = z
      continue 
    if m == 0 : 
      for dir in (-1, 1): 
        if check(y, dir) and (g[x][y + dir] == '.' or ((tl != -1) and (tr != -1) and (tl <= y + dir <= tr))):
          bottom = goDown(x, y + dir) 
          if 0 < bottom - x <= f: 
            heappush(pq, [z, (bottom, y + dir, 0, -1, -1)])
          elif bottom == x : 
            heappush(pq, [z, (x, y + dir, 0, tl, tr)])
            if dir < 0 : 
              heappush(pq, [z + 1, (x, y, dir, y + dir, tr)])
            else :
              heappush(pq, [z + 1, (x, y, dir, tl, y + dir)])  
    else:
        if check(y, -m) and (g[x][y - m] == '.' or ((tl != -1) and (tr != -1) and (tl <= y - m <= tr))) : 
          if g[x + 1][y - m] != '.' : 
            heappush(pq, [z + 1, (x, y - m, m, tl, tr)])  
        bottom = goDown(x + 1, y + m) 
        if bottom - x <= f :
          if bottom - x == 1: 
            if m < 0 :
              heappush(pq, [z, (x + 1, y + m, 0, tl, y + m)])
            else : 
              heappush(pq, [z, (x + 1, y + m, 0, y + m, tr)])
          else: 
              heappush(pq, [z, (bottom, y + m, 0, -1, -1)])
              
    
  print("Case #" + "{:d}".format(_ + 1), end = ': ')
  if ret == oo: 
    print("No")
  else: 
    print("Yes","{:d}".format(ret))  
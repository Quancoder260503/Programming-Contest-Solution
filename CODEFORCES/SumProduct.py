import math
import sys
from collections import Counter
 
def solve():
    n = int(input())
    a = [*map(int, input().split())]
    mp = Counter(map(str,a))
    for i in range(n):
      if a[i] not in mp : 
        mp[a[i]] = 0 
      mp[a[i]] += 1 
      
    q = int(input())
    out = []
 
    for _ in range(q):
        x, y = map(int, input().split())
 
        if x * x < 4 * y:
            print(0, end = ' ')
            continue
 
        disc = int(math.sqrt(x*x - 4*y))
 
        r1 = (x + disc) // 2 
        r2 = (x - disc) // 2
        
        if r1 + r2 != x or r1 * r2 != y : 
          print(0, end = ' ')
          continue 
        
        if r1 == r2:
            cnt = mp.get(r1, 0)
            print(cnt * (cnt - 1) // 2, end = ' ')
        else:
            # Pair (r1, x - r1)
            a = mp.get(r1, 0)
            b = mp.get(x - r1, 0)
            if x == 2 * r1:
                b -= 1
            print(a * b, end = ' ')

    print('') 


T = int(input())
for _ in range(T):
    solve()

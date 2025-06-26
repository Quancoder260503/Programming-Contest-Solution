from collections import defaultdict
import math
 
n, k = map(int, input().split())
 
def rec(aura, num_games, who) :
  if num_games == 0 : 
      return aura 
  if who == 'Alice' :
    ans = 0 
    for x in range(1, n): 
      ans = max(ans, rec((aura * x) % n, num_games - 1, 'Bob'))
    return ans
  else : 
    ans = 1000000
    for x in range(1, n): 
      ans = min(ans, rec((aura * x) % n, num_games - 1, 'Alice')) 
    return ans 
 
def is_prime(x) : 
    for j in range(2, int(math.sqrt(x)) + 1): 
       if x % j == 0: 
           return j 
    return -1 
 
cc = is_prime(n) 
if cc == -1: 
  print(1 if k & 1 else n - 1)    
else :  
  if k >= 3 : 
    print(0) 
  else: 
    if k == 1 : print(1) 
    if k == 2 : print(n * (cc - 1) // cc)
    
    
#print(rec(1, k, 'Bob'))
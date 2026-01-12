import sys
sys.set_int_max_str_digits(1000000)
 
n = int(input())
k = int(input())
pos = [] 
neg = []
for i in range(n) : 
  x = int(input())
  if x > 0 : 
    pos.append(x) 
  elif x < 0: 
    neg.append(x) 
      
 
pos.sort(reverse = True)
neg.sort()
 
ptr = len(pos) - 1
ans = 0 
for i in range(len(pos)): 
 while ptr > i and (pos[i] * pos[ptr]) <= k: 
  ptr = ptr - 1 
 if ptr > i : 
  ans += ptr - i
 
ptr = len(neg) - 1
for i in range(len(neg)): 
 while ptr > i and (neg[i] * neg[ptr])  <= k: 
  ptr = ptr - 1 
 if ptr > i: 
  ans += ptr - i  
 
print(ans)
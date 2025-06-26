test_case = int(input())
for _ in range(test_case): 
  n, m = map(int, input().split())
  m += 1 
  ans = 0
  for b in range(30, -1, -1): 
    if n >= m : 
        break
    if (n & (1 << b)) == (m & (1 << b)): 
       continue
    if m & (1 << b) > 0: 
     ans |= (1 << b) 
     n   |= (1 << b)
  print(ans)          
  
# (n ^ x) = i >= m 
# for all number that has 
#
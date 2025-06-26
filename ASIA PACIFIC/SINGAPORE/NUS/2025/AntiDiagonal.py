'''
def rec(who, grid, i, j, n) :   
 if i + j == n : 
   return grid[i][j] == 'a'
 if who == "A" : 
    ret = 0
    if i + 1 <= n : 
      ret = rec("B", grid, i + 1, j, n)
    if j + 1 <= n : 
      ret = ret or rec("B", grid, i, j + 1, n)
    return ret 
 else : 
    ret = 1
    if i + 1 <= n :  
      ret = rec("A", grid, i + 1, j, n) 
    if j + 1 <= n :   
      ret =ret and rec("A", grid, i, j + 1, n) 
    return ret  
     
n = int(input())
ans = 0
for mask in range(1 << (n + 1)) : 
  grid = [['.' for i in range(n + 1)] for j in range(n + 1)]
  cc = ""
  for i in range(n + 1) : 
    if mask >> i & 1 : 
        grid[i][n - i] = 'a' 
        cc += 'a'
    else : 
        grid[i][n - i] = 'b'
        cc += 'b'
        
  good = rec('A', grid, 0, 0, n)
  if good : 
      ans += 1 
      
print(ans)     
''' 
n = int(input())
MOD = 1000000000 + 3233 
num = (n - 1) // 2 
ret = 1 
for _ in range(num) : 
 ret = ret * 4 % MOD
 
ret = ret * 3 % MOD
print(ret)
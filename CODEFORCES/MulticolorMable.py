n = int(input())
MOD = 1000000007
s = 0 
array = [] 
for i in range(n): 
  array.append(s)
  s = s ^ 1 
dp = [[0 for i in range(2)]] * n
dp[0][0] = 1
for i in range(1, n): 
  dp[i][array[i]] = (dp[i - 1][array[i]] + dp[i - 1][array[i] ^ 1] + 1) % MOD
  dp[i][array[i] ^ 1] = dp[i - 1][array[i] ^ 1]
  
print((dp[n - 1][0] + dp[n - 1][1]) % MOD)
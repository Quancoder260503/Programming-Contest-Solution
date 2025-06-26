n = int(input())
a = []
for i in range(n):
   a.append(int(input()))
a = sorted(a)
ret = 10000000000000
for i in range(n // 2): 
  ret = min(ret, a[i] + a[n - 1 - i])
print(ret)
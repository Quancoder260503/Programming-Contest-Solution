n, k = map(int, input().split())
a = list(map(int, input().split()))
ret = 0 
acc = 0
for i in range(k) : 
   acc += a[i]
ret += acc
for i in range(k, len(a)): 
   acc += a[i] - a[i - k]
   ret += acc
print("{:.7f}".format(ret / (n - k + 1)))
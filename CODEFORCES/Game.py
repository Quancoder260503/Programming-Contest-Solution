n, r = map(int, input().split())
m = pow(2, n)
ws = map(int, input().split())
sum = 0
a = []
for x in ws: 
  a.append(x)
for i in range(m): 
  sum += a[i]
print("{:.7f}".format(sum / m))
for i in range(r): 
  mask, g = map(int, input().split())
  sum = sum - a[mask] + g
  print("{:.7f}".format(sum / m))
  a[mask] = g 


  
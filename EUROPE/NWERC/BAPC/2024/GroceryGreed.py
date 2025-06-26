n = int(input())
a = [round(100 * i) for i in map(float, input().split())]
m = [0] * 5
for c in a : 
  m[c % 5] += 1
k = min(m[3], m[4])
print('%.2f'%((sum(a) - m[1] - 2 * m[2] - 2 * k - (m[3] - k) // 2 - 2 * (((m[4] - k) // 3))) / 100))
import string 

k, n = map(int, input().split())
dp = {}
cc = lambda c : ord(c) - ord('a')

def search(limit, last, freq, curr) : 
  if curr >= k * (k + 1) / 2 : 
    return ""
  for c in string.ascii_lowercase : 
    if c == last : 
      continue 
    freq[cc(c)] += 1
    d = count(limit + 1, c, freq, curr + 1)
    if limit >= d : 
      limit = limit - d 
      freq[cc(c)] -= 1 
    else : 
      return c + search(limit, c, freq, curr + 1)
  return "-1"

def count(limit, last, freq, curr):
  m = sorted(freq)
  if any ((x - y < 26 - k - 1 and x >= 26 - k) or (y > 0 and x < 26 - k) for x, y in enumerate(m)) : 
    return 0
  if curr >= k * (k + 1) / 2 : 
    return 1 
  array = m
  if last != ' ': 
    p = cc(last) 
    array = sorted(freq[:p] + freq[(p + 1):])
  acc = 0 
  for x in array:
    acc = acc * n + x
  if (acc, curr) in dp: 
    return dp[(acc, curr)] 
  total = 0
  for c in string.ascii_lowercase:
    if c == last : 
      continue 
    freq[cc(c)] += 1 
    cnt = min(limit, count(limit, c, freq, curr + 1)) 
    limit = limit - cnt
    freq[cc(c)] -= 1
    total += cnt 
    if limit == 0 : 
      break
  if (acc, curr) not in dp : 
    dp[(acc, curr)] = total 
  return total 
    
print(search(n - 1, ' ', [0 for i in range(26)], 0)) 
    
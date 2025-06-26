n, m, r = map(int, input().split())
s = [(input().count('P'), i + 1 == r) for i in range(n)]
while s: 
    while not (x := s.pop())[0]: 
      if x[1] : 
        exit(print(len(s) + 1))
    s.insert(len(s) - max(0, input().count('y') - 3), (x[0] - 1, x[1]))
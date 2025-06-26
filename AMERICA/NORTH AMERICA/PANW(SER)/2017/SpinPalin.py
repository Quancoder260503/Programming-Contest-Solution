s = input()
n = len(s)
oo = int(100000000000000)
dyn = [[[-1 for i in range(2)] for j in range(2)] for k in range(n)] 

def getFix(a, b, c, d): 
   e = 10 * a + b 
   f = c + d
   return (f > e) * oo or (e - f)

def memo(pos, a1, a2): 
    if pos == n - pos - 1: return min(getFix(a1, i, a2, int(s[pos])) for i in range(10))
    if pos  > n - pos - 1: return (a1 != a2) * oo 
    if dyn[pos][a1][a2] != -1 : return dyn[pos][a1][a2]
    ret = oo 
    for digit in range(10): 
       for need_carry in range(2): 
           curr = int(s[n - pos - 1]) + a2
           ret = min(ret, getFix(a1, digit, need_carry, int(s[pos])) + 
                          (digit < curr) * 10 + digit - curr + memo(pos + 1, need_carry, digit < curr))
    dyn[pos][a1][a2] = ret
    return ret

print(min(memo(0, 1, 0), memo(0, 0, 0)))
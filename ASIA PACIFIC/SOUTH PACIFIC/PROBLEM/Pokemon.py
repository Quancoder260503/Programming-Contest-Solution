def memo(pos, weight, budget, best, Cost, Prob): 
    if pos == 0 and weight == 0: return 1.0
    if pos == 0 : return 0.0
    ret = best[pos][weight]
    if ret >= 0: return ret 
    ret = 0
    acc = 1.0
    for k in range(budget + 1): 
        if weight >= k * Cost[pos] : 
            ret = max(ret, memo(pos - 1, weight - k * Cost[pos], budget, best, Cost, Prob) * (1.0 - acc))
        acc = acc * (1.0 - Prob[pos])
    best[pos][weight] = ret
    return ret

def solve(): 
    budget, n = map(int, input().split())
    if budget == 0 : exit(0)
    Prob = [0.0 for i in range(n + 1)]
    Cost = [0 for i in range(n + 1)]
    for i in range(1, n + 1): 
        val, p = map(str, input().split()) 
        Cost[i] = int(val)
        Prob[i] = float(p)
    best = [[-1.0 for i in range(budget + 1)] for j in range(n + 1)] 
    def memo(pos, weight): 
        if pos == 0 and weight == 0: return 1.0
        if pos == 0 : return 0.0
        ret = best[pos][weight]
        if ret >= 0: return ret 
        ret = 0
        acc = 1.0
        for k in range(budget + 1): 
            if weight >= k * Cost[pos] : 
                ret = max(ret, memo(pos - 1, weight - k * Cost[pos]) * (1.0 - acc))
            else: 
                break
            acc = acc * (1.0 - Prob[pos])
        best[pos][weight] = ret
        return ret
    ret = 0.0 
    ind = 0
    for w in range(budget + 1): 
        opt = memo(n, w)
        if ret < opt: 
           ret, ind = opt, w
    print(ind, "{:.4f}".format(ret))

while True : 
    solve()
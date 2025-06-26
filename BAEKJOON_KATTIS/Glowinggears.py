T = int(input()) 
for i in range(T): 
    n = int(input())
    ret = 0
    idx = 0 
    for _ in range(n): 
        a, b, c = map(float, input().split)
        curr = b * b / (4 * a) + c 
        if curr > ret: 
           ret = curr
           idx = i
    print(idx + 1)
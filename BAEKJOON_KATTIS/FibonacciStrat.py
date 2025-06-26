import math 
T = int(input())
M = 10000
L = 100
fib = [0] * L
fib[0] = 0 
fib[1] = 1
for i in range(2, L): 
    fib[i] = fib[i - 1] + fib[i - 2]
for _ in range(T): 
    n = int(input())
    flag = 0 
    for b in range(1, M): 
        for i in range(3, L):
            if (n - b * fib[i - 1]) % fib[i - 2] == 0:
                a = (n - b * fib[i - 1]) / fib[i - 2]
                if(b >= a and a > 0): 
                   print(int(a), int(b)) 
                   flag = 1
                   break 
        if flag : break 
        

             
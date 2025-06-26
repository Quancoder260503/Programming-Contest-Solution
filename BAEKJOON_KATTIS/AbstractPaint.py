Q = int(input())
mod = 1000000007
for _ in range(Q): 
    R, C = map(int, input().split())
    ret = (2 ** (R * C)) % mod * (3 ** (R + C)) % mod
    print(ret) 
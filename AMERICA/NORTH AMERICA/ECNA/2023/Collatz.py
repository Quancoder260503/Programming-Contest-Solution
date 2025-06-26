s = input()[::-1]
for i in range(4, 100, 2): 
    n = 1 << i
    for ch in s: 
        if ch == 'O': 
            if n % 6 != 4 : 
                n = 0
                break 
            n = n // 3
        else: 
            n = n * 2
    else: 
        print(n)
        break 
else: 
    print("INVALID")      
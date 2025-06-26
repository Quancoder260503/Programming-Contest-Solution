n = input()
s = sum(map(int, input().split()))
acc = 0
while s > 1 : 
    acc += 1
    s = s // 2
print(2 ** acc)

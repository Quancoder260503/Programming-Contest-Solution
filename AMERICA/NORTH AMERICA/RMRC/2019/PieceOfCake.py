n, a, b = map(int, input().split())
print(4 * max(n - a, a) * max(n - b, b))
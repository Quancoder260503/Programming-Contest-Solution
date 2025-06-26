s = input()
print ((ord(s[0]) - ord('0') + 1) * pow(10, len(s) - 1) - int(s))
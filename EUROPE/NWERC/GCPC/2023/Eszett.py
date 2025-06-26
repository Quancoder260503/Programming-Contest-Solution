S = input().lower()
if S.find("sss") != -1: 
    print(S.replace("sss", "sB"))
    print(S.replace("sss", "Bs"))
elif S.find("ss")  != -1:
    print(S.replace("ss", "B"))
print(S)
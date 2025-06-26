A = "KANGAROO"
B = "KIWIBIRD"
S = input()
ctra = ctrb = 0
for ch in S:
    for ch2 in A : if ch == ch2 : ctra += 1
    for ch2 in B : if ch == ch2 : ctrb += 1
if ctra > ctrb: 
    print("Kangaroos")
elif ctra < ctrb: 
    print("Kiwis")
else: 
    print("Feud continues") 

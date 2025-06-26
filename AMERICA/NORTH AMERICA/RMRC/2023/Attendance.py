n = int(input())
s = []
ctr = 0 
for i in range(n): 
    s.append(input())
for i in range(n): 
	if i + 1 < n and s[i + 1] == "Present!" : 
		 i += 1 
	elif s[i] != "Present!": 
		print(s[i]) 
		ctr += 1
if ctr == 0: print("No Absences")
	
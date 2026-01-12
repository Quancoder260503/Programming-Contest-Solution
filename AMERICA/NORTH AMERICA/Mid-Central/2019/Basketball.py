s = input() 
scoreA = 0
scoreB = 0
rule = False
for i in range(0, len(s), 2): 
  if s[i] == 'A' : 
    scoreA += ord(s[i + 1]) - ord('0')
  else : 
    scoreB += ord(s[i + 1]) - ord('0')
  if scoreA == 10 and scoreB == 10 : 
    rule = True
    continue 
  if rule : 
    if scoreA > scoreB + 1 : 
      print("A") 
      exit() 
    if scoreB > scoreA + 1 : 
      print("B") 
      exit()
  else : 
    if scoreA < scoreB and scoreB >= 11 : 
        print("B") 
        exit()
    if scoreA > scoreB and scoreA >= 11 : 
        print("A") 
        exit()
        
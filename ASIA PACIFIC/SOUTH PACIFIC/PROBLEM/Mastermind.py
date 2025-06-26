n = int(input())
Comb = []
def gen_comb():
    _dict = "ABCDEF"
    for a in _dict: 
       for b in _dict: 
           for c in _dict:
               for d in _dict: 
                   words = a + b + c + d
                   Comb.append(words)  

gen_comb()

def check(guess, target, scoreB, scoreW): 
    B = 0
    W = 0
    ctr = [0] * 6
    cnt = [0] * 6
    for i in range(len(guess)): 
      if guess[i] == target[i]: 
        B += 1  
        continue
      ctr[ord(guess[i])  - 65] += 1 
      cnt[ord(target[i]) - 65] += 1 
    for i in range(6): 
        W += min(cnt[i], ctr[i])
    return B == scoreB and W == scoreW

for i in range(n): 
    new_Comb = []
    guess, scoreB, scoreW = map(str, input().split())
    for cand in Comb:
        if check(guess, cand, int(scoreB), int(scoreW)) : 
           new_Comb.append(cand)
    Comb = new_Comb  
    if(len(Comb) == 1): 
        print(Comb[0])
        print(i + 1)
        break
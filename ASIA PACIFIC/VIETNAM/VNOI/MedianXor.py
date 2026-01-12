def solve():
    A, B, C, D = map(int, input().split()) 
    median_ind = ((B - A + 1) * (D - C + 1) + 1) // 2 
    
    max_len = max(A.bit_length(), B.bit_length(), C.bit_length(), D.bit_length())
    dp = [[[[[-1 for i in range(2)] for j in range(2)] for k in range(2)] for p in range(2)] for pp in range(max_len + 1)]
    
    def memo(pos, equalA, equalB, equalC, equalD):
        if pos == -1:
            return 1
        if dp[pos][equalA][equalB][equalC][equalD] != -1: 
            return dp[pos][equalA][equalB][equalC][equalD]
        ret = 0
        for x_bit in range(2):
            for y_bit in range(2):
                if equalB and (x_bit > 0) and ((B >> pos & 1) == 0):
                    continue
                if equalD and (y_bit > 0) and ((D >> pos & 1) == 0):
                    continue
                if equalA and (x_bit == 0) and ((A >> pos & 1) == 1):
                    continue
                if equalC and (y_bit == 0) and ((C >> pos & 1) == 1):
                    continue

                nextEqualA = equalA & (x_bit == (A >> pos & 1))
                nextEqualB = equalB & (x_bit == (B >> pos & 1))
                nextEqualC = equalC & (y_bit == (C >> pos & 1))
                nextEqualD = equalD & (y_bit == (D >> pos & 1))
                
                ret += memo(pos - 1, nextEqualA, nextEqualB, nextEqualC, nextEqualD)
        dp[pos][equalA][equalB][equalC][equalD] = ret
        return ret
    
    states = {(True, True, True, True) : 1}
    ans = 0
    
    def compute(c_bit): 
        state_num = {} 
        ret = 0
        for x_bit in range(2): 
          for y_bit in range(2):
           if c_bit == (x_bit ^ y_bit): 
             for (state, weight) in states.items():  
                equalA, equalB, equalC, equalD = state
                 
                if equalB and (x_bit > 0)  and ((B >> pos & 1) == 0):
                   continue
                if equalD and (y_bit > 0)  and ((D >> pos & 1) == 0):
                   continue
                if equalA and (x_bit == 0) and ((A >> pos & 1) == 1):
                   continue
                if equalC and (y_bit == 0) and ((C >> pos & 1) == 1):
                   continue
          
                nextEqualA = equalA & (x_bit == (A >> pos & 1))
                nextEqualB = equalB & (x_bit == (B >> pos & 1))
                nextEqualC = equalC & (y_bit == (C >> pos & 1))
                nextEqualD = equalD & (y_bit == (D >> pos & 1))
                ret += weight * memo(pos - 1, nextEqualA, nextEqualB, nextEqualC, nextEqualD)
                key = (nextEqualA, nextEqualB, nextEqualC, nextEqualD)
                if key not in state_num: 
                    state_num[key] = weight 
                else : 
                    state_num[key] += weight
                    
        return (ret, state_num) 
    
    for pos in range(max_len - 1, -1, -1):
     ret0, state0 = compute(0) 
     if median_ind <= ret0: 
        states = state0  
     else: 
        ret1, state1 = compute(1)
        median_ind = median_ind - ret0
        ans += (1 << pos)
        states = state1
        
    print(ans)                     

num_test = int(input())
for i in range(num_test):
  solve()
   
   
   
   
   
   
   



'''
Binary Search DP - overflow 

def solve():
    A, B, C, D = map(int, input().split()) 
    def memo(pos, equalA, equalB, equalC, equalD, equalTarget, target, dp):
        if pos == -1:
            return 1
        key = (pos, equalA, equalB, equalC, equalD, equalTarget)
        if key in dp:
            return key
        ret = 0
        for x_bit in range(2):
            for y_bit in range(2):
                c_bit = x_bit ^ y_bit
                if equalTarget and (c_bit > 0) and ((target >> pos & 1) == 0):
                    continue
                if equalB and (x_bit > 0) and ((B >> pos & 1) == 0):
                    continue
                if equalD and (y_bit > 0) and ((D >> pos & 1) == 0):
                    continue
                if equalA and (x_bit == 0) and ((A >> pos & 1) == 1):
                    continue
                if equalC and (y_bit == 0) and ((C >> pos & 1) == 1):
                    continue

                nextEqualA = equalA & (x_bit == (A >> pos & 1))
                nextEqualB = equalB & (x_bit == (B >> pos & 1))
                nextEqualC = equalC & (y_bit == (C >> pos & 1))
                nextEqualD = equalD & (y_bit == (D >> pos & 1))
                nextEqualTarget = equalTarget & (c_bit == (target >> pos & 1))
                ret += memo(pos - 1, nextEqualA, nextEqualB, nextEqualC, nextEqualD, nextEqualTarget, target, dp)

        dp[key] = ret
        return ret
    
    median_ind = (B - A + 1) * (D - C + 1) / 2 
    def check(x) : 
      dp = {}
      ans = memo(x.bit_length(), True, True, True, True, True, x, dp)
      return ans >= median_ind
  
    lo = 0
    hi = (1 << 200)
    while lo < hi : 
      mid = (lo + hi) // 2 
      if check(mid) : 
        hi = mid 
      else : 
        lo = mid + 1 
    print(lo)  

num_test = int(input())
for i in range(num_test):
   solve()

'''

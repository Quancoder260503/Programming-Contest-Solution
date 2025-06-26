import math 
n, w = map(int, input().split())
ret = 0.0
_Prob = 1.0
last_safe = 0.0
acc = 0.0
for i in range(n): 
   type, Prob, val = map(str, input().split())
   cost = math.log(1 + float(val) / w)
   acc += _Prob * (1 - float(Prob)) * last_safe
   ret = max(ret, acc + float(Prob) * _Prob * cost)
   _Prob = _Prob * float(Prob)
   if type == "safe": last_safe = cost
   
print("${:.2f}".format((math.exp(ret) - 1) * w))       
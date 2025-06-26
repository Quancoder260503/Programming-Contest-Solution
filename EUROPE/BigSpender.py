S   = int(input(), base = 2)
D   = int(input(), base = 2) 
M   = int(input(), base = 2) 

num_day = 0
while M.bit_length() >= D : 
  M_prev = M 
  M = M >> D 
  M += S 
  num_day += D 
  if M_prev <= M : 
    print("Infinite money!")
    exit()

num_day += M.bit_length() 
print(bin(num_day)[2:])
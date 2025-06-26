#include "bits/stdc++.h"

using namespace std;

#define int64_t long long

const int64_t oo = LLONG_MAX / 1000; 

const int LOG = 17;  
int64_t dyn[1 << LOG][LOG], cost[1 << LOG];  
int N, K; 

int64_t memo(int mask, int envelope) { 
   if(mask == 0)      return 0; 
   if(envelope == 0)  return oo;  
   int64_t &ret = dyn[mask][envelope]; 
   if(ret != -1) return ret; 
   ret = oo; 
   for(int smask = mask; ; smask = (smask - 1) & mask) { 
    ret = min(ret, cost[mask ^ smask] + memo(smask, envelope - 1));
    if(smask == 0) break;  
   }
   return ret; 
}

int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0);
  memset(dyn, -1, sizeof(dyn)); 
  cin >> N >> K; 
  vector<int>x(N), y(N), q(N); 
  for(int i = 0; i < N; i++) { 
    cin >> x[i] >> y[i] >> q[i]; 
  }
  for(int mask = 0; mask < (1 << N); mask++) { 
    int max_x = 0, max_y = 0; 
    for(int i = 0; i < N; i++) if(mask & (1 << i)) { 
      max_x = max(max_x, x[i]); 
      max_y = max(max_y, y[i]); 
    }
    for(int i = 0; i < N; i++) if(mask & (1 << i)) { 
      cost[mask] += 1LL * q[i] * (1LL * max_x * max_y - 1LL * x[i] * y[i]); 
    }
  }
  cout << memo((1 << N) - 1, K) << '\n'; 
  return 0; 
}

/*
  If we have a set of cards (x1, y1), (x2, y2), (x3, y3), ...., (xn, yn) we can greedily, choose the envelope of 
  size (max(x[i]), max(y[i])); 
  Then use sub-mask dynamic programming to solve the problem with f(i, mask) being the minimum waste using i-th envelopes 
  with mask represented the cards has been filled or not ? 
*/ 
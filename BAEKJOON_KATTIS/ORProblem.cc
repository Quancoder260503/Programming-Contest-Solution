#include "bits/stdc++.h"

using namespace std; 

const int mod = 1e9 + 7; 
const int maxf = 1e6 + 1; 
const int LOG = 20; 

int64_t fact[maxf], ifact[maxf]; 

int64_t Comb(int a, int b) {
  if (a == b) return 1;
  if (a < b || b < 0) return 0;
  return fact[a] % mod * ifact[b] % mod * ifact[a - b] % mod;
}

int64_t fpow(int64_t a, int64_t k) {
  if (!k) return 1;
  int64_t res = a, tmp = a;
  k--;
  while (k) {
    if (k & 1) {
      res = (int64_t)res % mod * tmp % mod;
    }
    tmp = (int64_t)tmp % mod * tmp % mod;
    k >>= 1;
  }
  return res;
}

void init(void) {
  fact[0] = ifact[0] = 1;
  for (int i = 1; i < maxf; i++) {
    fact[i] = fact[i - 1] % mod * i % mod;
    ifact[i] = ifact[i - 1] % mod * fpow(i, mod - 2) % mod;
  }
  return;
}

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  init(); 
  int N, K, L, R; 
  cin >> N >> K >> L >> R;
  vector<int>a(N); 
  vector<int64_t>ways(maxf); 
  for(int i = 0; i < N; i++) { 
    cin >> a[i]; 
    ways[a[i]]++; 
  } 
  for(int i = 0; i < LOG; i++) { 
    for(int mask = 0; mask < maxf; mask++) { 
      if(mask & (1 << i)) { 
        ways[mask] += ways[mask ^ (1 << i)];    
      }
    }
  }
  for(int i = 0; i < maxf; i++) { 
    ways[i] = Comb(ways[i], K);  
  } 
  for(int i = 0; i < LOG; i++) { 
    for(int mask = 0; mask < maxf; mask++) { 
      if(mask & (1 << i)) { 
       (ways[mask] += mod - ways[mask ^ (1 << i)]) %= mod; 
      }
    }
  }
  int64_t ret = 0; 
  for(int i = L; i <= R; i++) { 
    if(i % 3 == 0) { 
      (ret += ways[i]) %= mod; 
    }
  }
  cout << ret << '\n'; 
  return 0; 
}
/*
  nums[x] = number of elements needed to 

*/

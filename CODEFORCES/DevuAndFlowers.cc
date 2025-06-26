#include "bits/stdc++.h"

using namespace std; 

const int MOD = 1e9 + 7;

#define int64_t long long
#define sz(x) int(x.size())

int64_t mod_pow(int64_t a, int64_t b, int64_t p) {
  int64_t res = 1;
  while (b > 0) {
    if (b & 1) res = (res * a) % p;
    a = (a * a) % p;
    b >>= 1;
  }
  return res;
}

int64_t mod_inv(int64_t a, int64_t p) { return mod_pow(a % p, p - 2, p); }

int64_t ifact; 

int64_t Comb(int64_t N, int K) { 
  static unordered_map<int64_t, int64_t>comb;
  if(N < K || K < 0) return 0;
  if(comb.count(N)) return comb[N];   
  int64_t ret = 1; 
  for(int64_t x = N - K + 1; x <= N; x++) { 
   ret = 1LL * x % MOD * ret % MOD; 
  }
  ret = ret % MOD * ifact % MOD; 
  return comb[N] = ret; 
}

int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int64_t S; 
  int N; 
  cin >> N >> S; 
  vector<int64_t>a(N); 
  ifact = 1; 
  for(int i = 0; i < N; i++) { 
   cin >> a[i]; 
  }
  for(int i = 1; i < N; i++) { 
   ifact = ifact % MOD * i % MOD; 
  }
  ifact = mod_inv(ifact, MOD); 
  vector<int64_t>dp(1 << N); 
  /* 
  for(int mask = (1 << N) - 1; mask >= 0; mask--) { 
   int64_t sum = 0; 
   for(int i = 0; i < N; i++) { 
    if(mask & (1 << i)) {
     sum += a[i]; 
    } else { 
     (dp[mask] += MOD - dp[mask | (1 << i)]) %= MOD; 
    }
   }
   (dp[mask] += Comb(S - sum - 1, N - 1)) %= MOD; 
  }
  */  
  for(int mask = 0; mask < (1 << N); mask++) { 
   int64_t sum = 0; 
   for(int i = 0; i < N; i++) { 
    if(mask & (1 << i)) continue; 
    sum += (a[i] + 1); 
   }
   dp[mask] = Comb(S - sum + N - 1, N - 1); 
  }
  for(int i = 0; i < N; i++) { 
   for(int mask = 0; mask < (1 << N); mask++) { 
    if(mask & (1 << i)) { 
     (dp[mask] += MOD - dp[mask ^ (1 << i)]) %= MOD; 
    }
   }
  }
  cout << dp[(1 << N) - 1] << '\n'; 
  return 0; 
}
/*
 * dp[mask] = {ways to distribute candies such that mask i-th on if num candies 
              chosen from the ith bags exceed its max}; 
 * x[1] + x[2] + ... + x[n] = s - a[1] - a[2] - ... - a[n]
   Comb(s - a[2] - ... - a[n] - 1, n - 1) - Comb(s - a[1] - ... - a[n] - 1, n - 1)
*/ 
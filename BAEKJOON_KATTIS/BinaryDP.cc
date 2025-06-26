#include "bits/stdc++.h"

using namespace std; 

const int MOD = 1e9 + 7; 
const int maxf = 1e6 + 2; 

int64_t pw2[maxf], fact[maxf], ifact[maxf]; 

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

void solve() {    
  int N, M; 
  cin >> N >> M; 
  vector<vector<vector<int64_t>>>dp(N + 1, vector<vector<int64_t>>(M + 1, vector<int64_t>(N + 1))); 
  dp[0][0][0] = 1;
  for(int pos = 0; pos < N; pos++) { 
   for(int amt = 0; amt <= M; amt++) { 
    for(int _size = 0; _size <= N; _size++) {      
     (dp[pos + 1][amt][_size] += dp[pos][amt][_size]) %= MOD; 
     if(_size < N) { 
      for(int take = 1; take <= amt; take++) { 
        (dp[pos + 1][amt][_size + 1] += pw2[take * pos] % MOD * dp[pos][amt - take][_size] % MOD * 
                                        ifact[take] % MOD) %= MOD; 
      }   
     }
    }
   }
  }
  auto Comb = [&](int n, int k) -> int64_t { 
    if(n < k) return 0; 
    return fact[n] % MOD * ifact[n - k] % MOD * ifact[k] % MOD; 
  };
  int64_t ret = 0;  
  for(int takeAmt = 1; takeAmt <= N; takeAmt++) { 
    int64_t ways = dp[N][M][takeAmt] % MOD * fact[M] % MOD;
    for(int j = (takeAmt % 2 == 0); j <= N - takeAmt; j += 2) {
     (ret += Comb(N - takeAmt, j) * ways % MOD) %= MOD;
    } 
  }
  cout << ret << '\n'; 
  return; 
}

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0);
  int T;
  pw2[0] = fact[0] = ifact[0] = 1; 
  for(int j = 1; j < maxf; j++) { 
    pw2[j] = pw2[j - 1] * 2 % MOD; 
    fact[j] = fact[j - 1] * j % MOD; 
    ifact[j] = mod_inv(fact[j], MOD); 
  }
  for(cin >> T; T--; ) { 
    solve(); 
  }
  return 0; 
}
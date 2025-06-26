#include "bits/stdc++.h"

using namespace std;

#define int64_t long long
#define sz(x) int(x.size()) 

int64_t fpow(int64_t a, int64_t k, int64_t mod) {
  if (!k) return 1;
  int64_t res = a, tmp = a;
  k--;
  while (k) {
    if (k & 1) {
      res = 1LL * res % mod * tmp % mod;
    }
    tmp = 1LL * tmp % mod * tmp % mod;
    k >>= 1;
  }
  return res;
}

vector<int>mod_primes = {1000000007, 998244353, 167772161, 469762049, 330402221, 179753603, 379019161, 
                          730775519, 860934721, 445881679, 455974231
};

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int N, Q;
  string S;
  cin >> Q;
  for (int iter = 0; iter < Q; iter++) {
    cin >> S;
    N = sz(S);
    vector<vector<int64_t>> range(N, vector<int64_t>(N));
    for (int i = 0; i < N; i++) {
      if (S[i] == '0') continue;
      vector<int64_t>cc(sz(mod_primes)); 
      for (int j = i; j < N; j++) {
        range[i][j] = true; 
        for(int k = 0; k < sz(mod_primes); k++) { 
          cc[k] = (10 % mod_primes[k] * cc[k] % mod_primes[k] + S[j] - '0') % mod_primes[k]; 
          range[i][j] &= (fpow(cc[k], (mod_primes[k] - 1) / 2, mod_primes[k]) == 1); 
        } 
       // cout << i << " " << j << " " << range[i][j] << '\n'; 
      }
    }
    vector<int64_t> dyn(N + 1);
    dyn[0] = 1; 
    for(int i = 1; i <= N; i++) { 
      if(S[i - 1] == '0') continue; 
      for(int j = i; j <= N; j++) if(range[i - 1][j - 1]) { 
        dyn[j] += dyn[i - 1]; 
      }
    }
    cout << dyn[N] << '\n'; 
  }
  return 0;
}
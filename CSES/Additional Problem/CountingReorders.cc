#include "bits/stdc++.h"
 
using namespace std;
 
#define sz(x) int(x.size())
 
const int MOD = 1e9 + 7;
const int ALPHA = 26; 

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
 
int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  string S;
  cin >> S;
  int N = sz(S);
  vector<int>freq(ALPHA); 
  for (int i = 0; i < N; i++) {
    freq[S[i] - 'a']++;
  }
  vector<vector<int64_t>>Comb(N + 1, vector<int64_t>(N + 1)); 
  vector<int64_t>fact(N + 1), ifact(N + 1); 
  Comb[0][0] = fact[0] = ifact[0] = 1;
  for (int i = 1; i <= N; i++) {
    for (int j = 0; j <= i; j++) {
      Comb[i][j] = (Comb[i - 1][j] + (j > 0 ? Comb[i - 1][j - 1] : 0)) % MOD;
    }
    fact[i] = fact[i - 1] * i % MOD; 
    ifact[i] = mod_inv(fact[i], MOD); 
  }
  vector<int>c; 
  for(int i = 0; i < ALPHA; i++) { 
    if(freq[i] > 0) { 
      c.push_back(i); 
    }
  }
  vector<vector<int64_t>> dp(sz(c) + 1, vector<int64_t>(N + 1)); 
  dp[0][0] = 1;
  int sum = 0; 
  for(int i = 0; i < sz(c); i++) { 
    vector<int64_t> ways(freq[c[i]] + 1); 
    for(int j = 1; j <= freq[c[i]]; j++) { 
      ways[j] = Comb[freq[c[i]] - 1][j - 1] % MOD * 
               (freq[c[i]] - j & 1 ? MOD - 1 : 1) % MOD * 
               ifact[j] % MOD ;
    } 
    for(int j = 0; j <= freq[c[i]]; j++) { 
      for(int k = 0; k <= sum; k++) { 
        (dp[i + 1][j + k] += ways[j] % MOD * dp[i][k] % MOD) %= MOD; 
      }
    }
    sum += freq[c[i]]; 
  } 
  int64_t ret = 0; 
  for(int i = 0; i <= N; i++) { 
    (ret += dp[sz(c)][i] * fact[i] % MOD) %= MOD; 
  }
  cout << ret << '\n'; 
  return 0;
}
// dp[i][j] = {number of ways to divide the first ith numbers into intervals}
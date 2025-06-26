#include <bits/stdc++.h> 

using namespace std; 

#define sz(x) int(x.size())

#define sz(x) int(x.size())

const int MOD  = 998244353;
const int maxf = 2e6 + 10;

int64_t fact[maxf], ifact[maxf], fib[maxf];

int64_t Comb(int a, int b) {
  if (a == b) return 1;
  if (a < b || b < 0) return 0;
  return fact[a] % MOD * ifact[b] % MOD * ifact[a - b] % MOD;
}

int64_t fpow(int64_t a, int64_t k) {
  if (!k) return 1;
  int64_t res = a, tmp = a;
  k--;
  while (k) {
    if (k & 1) {
      res = (int64_t)res % MOD * tmp % MOD;
    }
    tmp = (int64_t)tmp % MOD * tmp % MOD;
    k >>= 1;
  }
  return res;
}

void init(void) {
  fact[0] = ifact[0] = 1;
  for (int i = 1; i < maxf; i++) {
   fact[i] = fact[i - 1] % MOD * i % MOD;
   ifact[i] = ifact[i - 1] % MOD * fpow(i, MOD - 2) % MOD;
  }
  return;
}

int main() { 
 int N, T; 
 init(); 
 for(cin >> T; T--; ) { 
  cin >> N; 
  vector<int>a(N); 
  vector<pair<int, int>>freq;
  for(int i = 0; i < N; i++) { 
   cin >> a[i]; 
  }
  for(int i = 0; i < N; i++) { 
   int c = 0; 
   while(c + i < N && a[i] == a[c + i]) { 
    c++; 
   } 
   freq.push_back({a[i], c}); 
   i = i + c - 1; 
  } 
  int M = sz(freq); 
  vector<vector<int64_t>>dp(N + 1, vector<int64_t>(N / 2 + 1));
  sort(freq.rbegin(), freq.rend()); 
  if(freq[0].second > 1) {
    cout << 0 << '\n'; 
    goto done; 
  } 
  dp[1][1] = 1; 
  for(int i = 1, acc = 1; i < M; i++) { 
   for(int even = 0; even <= min(N / 2, acc); even++) { 
    int spots = max(0, max(0, even - 1 + (even == N / 2)) - (acc - even));
    if(even < N / 2) { 
     (dp[acc + freq[i].second][even + 1] += dp[acc][even] % MOD * Comb(spots, freq[i].second - 1) % MOD) %= MOD; 
    }
    (dp[acc + freq[i].second][even] += dp[acc][even] % MOD * Comb(spots, freq[i].second) % MOD ) %= MOD; 
   }
   acc += freq[i].second; 
  }
  cout << dp[N][N / 2] << '\n'; 
 done:;
 } 
 return 0;
}

/*
 * dp[even][odd] = ways to fill the array with even-th position being filled and odd among (even - 1) gaps has been filled 
*/
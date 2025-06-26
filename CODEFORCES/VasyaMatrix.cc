#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

const int MOD = 998244353; 

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

int main(void) {
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 int N, M; 
 cin >> N >> M; 
 vector<array<int, 3>>g; 
 for(int i = 0; i < N; i++) { 
  for(int j = 0, x; j < M; j++) { 
   cin >> x; 
   g.push_back({x, i, j}); 
  }
 }
 sort(g.begin(), g.end()); 
 pair<int, int>start; 
 int st = 0; 
 cin >> start.first >> start.second;
 --start.first, --start.second; 
 int64_t sumX = 0, sumY = 0, sumSquareX = 0, sumSquareY = 0, sum = 0; 
 vector<vector<int64_t>>dp(N, vector<int64_t>(M)); 
 for(int pos = 0; pos < N * M; pos++) {
  int j = pos + 1; 
  while(j < N * M && g[pos][0] == g[j][0]) {j++; }
  if(pos > 0) {
   int64_t den = mod_inv(pos, MOD); 
   for(int i = pos; i < j; i++) { 
    int64_t currX = (1LL * pos % MOD * g[i][1] % MOD * g[i][1] % MOD - 2LL * sumX % MOD * g[i][1] % MOD + sumSquareX + MOD) % MOD;
    int64_t currY = (1LL * pos % MOD * g[i][2] % MOD * g[i][2] % MOD - 2LL * sumY % MOD * g[i][2] % MOD + sumSquareY + MOD) % MOD;
    dp[g[i][1]][g[i][2]] = (currX + currY + sum) % MOD * den % MOD ; 
   }
  }
  for(int i = pos; i < j; i++) { 
   (sum += dp[g[i][1]][g[i][2]]) %= MOD; 
   (sumSquareX += g[i][1] % MOD * g[i][1] % MOD) %= MOD; 
   (sumX += g[i][1]) %= MOD; 
   (sumSquareY += g[i][2] % MOD * g[i][2] % MOD) %= MOD; 
   (sumY += g[i][2]) %= MOD; 
  }
  pos = j - 1;  
 }
 cout << dp[start.first][start.second] << '\n'; 
 return 0; 
}

/**
 * 
 * 
 */

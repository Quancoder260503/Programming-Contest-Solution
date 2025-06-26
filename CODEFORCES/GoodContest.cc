#include "bits/stdc++.h"
 
using namespace std; 
 
const int MOD = 998244353; 

#define int64_t long long
#define sz(x) int(x.size())

const int maxf = 200; 

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

int64_t dp[maxf][maxf], ways[maxf][maxf], fact[maxf], ifact[maxf];

int main(void) { 
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0);
 fact[0] = ifact[0] = 1; 
 for(int i = 1; i < maxf; i++) { 
  fact[i] = fact[i - 1] % MOD * i % MOD; 
  ifact[i] = mod_inv(fact[i], MOD); 
 }
 int N; 
 cin >> N; 
 vector<int>L(N), R(N);
 vector<int>coord;  
 for(int i = N - 1; i >= 0; i--) { 
  cin >> L[i] >> R[i];
  R[i]++; 
  coord.push_back(L[i]); 
  coord.push_back(R[i]);  
 } 
 sort(coord.begin(), coord.end()); 
 coord.erase(unique(coord.begin(), coord.end()), coord.end());
 for(int interval = 0; interval + 1 < sz(coord); interval++) { 
  vector<vector<int64_t>>memo(N + 1, vector<int64_t>(N + 1, -1)); 
  int rangeLen = coord[interval + 1] - coord[interval]; 
  function<int64_t(int, int)> func = [&](int num, int distinct) -> int64_t { 
   if(distinct > rangeLen || distinct < 0) return 0; 
   if(num == 0) return (distinct == 0);  
   int64_t &ret = memo[num][distinct]; 
   if(ret != -1) return ret; 
   ret = 0; 
   for(int choose = 1; choose <= num; choose++) { 
    (ret += func(num - choose, distinct - 1) % MOD * (rangeLen - distinct + 1) % MOD) %= MOD; 
   }
   return ret; 
  }; 
  for(int num = 1; num <= N; num++) { 
   for(int distinct = 1; distinct <= num; distinct++) { 
   int64_t cc = func(num, distinct);
    (ways[interval][num] += cc % MOD * ifact[distinct] % MOD) %= MOD; 
   } 
  }  
 }
 memset(dp, -1, sizeof(dp)); 
 function<int64_t(int, int)> F = [&](int pos, int interval) -> int64_t { 
  if(pos == N) return interval <= sz(coord); 
  if(interval >= sz(coord)) return 0; 
  int64_t &ret = dp[pos][interval]; 
  if(ret != -1) return ret; 
  ret = F(pos, interval + 1); 
  for(int curr = pos; curr < N; curr++) { 
   if(L[curr] <= coord[interval] && coord[interval + 1] <= R[curr]) { 
    (ret += ways[interval][curr - pos + 1] % MOD * F(curr + 1, interval + 1) % MOD) %= MOD; 
   } else { 
    break; 
   }
  }
  return ret; 
 }; 
 int64_t den = 1; 
 for(int i = 0; i < N; i++) {   
  den = den % MOD * (R[i] - L[i]) % MOD; 
 }
 int64_t ret = F(0, 0) % MOD * mod_inv(den, MOD) % MOD; 
 cout << ret << '\n'; 
 return 0; 
}
/**
 * ways[i][num][d] ways to select num numbers in the range ith such 
 * that there are d distinct numbers
   [L, R)
   ways[i][num][d + 1] = ways[i][num - k][d] * (R[i] - L[i] + 1 - d) 
  1 1 1 
  2 2 2 
  1 2 2 
  

 */
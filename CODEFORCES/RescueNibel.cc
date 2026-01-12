#include "bits/stdc++.h" 

using namespace std; 

#define sz(x) int(x.size())

const int MOD = 998244353; 

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
  int n, k; 
  cin >> n >> k; 
  vector<int64_t>fact(2 * n + 1), ifact(2 * n + 1); 
  fact[0] = ifact[0] = 1; 
  for(int i = 1; i <= 2 * n; i++) { 
   fact[i] = fact[i - 1] * i % MOD; 
   ifact[i] = mod_inv(fact[i], MOD); 
  }
  auto Comb = [&](int n, int k) -> int64_t { 
   if(n < k || k < 0) return 0; 
   return fact[n] % MOD * ifact[k] % MOD * ifact[n - k] % MOD; 
  }; 
  vector<int>l(n), r(n); 
  vector<pair<int, int>>vec; 
  for(int i = 0; i < n; i++) { 
   cin >> l[i] >> r[i]; 
   vec.push_back({l[i], i + 1}); 
   vec.push_back({r[i] + 1, -(i + 1)}); 
  }
  sort(vec.begin(), vec.end()); 
  set<int>ms; 
  int64_t ans = 0; 
  for(auto [x, ind] : vec) { 
   if(ind < 0) { 
    ms.erase(-ind); 
    //cout << sz(ms) << " " << k << " " << ind << '\n'; 
   } else { 
    ms.insert(ind); 
    ans += Comb(sz(ms) - 1, k - 1); 
    ans %= MOD; 
  //  cout << ans << " " << sz(ms) << " " << k << " " << ind << '\n'; 
   }
  }
  cout << ans << '\n'; 
  return 0;   
}

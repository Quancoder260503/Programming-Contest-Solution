#include "bits/stdc++.h"
 
using namespace std; 
 
#define int64_t long long
#define sz(x) int(x.size())
 
const int MOD = 235813;
 
class Moonson { 
 public :
  void solve() { 
  int N; 
  cin >> N; 
  vector<int>a(N); 
  for(int i = 0; i < N; i++) { 
   cin >> a[i]; 
  }
  vector<int64_t>fact(N + 1, 1), ifact(N + 1, 1); 
  fact[0] = ifact[0] = 1; 
  for(int i = 1; i < sz(fact); i++) { 
   fact[i] = fact[i - 1] % MOD * i % MOD; 
   ifact[i] = mod_inv(fact[i], MOD);
  }
  auto Comb = [&](int n, int k) -> int64_t { 
   if(n < k || k < 0) return 0; 
   return fact[n] % MOD * ifact[n - k] % MOD * ifact[k] % MOD; 
  }; 
  vector<int64_t>prefix(N, 0), suffix(N, 0);  
  for(int i = 0; i < N; i++) { 
   prefix[i] = a[i] % MOD * Comb(N - 1, i) % MOD * ((N - 1 - i) & 1 ? -1 : 1) + MOD; 
   (prefix[i] += (i ? prefix[i - 1] : 0)) %= MOD; 
  }
  for(int i = N - 1; i >= 0; i--) { 
   suffix[i] = a[i] % MOD * Comb(N - 1, i) % MOD * ((N - 1 - i) & 1 ? -1 : 1) + MOD; 
   (suffix[i] += (i + 1 < N ? suffix[i + 1] : 0)) %= MOD; 
  }
  int ans = 0; 
  for(int i = 0; i < N; i++) { 
   int64_t rem = 0, coef = (Comb(N - 1, i) % MOD * ((N - 1 - i) & 1 ? -1 : 1) + MOD) % MOD; 
   if(i)         rem += prefix[i - 1]; 
   if(i + 1 < N) rem += suffix[i + 1]; 
   rem = (MOD - rem % MOD) % MOD; 
   rem = rem % MOD * mod_inv(coef, MOD) % MOD; 
   a[i] = (MOD + a[i]) % MOD; 
   if(rem != a[i]) { 
    if(rem <= 100000) ans++; 
    else { 
     if(rem >= MOD - 100000) ans++; 
    }
   }
  }
  cout << ans << '\n'; 
  return;  
 } 
 private : 
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
}; 
 
int main(void) { 
  Moonson task; 
  task.solve(); 
  return 0; 
}
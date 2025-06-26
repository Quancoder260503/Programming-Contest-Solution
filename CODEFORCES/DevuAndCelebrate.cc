#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

const int MOD = 1e9 + 7;
const int maxf = 2e6 + 10;

int64_t fact[maxf], ifact[maxf];

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


int64_t Comb(int a, int b) {
  if(a == b) return 1;
  if (a < b || b < 0) return 0;
  return fact[a] % MOD * ifact[b] % MOD * ifact[a - b] % MOD;
}

void init(void) {
  fact[0] = ifact[0] = 1;
  for (int i = 1; i < maxf; i++) {
    fact[i] = fact[i - 1] % MOD * i % MOD;
    ifact[i] = mod_inv(fact[i], MOD); 
  }
  return;
}

template <int N>
struct MultiplicativeFunction {
  MultiplicativeFunction() {
    // Init sieve
    for (int i = 2; i * i < N; i++) {
      if (!sieve[i]) {
        for (int j = i * i; j < N; j += i) {
          sieve[j] = i;
        }
      }
    }
    for (int i = 2; i < N; i++) {
      if (!sieve[i]) {
        pk[i] = {i, 1};
      } else {
        int p = sieve[i];

        if (pk[i / p].first == p) {  // i = p^k
          pk[i] = {p, pk[i / p].second + 1};
        } else {
          pk[i] = {-1, 0};
        }
      }
    }
  }
  array<int, N> divisors() {
    array<int, N> res;
    res[1] = 1;

    for (int i = 2; i < N; i++) {
      if (pk[i].first > 0) {  // i = p^k
        res[i] = pk[i].second + 1;
      } else {
        // i = u * v, gcd(u, v) = 1
        int u = i, v = 1;
        int p = sieve[i];
        while (u % p == 0) {
          u /= p;
          v *= p;
        }
        res[i] = res[u] * res[v];
      }
    }

    return res;
  }
  array<int, N> mobius() {
    array<int, N> res;
    res[1] = 1;

    for (int i = 2; i < N; ++i) {
      if (pk[i].first > 0) {  // i = p^k
        res[i] = (pk[i].second >= 2) ? 0 : -1;
      } else {
        // i = u * v, gcd(u, v) = 1
        int u = i, v = 1;
        int p = sieve[i];
        while (u % p == 0) {
          u /= p;
          v *= p;
        }
        res[i] = res[u] * res[v];
      }
    }
    return res;
  }
  array<int, N> sieve = {0};
  array<pair<int, int>, N> pk;
};

MultiplicativeFunction<200001>phi; 

int main(void) {  
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0);
 int T; 
 init(); 
 auto mobius = phi.mobius(); 
 vector<vector<int>>d(200001); 
 for(int i = 1; i < 200001; i++) { 
  for(int j = i; j < 200001; j += i) { 
   d[j].push_back(i); 
  }
 }
 for(cin >> T; T--; ) {
  int N, F; 
  cin >> N >> F; 
  int64_t ret = 0; 
  for(auto &x : d[N]) { 
  (ret += MOD + mobius[x] * Comb(N / x - 1, F - 1)) %= MOD; 
  }
  cout << ret << '\n'; 
 }
 return 0;
}

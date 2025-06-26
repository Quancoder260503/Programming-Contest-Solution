#include <bits/stdc++.h> 

using namespace std; 

#define sz(x) int(x.size())

const int mod = 998244353;
const int maxf = 2e6 + 10;

int64_t fact[maxf], ifact[maxf], fib[maxf];

int64_t Comb(int a, int b) {
  if (a == b) return 1;
  if (a < b || b < 0) return 0;
  return fact[a] % mod * ifact[b] % mod * ifact[a - b] % mod;
}

int64_t fpow(int64_t a, int64_t k) { 
  if (!k) return 1;
  int64_t res = a, tmp = a;
  k--;
  while (k) {
    if (k & 1) {
      res = (int64_t)res % mod * tmp % mod;
    }
    tmp = (int64_t)tmp % mod * tmp % mod;
    k >>= 1;
  }
  return res;
}

void init(void) {
  fact[0] = ifact[0] = 1;
  for (int i = 1; i < maxf; i++) {
    fact[i] = fact[i - 1] % mod * i % mod;
    ifact[i] = ifact[i - 1] % mod * fpow(i, mod - 2) % mod;
  }
  return;
}

int main() {
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0);
 init(); 
 int N; 
 int64_t K; 
 cin >> N >> K; 
 if(N <= K) { 
  cout << 0 << '\n'; 
  return 0; 
 } 
 int64_t ret = 0; 
 for(int i = 0; i <= N - K; i++) { 
  (ret += mod + (i & 1 ? -1 : 1) * fpow(N - K - i, N) % mod * Comb(N - K, i) % mod * ifact[N - K] % mod) %= mod; 
 } 
 ret = ret % mod * fact[N - K] % mod * Comb(N, N - K) % mod;
 if(K > 0) ret = ret * 2 % mod; 
 cout << ret << '\n'; 
 return 0; 
}
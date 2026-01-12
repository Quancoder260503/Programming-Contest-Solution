#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())
#define int64_t long long 

const int maxn = 4e6 + 10; 

pair<int64_t, int64_t> bezout(int64_t a, int64_t b) {
 if (!a) return {0, 1};
 auto [x, y] = bezout(b % a, a);
 return {y - (b / a) * x, x};
}

pair<int64_t, int64_t> chinese_remainder_theorem(int64_t a, int64_t n, int64_t b, int64_t m) {
 int64_t g = gcd(n, m);
 if ((b - a) % g) return {0, -1};
 if (m > n) {
  swap(a, b);
  swap(n, m);
 }
 a %= n;
 b %= m;
 int64_t lcm = n / g * m;
 n /= g;
 m /= g;
 auto [x, y] = bezout(n, m);
 int64_t r = ((__int128) a * m * y + (__int128) b * n * x) % lcm;
 if (r < 0) r += lcm;
 return {r, lcm};
}

int64_t Comb(int64_t n, int64_t k, vector<int64_t>&fact, vector<int64_t>&ifact, int p) { 
 if(n < k || k < 0) return 0; 
 if(n >= p || k >= p) return Comb(n / p, k / p, fact, ifact, p) % p * Comb(n % p, k % p, fact, ifact, p) % p;
 return fact[n] % p * ifact[n - k] % p * ifact[k] % p;   
}

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
 vector<int>prime = {3, 11, 101, 3000301}; 
 vector<vector<int64_t>>fact(sz(prime), vector<int64_t>(maxn)); 
 vector<vector<int64_t>>ifact(sz(prime), vector<int64_t>(maxn)); 
 for(int i = 0; i < sz(prime); i++) { 
  fact[i][0] = ifact[i][0] = 1;  
  for(int j = 1; j < sz(fact[i]); j++) { 
    fact[i][j] = fact[i][j - 1] % prime[i] * j % prime[i]; 
    ifact[i][j] = mod_inv(fact[i][j], prime[i]); 
  }
 }
 int64_t N, K, C; 
 int T; 
 for(cin >> T; T--; ) { 
  cin >> N >> K >> C;  
  pair<int64_t, int64_t>ret = {Comb(N - 1, C - 1, fact[0], ifact[0], prime[0]) * 2, prime[0]}; 
  for(int j = 1; j < sz(prime); j++) { 
   ret = chinese_remainder_theorem(ret.first, ret.second, Comb(N - 1, C - 1, fact[j], ifact[j], prime[j]) * 2, prime[j]); 
  }
  cout << ret.first << '\n'; 
 }
 return 0; 
}
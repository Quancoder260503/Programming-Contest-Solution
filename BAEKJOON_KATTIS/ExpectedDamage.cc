#include<bits/stdc++.h> 

using namespace std;

#define sz(x) int(x.size())

const int mod = 998244353;

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

int main() {
 int N, M; 
 cin >> N >> M; 
 vector<int64_t>health(N), prefix(N + 1); 
 for(int i = 0; i < N; i++) { 
  cin >> health[i]; 
 } 
 sort(health.begin(), health.end()); 
 for(int i = 0; i < N; i++) { 
  (prefix[i + 1] = prefix[i] + health[i]) %= mod;
 } 
 int64_t ret = 0;
 for(int i = 0, a, b; i < M; i++) { 
  cin >> a >> b; 
  int bigger = lower_bound(health.begin(), health.end(), b) - health.begin();
  int64_t ret = prefix[bigger] % mod * 
                (max(0, N - bigger + 1 - a) % mod * mod_inv(N - bigger + 1, mod) % mod + mod) % mod;
  ret %= mod; 
  ret += max(0, N - bigger - a) % mod * mod_inv(N - bigger, mod) % mod * 
         (prefix[N] - prefix[bigger] + mod) % mod;
  ret %= mod; 
  cout << ret << '\n'; 
 } 
 return 0;
}
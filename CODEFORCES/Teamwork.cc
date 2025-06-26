#include "bits/stdc++.h"
 
using namespace std; 
 
#define sz(x) int(x.size())
#define int64_t long long
 
const int mod = 1e9 + 7; 
const int maxf = 5e3 + 2; 
const int maxc = 1e6 + 2;
 
int64_t dyn[maxf][maxf], pw2[maxc]; 
int N, K; 
 
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
 
int64_t memo(int a, int b, int sum) { 
  int64_t &ret = dyn[a][b]; 
  if(ret != -1) return ret;
  int c = sum - b; 
  if(a == 0) return ret = (c < maxc ? pw2[c] : fpow(2, c)); 
  (ret = 1LL * c % mod * memo(a - 1, b + 1, sum) % mod + 
        1LL * b % mod * memo(a - 1, b, sum) % mod) %= mod;
  return ret;
}
 
int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  pw2[0] = 1; 
  for(int i = 1; i < maxc; i++) { 
    pw2[i] = pw2[i - 1] % mod * 2 % mod; 
  } 
  cin >> N >> K;
  memset(dyn, -1, sizeof(dyn));
  cout << memo(K, 0, N) << '\n'; 
  return 0; 
}
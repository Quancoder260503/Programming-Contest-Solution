#include "bits/stdc++.h"

using namespace std;

#define int64_t long long

const int mod = 998244353;
const int maxf = 2e6; 
int N, M, K;

int64_t ret[maxf]; 

int64_t fpow(int64_t a, int64_t k) {
  if (!k) return 1;
  int64_t res = a, tmp = a;
  k--;
  while (k) {
    if (k & 1) {
      res = 1LL * res % mod * tmp % mod;
    }
    tmp = 1LL* tmp % mod * tmp % mod;
    k >>= 1;
  }
  return res;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> N >> M >> K;
  for(int i = 1; i <= M; i++) { 
    ret[i] = fpow(M / i, N); 
  }
  for(int i = M; i > 0; i--) { 
    for(int j = 2 * i; j <= M; j += i) { 
       ret[i] = (ret[i] + mod - ret[j]) % mod; 
    }
  }
  cout << ret[K] << '\n';
  return 0;
}
#include "bits/stdc++.h"

using namespace std;

const int maxf = 305;
const int mod = 1e9 + 7;

int64_t dyn[maxf][maxf][2];
int a[maxf], N, g[maxf][maxf];

int64_t memo(int i, int j, int type) {
  if((i + 1) % N == j) return 1; 
  int64_t &ret = dyn[i][j][type];
  if (ret != -1) return ret;
  ret = 0; 
  for(int k = (i + 1) % N; k != j; k = (k + 1) % N) { 
    if(g[i][k] && !type) { 
      (ret += memo(i, k, 0) % mod * memo(k, j, 0) % mod) %= mod; 
    }
    if(g[k][j]) { 
      (ret += memo(i, k, 1) % mod * memo(k, j, 0) % mod) %= mod; 
    }
  }
  return ret;
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

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> N;
  for (int i = 0; i < N; i++) {
    cin >> a[i];
  }
  for(int i = 0; i < N; i++) { 
    for(int j = 0; j < N; j++) { 
      g[i][j] = (gcd(a[i], a[j]) > 1); 
    }
  }
  memset(dyn, -1, sizeof(dyn));
  int64_t ret = 0; 
  for(int i = 0; i < N; i++) { 
    for(int j = i + 1; j < N; j++) if(g[i][j]) { 
      ret += memo(i, j, 0) % mod * memo(j, i, 0) % mod; 
      ret %= mod; 
    }
  }
  ret = ret % mod * fpow(N - 1, mod - 2) % mod; 
  cout << ret << '\n'; 
  return 0;
}

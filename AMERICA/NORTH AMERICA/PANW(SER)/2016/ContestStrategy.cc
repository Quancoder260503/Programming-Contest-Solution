#include "bits/stdc++.h"

using namespace std;

const int mod = 1e9 + 7;

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

vector<vector<vector<vector<int64_t>>>>dyn; 
vector<int>T;
vector<int64_t>inv; 
int K, N; 

int64_t memo(int inc, int inless, int outless, int outmore) {
  int64_t &ret = dyn[inc][inless][outless][outmore];
  if (ret != -1) return ret;
  if (inc && inless == 0) return 0; 
  int rem = outless + outmore + (!inc);
  if (rem == 0) return inless;
  if (inless > 0) inless--;
  dyn[inc][inless + 1][outless][outmore] = 
      (1 +
        (inc == 0    ? memo(true, inless, outless, outmore) % mod * inv[rem] % mod : 0) +
        (outless > 0 ? memo(inc, inless + 1, outless - 1, outmore) % mod * outless % mod * inv[rem] % mod : 0) +
        (outmore > 0 ? memo(inc, inless, outless, outmore - 1)     % mod * outmore % mod * inv[rem] % mod : 0));
  return dyn[inc][inless + 1][outless][outmore];
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> N >> K;
  T.resize(N); 
  inv.resize(N + 1); 
  for (int i = 0; i < N; i++) {
    cin >> T[i];
  }
  for(int i = 1; i <= N; i++) { 
    inv[i] = fpow(i, mod - 2); 
  }
  sort(T.begin(), T.end());
  dyn.resize(2, vector<vector<vector<int64_t>>>(K + 1, vector<vector<int64_t>>(N + 1, vector<int64_t>(N + 1, -1))));
  int64_t ret = 0;
  for (int i = 0; i < N; i++) { 
    (ret += (N + K - memo(false, K, i, N - i - 1) % mod + mod) % mod * T[i] % mod) %= mod;
  }
  for (int i = 1; i <= N; i++) {
    ret = ret % mod * i % mod;
  }
  cout << ret << '\n';
  return 0;
}